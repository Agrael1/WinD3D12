#include "pch.h"
#include "Material.h"
#include "Sampler.h"
#include "RasterizerState.h"
#include "Texture.h"
#include "Shaders.h"
#include "PhongLightLayout.h"

using namespace ver;

ver::Material::Material(const Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path) noexcept
	:modelPath(path.string()), vtxLayout({VType::Position3D, VType::Normal})
{
	const auto rootPath = path.parent_path().string() + "\\";
	{
		aiString tempName;
		material.Get(AI_MATKEY_NAME, tempName);
		name = tempName.C_Str();
	}

	std::vector<Texture> texes;
	texes.reserve(3);
	// phong technique
	{
		std::string shaderCodeVS = "Phong";
		std::string shaderCodePS = "Phong";
		aiString texFileName;

		// common (pre)
		vtxLayout.Add(VType::Position3D);
		vtxLayout.Add(VType::Normal);

		dc::Layout pscLayout;
		bool hasTexture = false;
		bool hasGlossAlpha = false;
		bool bHasDiffuse = false;
		bool bHasSpecular = false;
		bool bHasNormal = false;
		uint8_t texOffset = 3;

		// diffuse
		{
			if (bHasDiffuse = (material.GetTexture(aiTextureType_DIFFUSE, 0, &texFileName) == aiReturn_SUCCESS))
			{
				hasTexture = true;
				shaderCodeVS += "Dif";
				shaderCodePS += "Dif";
				vtxLayout.Add(VType::Texture2D);
				texes.emplace_back(gfx, rootPath + texFileName.C_Str(), texOffset++);
			}
			else
			{
				pscLayout.Add(dc::Type::Float3, "materialColor");
			}
		}
		// specular
		{
			if (bHasSpecular = (material.GetTexture(aiTextureType_SPECULAR, 0, &texFileName) == aiReturn_SUCCESS))
			{
				hasTexture = true;
				shaderCodePS += "Spc";
				vtxLayout.Add(VType::Texture2D);
				texes.emplace_back(gfx, rootPath + texFileName.C_Str(), texOffset++);
				pscLayout.Add({
					{"useGlossAlpha", dc::Type::Bool, },
					{"useSpecularMap", dc::Type::Bool} });
			}
			pscLayout.Add({
				{"specularColor", dc::Type::Float3},
				{"specularWeight", dc::Type::Float },
				{"specularGloss", dc::Type::Float } });
		}
		// normal
		{
			if (bHasNormal = (material.GetTexture(aiTextureType_NORMALS, 0, &texFileName) == aiReturn_SUCCESS))
			{
				hasTexture = true;
				shaderCodeVS += "Nrm";
				shaderCodePS += "Nrm";
				vtxLayout.Add(VType::Texture2D);
				vtxLayout.Add(VType::Tangent);
				vtxLayout.Add(VType::Bitangent);
				texes.emplace_back(gfx, rootPath + texFileName.C_Str(), texOffset++);
				pscLayout.Add({
					{"useNormalMap"   , dc::Type::Bool },
					{"normalMapWeight", dc::Type::Float} });
			}
		}

		if (bHasDiffuse)
		{
			bool hasAlpha = false;
			if (texes[0].UsesAlpha())
			{
				hasAlpha = true;
				shaderCodePS.insert(8, "Msk");
			}
			pipeline.BindRasterLayout(RasterizerState(gfx, hasAlpha));
		}
		if (bHasSpecular)
		{
			hasGlossAlpha = texes[1].UsesAlpha();
		}

		for (auto& x : texes)
			bindings.BindResource(x);

		// common (post)
		{
			//step.AddBindable(std::make_shared<TransformCbuf>(gfx, 0u));
			auto pvs = Shader::Resolve(gfx, shaderCodeVS + ".vs", "main");
			auto pps = Shader::Resolve(gfx, shaderCodePS + ".ps", "main");

			pipeline.BindVertexLayout(vtxLayout);
			pipeline.BindVertexShader(*pvs.get());
			pipeline.BindPixelShader(*pps.get());
			pipeline.SetBindGroup(PhongLightLayout::Get(gfx), 1);
			if (hasTexture) bindings.BindResource(Sampler{ gfx, texOffset++ });

			// PS material params (cbuf)
			dc::Buffer buf{ std::move(pscLayout) };
			if (auto r = buf["materialColor"]; r)
			{
				aiColor3D color = { 0.45f,0.45f,0.85f };
				material.Get(AI_MATKEY_COLOR_DIFFUSE, color);
				r = reinterpret_cast<DirectX::XMFLOAT3&>(color);
			}
			buf["useGlossAlpha"].SetIfExists(hasGlossAlpha);
			buf["useSpecularMap"].SetIfExists(true);
			if (auto r = buf["specularColor"]; r)
			{
				aiColor3D color = { 0.18f,0.18f,0.18f };
				material.Get(AI_MATKEY_COLOR_SPECULAR, color);
				r = reinterpret_cast<DirectX::XMFLOAT3&>(color);
			}
			buf["specularWeight"].SetIfExists(1.0f);
			if (auto r = buf["specularGloss"]; r)
			{
				float gloss = 8.0f;
				material.Get(AI_MATKEY_SHININESS, gloss);
				r = gloss;
			}
			buf["useNormalMap"].SetIfExists(true);
			buf["normalMapWeight"].SetIfExists(1.0f);
			pixcb.emplace(gfx, std::move(buf), 2u);
		}
	}
}

