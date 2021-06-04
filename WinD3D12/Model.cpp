#include "pch.h"
#include <Model.h>
#include <Material.h>
#include <Node.h>

using namespace ver;

DirectX::XMMATRIX ScaleTranslation(DirectX::XMMATRIX matrix, float scale)
{
	namespace dx = DirectX;
	dx::XMVECTOR s = _mm_load1_ps(&scale);
	s = _mm_and_ps(s, dx::g_XMMask3);
	matrix.r[3] = _mm_add_ps(_mm_mul_ps(matrix.r[3], s), dx::g_XMIdentityR3);
	return matrix;
}

winrt::Windows::Foundation::IAsyncAction 
ver::Model::MakeAsync(std::unique_ptr<Model>& to, Graphics& gfx, std::string_view pathString, float scale)
{
	std::unique_ptr<Model> out(new Model());

	Assimp::Importer imp;
	const auto pScene = imp.ReadFile(pathString.data(),
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_ConvertToLeftHanded |
		aiProcess_GenNormals |
		aiProcess_CalcTangentSpace
	);

	if (!pScene->mNumMeshes || pScene == nullptr)
	{
		to.reset();
		co_return;
	}


	out->meshPtrs.reserve(pScene->mNumMeshes);

	std::vector<Material> materials;
	materials.resize(pScene->mNumMaterials);
	co_await MakeMaterialsAsync(gfx, materials, pScene, pathString);

	std::vector<concurrency::task<std::shared_ptr<Mesh>>> meshes;
	meshes.reserve(pScene->mNumMeshes);
	//parse materials
	for (size_t i = 0; i < pScene->mNumMeshes; i++)
	{
		const auto& mesh = *pScene->mMeshes[i];
		meshes.push_back(Mesh::MakeAsync(gfx, materials[mesh.mMaterialIndex], mesh, scale));
	}
	for (auto&& t : meshes)
		out->meshPtrs.push_back(co_await t);

	int nextId = 0;
	out->pRoot = out->ParseNode(nextId, *pScene->mRootNode, scale);
	to.reset(out.release());
}

winrt::Windows::Foundation::IAsyncAction 
ver::Model::MakeMaterialsAsync(Graphics& gfx, std::vector<Material>& materials, const aiScene* pScene, std::string_view pathString)
{
	std::vector<winrt::Windows::Foundation::IAsyncAction> tasks;
	tasks.reserve(pScene->mNumMaterials);

	for (size_t i = 0; auto & mat: materials)
	{
		tasks.emplace_back(mat.MakeAsync(gfx, *pScene->mMaterials[i], pathString));
		i++;
	}
	for(auto&&t:tasks)co_await t;
}

std::unique_ptr<Node> ver::Model::ParseNode(int& nextId, const aiNode& node, float scale) noexcept
{
	namespace dx = DirectX;
	const auto transform = ScaleTranslation(dx::XMMatrixTranspose(dx::XMLoadFloat4x4(
		reinterpret_cast<const dx::XMFLOAT4X4*>(&node.mTransformation)
	)), scale);

	std::vector<Mesh*> curMeshPtrs;
	curMeshPtrs.reserve(node.mNumMeshes);
	for (size_t i = 0; i < node.mNumMeshes; i++)
	{
		const auto meshIdx = node.mMeshes[i];
		curMeshPtrs.push_back(meshPtrs.at(meshIdx).get());
	}

	auto pNode = std::make_unique<Node>(nextId++, node.mName.C_Str(), std::move(curMeshPtrs), transform);
	for (size_t i = 0; i < node.mNumChildren; i++)
	{
		pNode->AddChild(ParseNode(nextId, *node.mChildren[i], scale));
	}

	return pNode;
}