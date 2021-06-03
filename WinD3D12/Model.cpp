#include "pch.h"
#include <Model.h>

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

	auto v = imp.GetErrorString();

	if (!pScene->mNumMeshes || pScene == nullptr)
	{
		to.reset();
		co_return;
	}


	out->meshPtrs.reserve(pScene->mNumMeshes);

	std::vector<Material> materials;
	materials.resize(pScene->mNumMaterials);
	co_await MakeMaterialsAsync(gfx, materials, pScene, pathString);

	//parse materials
	for (size_t i = 0; i < pScene->mNumMeshes; i++)
	{
		const auto& mesh = *pScene->mMeshes[i];
		out->meshPtrs.push_back(std::make_unique<Mesh>(gfx, materials[mesh.mMaterialIndex], mesh, scale));
	}

	int nextId = 0;
	out->pRoot = out->ParseNode(nextId, *pScene->mRootNode, scale);
	to.reset(out.release());
}

winrt::Windows::Foundation::IAsyncAction ver::Model::MakeMaterialsAsync(Graphics& gfx, std::vector<Material>& materials, const aiScene* pScene, std::string_view pathString)
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
