#pragma once
#include <Node.h>
#include <Mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include <Material.h>


namespace ver
{
	class Material;
	class Model
	{
		friend class Panel;
	public:
		Model(const Graphics& gfx, std::string_view pathString, float scale = 1.0f);
		static winrt::Windows::Foundation::IAsyncAction
			MakeAsync(std::unique_ptr<Model>& to, const Graphics& gfx, std::string_view pathString, float scale = 1.0f);
		void Step(const Graphics& gfx, float dt);
		void Submit(wgpu::RenderPassEncoder& pass)const noexcept;
	private:
		Model() = default;
		static winrt::Windows::Foundation::IAsyncAction
			MakeMaterialsAsync(const Graphics& gfx, std::vector<Material>& materials, const aiScene* pScene, std::string_view pathString);
		std::unique_ptr<Node> ParseNode(int& nextId, const aiNode& node, float scale) noexcept;
	private:
		std::unique_ptr<Node> pRoot;
		std::vector<std::shared_ptr<Mesh>> meshPtrs;
		std::vector<Material> x_materials;
	};
}