winrt::Windows::Foundation::IAsyncAction 
Material::MakeAsync(const Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path)
{
	modelPath = path.string();
	const auto rootPath = path.parent_path().string() + "\\";
	{
		aiString tempName;
		material.Get(AI_MATKEY_NAME, tempName);
		name = tempName.C_Str();
	}

	std::vector<Foundation::IAsyncAction> tasks;
	std::vector<Texture> texes;
	texes.reserve(3);
	tasks.reserve(3);
	// phong technique
	{
		std::string shaderCodeVS = "Phong";
		std::string shaderCodePS = "Phong";
		aiString texFileName;

		// common (pre)
		vtxLayout.Add(VType::Position3D);
		vtxLayout.Add(VType::Normal);

		dc::Layout pscLayout;
		bool hasTexture = false;
		bool hasGlossAlpha = false;
		bool bHasDiffuse = false;
		bool bHasSpecular = false;
		bool bHasNormal = false;
		uint8_t texOffset = 3;

		// diffuse
		{
			if (bHasDiffuse = (material.GetTexture(aiTextureType_DIFFUSE, 0, &texFileName) == aiReturn_SUCCESS))
			{
				hasTexture = true;
				shaderCodeVS += "Dif";
				shaderCodePS += "Dif";
				vtxLayout.Add(VType::Texture2D);
				tasks.emplace_back(Texture::MakeAsync(texes.emplace_back(), gfx, rootPath + texFileName.C_Str(), texOffset++));
			}
			else
			{
				pscLayout.Add(dc::Type::Float3, "materialColor");
			}
		}
		// specular
		{
			if (bHasSpecular = (material.GetTexture(aiTextureType_SPECULAR, 0, &texFileName) == aiReturn_SUCCESS))
			{
				hasTexture = true;
				shaderCodePS += "Spc";
				vtxLayout.Add(VType::Texture2D);
				tasks.emplace_back(Texture::MakeAsync(texes.emplace_back(), gfx, rootPath + texFileName.C_Str(), texOffset++));
				pscLayout.Add({
					{"useGlossAlpha", dc::Type::Bool, },
					{"useSpecularMap", dc::Type::Bool} });
			}
			pscLayout.Add({
				{"specularColor", dc::Type::Float3},
				{"specularWeight", dc::Type::Float },
				{"specularGloss", dc::Type::Float } });
		}
		// normal
		{
			if (bHasNormal = (material.GetTexture(aiTextureType_NORMALS, 0, &texFileName) == aiReturn_SUCCESS))
			{
				hasTexture = true;
				shaderCodeVS += "Nrm";
				shaderCodePS += "Nrm";
				vtxLayout.Add(VType::Texture2D);
				vtxLayout.Add(VType::Tangent);
				vtxLayout.Add(VType::Bitangent);
				tasks.emplace_back(Texture::MakeAsync(texes.emplace_back(), gfx, rootPath + texFileName.C_Str(), texOffset++));
				pscLayout.Add({
					{"useNormalMap"   , dc::Type::Bool },
					{"normalMapWeight", dc::Type::Float} });
			}
		}

		for (auto& x : tasks)
			co_await(x);

		if (bHasDiffuse)
		{
			bool hasAlpha = false;
			if (texes[0].UsesAlpha())
			{
				hasAlpha = true;
				shaderCodePS.insert(8, "Msk");
			}
			pipeline.BindRasterLayout(RasterizerState(gfx, hasAlpha));
		}
		if (bHasSpecular)
		{
			hasGlossAlpha = texes[1].UsesAlpha();
		}

		for (auto& x : texes)
			bindings.BindResource(x);

		// common (post)
		{
			//step.AddBindable(std::make_shared<TransformCbuf>(gfx, 0u));
			auto pvs = Shader::ResolveAsync(gfx, shaderCodeVS + ".vs", "main");
			auto pps = Shader::ResolveAsync(gfx, shaderCodePS + ".ps", "main");

			co_await winrt::when_all(pvs, pps);

			pipeline.BindVertexLayout(vtxLayout);
			pipeline.BindVertexShader(*pvs.get());
			pipeline.BindPixelShader(*pps.get());
			pipeline.SetBindGroup(PhongLightLayout::Get(gfx), 1);
			if (hasTexture) bindings.BindResource(Sampler{ gfx, texOffset++ });

			// PS material params (cbuf)
			dc::Buffer buf{ std::move(pscLayout) };
			if (auto r = buf["materialColor"]; r)
			{
				aiColor3D color = { 0.45f,0.45f,0.85f };
				material.Get(AI_MATKEY_COLOR_DIFFUSE, color);
				r = reinterpret_cast<DirectX::XMFLOAT3&>(color);
			}
			buf["useGlossAlpha"].SetIfExists(hasGlossAlpha);
			buf["useSpecularMap"].SetIfExists(true);
			if (auto r = buf["specularColor"]; r)
			{
				aiColor3D color = { 0.18f,0.18f,0.18f };
				material.Get(AI_MATKEY_COLOR_SPECULAR, color);
				r = reinterpret_cast<DirectX::XMFLOAT3&>(color);
			}
			buf["specularWeight"].SetIfExists(1.0f);
			if (auto r = buf["specularGloss"]; r)
			{
				float gloss = 8.0f;
				material.Get(AI_MATKEY_SHININESS, gloss);
				r = gloss;
			}
			buf["useNormalMap"].SetIfExists(true);
			buf["normalMapWeight"].SetIfExists(1.0f);
			pixcb.emplace(gfx, std::move(buf), 2u);
		}
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

ver::VertexBuffer ver::Material::MakeVertexBindable(const Graphics& gfx, const aiMesh& mesh, float scale) const noexcept
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

ver::IndexBuffer ver::Material::MakeIndexBindable(const Graphics& gfx, const aiMesh& mesh) const noexcept
{
	return IndexBuffer(gfx, ExtractIndices(mesh));
}

PixelConstantBufferEx ver::Material::MakePixelBuffer(const Graphics& gfx) const noexcept
{
	return pixcb->Clone(gfx);
}

std::string ver::Material::MakeMeshTag(const aiMesh& mesh) const noexcept
{
	return modelPath + "%" + mesh.mName.C_Str();
}




