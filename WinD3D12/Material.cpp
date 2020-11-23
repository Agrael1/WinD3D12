#include "pch.h"
#include "Material.h"
#include "Surface.h"
#include "Future.h"


Future<std::vector<ver::Texture>>
ConstructTextures(const ver::Graphics& gfx, std::span<aiString> textures, size_t actual)noexcept
{
	if (!actual)
		co_return{};

	std::vector<winrt::Windows::Foundation::IAsyncAction> tasks;
	ver::SurfaceLoader surf;
	std::vector<ver::Texture> ret;
	ret.resize(actual);
	tasks.reserve(actual);

	for (size_t i = 0; auto & x : ret)
	{
		if (textures[i].length)
			tasks.push_back(surf.LoadTextureAsync(gfx, textures[i].C_Str(), &x));
		i++;
	}

	for (auto && x : tasks)
	{
		co_await x;
	}

	co_return ret;
}

ver::Material::Material(Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path) noexcept
	:modelPath(path.string()), vtxLayout({VType::Position3D, VType::Normal})
{
	const auto rootPath = path.parent_path().string() + "\\";
	{
		aiString tempName;
		material.Get(AI_MATKEY_NAME, tempName);
		name = tempName.C_Str();
	}
	std::string shaderCode = "Phong";
	std::array<aiString, 3> texFileName;
	size_t inserter = 0;

	dc::Layout pscLayout;
	bool hasTexture = false;
	bool hasGlossAlpha = false;

	

	// diffuse
	{
		bool hasAlpha = false;
		if (material.GetTexture(aiTextureType_DIFFUSE, 0, &texFileName[inserter]) == aiReturn_SUCCESS)
		{
			hasTexture = true;
			shaderCode += "Dif";
			vtxLayout.Add(VType::Texture2D);
			inserter++;
			//auto tex = Texture::Resolve(gfx, rootPath + texFileName.C_Str());
			//if (tex->UsesAlpha())
			//{
			//	hasAlpha = true;
			//	shaderCode += "Msk";
			//}
		}
		else
		{
			pscLayout.Add(dc::Type::Float3, "materialColor");
		}
	}
	//step.AddBindable(RasterizerState::Resolve(gfx, hasAlpha));
	// specular
	{
		if (material.GetTexture(aiTextureType_SPECULAR, 0, &texFileName[inserter]) == aiReturn_SUCCESS)
		{
			hasTexture = true;
			shaderCode += "Spc";
			vtxLayout.Add(VType::Texture2D);
			//auto tex = Texture::Resolve(gfx, rootPath + texFileName.C_Str(), 1);
			//hasGlossAlpha = tex->UsesAlpha();
			//step.AddBindable(std::move(tex));
			pscLayout.Add({
				{"useGlossAlpha", dc::Type::Bool, },
				{"useSpecularMap", dc::Type::Bool} });
			inserter++;
		}
		pscLayout.Add({
			{"specularColor", dc::Type::Float3},
			{"specularWeight", dc::Type::Float },
			{"specularGloss", dc::Type::Float } });
	}
	// normal
	{
		if (material.GetTexture(aiTextureType_NORMALS, 0, &texFileName[inserter]) == aiReturn_SUCCESS)
		{
			hasTexture = true;
			shaderCode += "Nrm";
			vtxLayout.Add(VType::Texture2D);
			vtxLayout.Add(VType::Tangent);
			vtxLayout.Add(VType::Bitangent);

			pscLayout.Add({
				{"useNormalMap"   , dc::Type::Bool },
				{"normalMapWeight", dc::Type::Float} });
		}
	}
	std::vector<ver::Texture> x = ConstructTextures(gfx, texFileName, inserter)();

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
