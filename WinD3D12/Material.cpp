#include "Material.h"

ver::Material::Material(Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path) noexcept
	:modelPath(path.string())
{
	const auto rootPath = path.parent_path().string() + "\\";
	{
		aiString tempName;
		material.Get(AI_MATKEY_NAME, tempName);
		name = tempName.C_Str();
	}
}

ver::dv::VertexBuffer ver::Material::ExtractVertices(const aiMesh& mesh) const noexcept
{
	return { vtxLayout,mesh };
}

std::vector<uint32_t> ver::Material::ExtractIndices(const aiMesh& mesh) const noexcept
{
	std::vector<uint32_t> indices;
	indices.reserve(mesh.mNumFaces * 3);
	for (unsigned int i = 0; i < mesh.mNumFaces; i++)
	{
		const auto& face = mesh.mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}
	return indices;
}

ver::VertexBuffer ver::Material::MakeVertexBindable(Graphics& gfx, const aiMesh& mesh, float scale) const noexcept
{
	auto vtc = ExtractVertices(mesh);
	if (scale != 1.0f)
	{
		for (auto i = 0u; i < vtc.Size(); i++)
		{
			DirectX::XMFLOAT3& pos = vtc[i].Attr<ver::dv::VertexLayout::ElementType::Position3D>();
			pos.x *= scale;
			pos.y *= scale;
			pos.z *= scale;
		}
	}
	return VertexBuffer{ gfx, vtc.data() };
}

ver::IndexBuffer ver::Material::MakeIndexBindable(Graphics& gfx, const aiMesh& mesh) const noexcept
{
	return IndexBuffer(gfx, ExtractIndices(mesh));
}

std::string ver::Material::MakeMeshTag(const aiMesh& mesh) const noexcept
{
	return modelPath + "%" + mesh.mName.C_Str();
}
