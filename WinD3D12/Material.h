#pragma once
#include "DynamicConstant.h"
#include "DynamicVBuffer.h"
#include "Pipeline.h"
#include <vector>
#include <filesystem>

struct aiMaterial;
struct aiMesh;


namespace ver
{
	class Graphics;

	class Material
	{
	public:
		Material() = default;
		Material(Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path) noexcept;
		winrt::Windows::Foundation::IAsyncAction
			MakeAsync(Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path);
	public:
		dv::VertexBuffer ExtractVertices(const aiMesh& mesh) const noexcept;
		std::vector<uint32_t> ExtractIndices(const aiMesh& mesh) const noexcept;
		VertexBuffer MakeVertexBindable(Graphics& gfx, const aiMesh& mesh, float scale = 1.0f) const noexcept;
		IndexBuffer MakeIndexBindable(Graphics& gfx, const aiMesh& mesh) const noexcept;
	private:
		std::string MakeMeshTag(const aiMesh& mesh) const noexcept;
		void MakeTextures(Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path);
	private:
		dv::VertexLayout vtxLayout;
		BindGroup bindings;
		Pipeline pipeline;
		std::string modelPath;
		std::string name;
	};
}
