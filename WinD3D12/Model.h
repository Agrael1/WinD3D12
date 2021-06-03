#pragma once
#include <Mesh.h>
#include <Node.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ModelException.h"


namespace ver
{
	class Model
	{
	public:
		static winrt::Windows::Foundation::IAsyncAction
			MakeAsync(std::unique_ptr<Model>& to, Graphics& gfx, std::string_view pathString, float scale = 1.0f);
	private:
		Model() = default;
		static winrt::Windows::Foundation::IAsyncAction
			MakeMaterialsAsync(Graphics& gfx, std::vector<Material>& materials, const aiScene* pScene, std::string_view pathString);
		static std::unique_ptr<Mesh> ParseMesh(Graphics& gfx, const aiMesh& mesh, const aiMaterial* const* pMaterials, const std::filesystem::path& path, float scale);
		std::unique_ptr<Node> ParseNode(int& nextId, const aiNode& node, float scale) noexcept;
	private:
		std::unique_ptr<Node> pRoot;
		std::vector<std::unique_ptr<Mesh>> meshPtrs;
	};
}
