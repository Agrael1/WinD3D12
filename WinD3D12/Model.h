#pragma once
#include <Node.h>
#include <Mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>


namespace ver
{
	class Material;
	class Model
	{
	public:
		static winrt::Windows::Foundation::IAsyncAction
			MakeAsync(std::unique_ptr<Model>& to, Graphics& gfx, std::string_view pathString, float scale = 1.0f);
	private:
		Model() = default;
		static winrt::Windows::Foundation::IAsyncAction
			MakeMaterialsAsync(Graphics& gfx, std::vector<Material>& materials, const aiScene* pScene, std::string_view pathString);
		std::unique_ptr<Node> ParseNode(int& nextId, const aiNode& node, float scale) noexcept;
	private:
		std::unique_ptr<Node> pRoot;
		std::vector<std::shared_ptr<Mesh>> meshPtrs;
	};
}
