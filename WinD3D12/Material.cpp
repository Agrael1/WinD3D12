#include "pch.h"
#include "Material.h"
#include "Surface.h"
#include "Sampler.h"
#include "RasterizerState.h"



std::vector<ver::Texture>
ConstructTextures(const ver::Graphics& gfx, std::span<std::string> textures, size_t actual)noexcept
{
	if (!actual)return{};

	ver::SurfaceLoader surf;
	std::vector<ver::Texture> ret;
	ret.resize(actual);

	for (size_t i = 0; auto & x : ret) {
		if (!textures[i].empty())
			surf.LoadTexture(gfx, textures[i], &x, i);
		i++;
	}

	return std::move(ret);
}
ver::Texture ExtractTexture(const ver::Graphics& gfx, std::string_view texture, uint32_t slot)
{
	ver::Texture x;
	ver::SurfaceLoader surf;
	surf.LoadTexture(gfx, texture, &x, slot);
	return std::move(x);
}

ver::Material::Material(Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path) noexcept
	:modelPath(path.string()), vtxLayout({VType::Position3D, VType::Normal})
{
	MakeTextures(gfx, material, path);
}
void ver::Material::MakeTextures(Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path)
{
	const auto rootPath = path.parent_path().string() + "\\";
	{
		aiString tempName;
		material.Get(AI_MATKEY_NAME, tempName);
		name = tempName.C_Str();
	}
	std::string shaderCode = "Phong";
	std::array<std::optional<ver::Texture>, 3> textures;


	dc::Layout pscLayout;
	bool hasTexture = false;
	bool hasGlossAlpha = false;
	uint8_t texOffset = 3;

	aiString aitexFileName;

	// diffuse
	{
		if (material.GetTexture(aiTextureType_DIFFUSE, 0, &aitexFileName) == aiReturn_SUCCESS)
		{
			hasTexture = true;
			shaderCode += "Dif";
			vtxLayout.Add(VType::Texture2D);
			textures[0] = ExtractTexture(gfx, rootPath + aitexFileName.C_Str(), texOffset++);
		}
		else
		{
			pscLayout.Add(dc::Type::Float3, "materialColor");
		}
	}
	// specular
	{
		if (material.GetTexture(aiTextureType_SPECULAR, 0, &aitexFileName) == aiReturn_SUCCESS)
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
			textures[1] = ExtractTexture(gfx, rootPath + aitexFileName.C_Str(), texOffset++);
		}
		pscLayout.Add({
			{"specularColor", dc::Type::Float3},
			{"specularWeight", dc::Type::Float },
			{"specularGloss", dc::Type::Float } });
	}
	// normal
	{
		if (material.GetTexture(aiTextureType_NORMALS, 0, &aitexFileName) == aiReturn_SUCCESS)
		{
			hasTexture = true;
			shaderCode += "Nrm";
			vtxLayout.Add(VType::Texture2D);
			vtxLayout.Add(VType::Tangent);
			vtxLayout.Add(VType::Bitangent);

			textures[2] = ExtractTexture(gfx, rootPath + aitexFileName.C_Str(), texOffset++);
			pscLayout.Add({
				{"useNormalMap"   , dc::Type::Bool },
				{"normalMapWeight", dc::Type::Float} });
		}
	}
	bool hasAlpha = false;
	if (textures[0] && textures[0].value().UsesAlpha())
	{
		shaderCode += "Msk";
		hasAlpha = true;
	}
	RasterizerState raster(gfx, hasAlpha);

	//set bindings
	{
		BindGroup bg(gfx, m_bindings);
		for (auto& x : textures){
			if (x) bg.BindResource(x.value());
		}
		if (hasTexture)
		{
			Sampler sample{ gfx , texOffset };
			bg.BindResource(sample);
		}

		
	//	step.AddBindable(std::make_shared<TransformCbuf>(gfx, 0u));
	//	auto pvs = VertexShader::Resolve(gfx, shaderCode + "_VS.cso");
	//	auto pvsbc = pvs->GetBytecode();
	//	step.AddBindable(std::move(pvs));
	//	step.AddBindable(PixelShader::Resolve(gfx, shaderCode + "_PS.cso"));
	//	step.AddBindable(InputLayout::Resolve(gfx, vtxLayout, pvsbc));
	//	if (hasTexture)
	//	{
	//		step.AddBindable(Sampler::Resolve(gfx));
	//	}
	//	// PS material params (cbuf)
	//	DC::Buffer buf{ std::move(pscLayout) };
	//	if (auto r = buf["materialColor"]; r.Exists())
	//	{
	//		aiColor3D color = { 0.45f,0.45f,0.85f };
	//		material.Get(AI_MATKEY_COLOR_DIFFUSE, color);
	//		r = reinterpret_cast<DirectX::XMFLOAT3&>(color);
	//	}
	//	buf["useGlossAlpha"].SetIfExists(hasGlossAlpha);
	//	buf["useSpecularMap"].SetIfExists(true);
	//	if (auto r = buf["specularColor"]; r.Exists())
	//	{
	//		aiColor3D color = { 0.18f,0.18f,0.18f };
	//		material.Get(AI_MATKEY_COLOR_SPECULAR, color);
	//		r = reinterpret_cast<DirectX::XMFLOAT3&>(color);
	//	}
	//	buf["specularWeight"].SetIfExists(1.0f);
	//	if (auto r = buf["specularGloss"]; r.Exists())
	//	{
	//		float gloss = 8.0f;
	//		material.Get(AI_MATKEY_SHININESS, gloss);
	//		r = gloss;
	//	}
	//	buf["useNormalMap"].SetIfExists(true);
	//	buf["normalMapWeight"].SetIfExists(1.0f);
	//	step.AddBindable(std::make_unique<CachingPixelConstantBufferEx>(gfx, std::move(buf), 1u));
	//}
	//phong.AddStep(std::move(step));
	//techniques.push_back(std::move(phong));

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




