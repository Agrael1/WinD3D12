#pragma once
#include "ConstantBufferEx.h"
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
		Material(const Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path) noexcept;
		winrt::Windows::Foundation::IAsyncAction
			MakeAsync(const Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path);
	public:
		dv::VertexBuffer ExtractVertices(const aiMesh& mesh) const noexcept;
		std::vector<uint32_t> ExtractIndices(const aiMesh& mesh) const noexcept;
		VertexBuffer MakeVertexBindable(const Graphics& gfx, const aiMesh& mesh, float scale = 1.0f) const noexcept;
		IndexBuffer MakeIndexBindable(const Graphics& gfx, const aiMesh& mesh) const noexcept;
		PixelConstantBufferEx MakePixelBuffer(const Graphics& gfx)const noexcept;
		const BindGroup& GetBinds()const noexcept { return bindings; }
		const Pipeline& GetPipeline()const noexcept { return pipeline; }
	private:
		std::string MakeMeshTag(const aiMesh& mesh) const noexcept;
	private:
		dv::VertexLayout vtxLayout;
		BindGroup bindings;
		Pipeline pipeline;
		std::optional<PixelConstantBufferEx> pixcb;
		std::string modelPath;
		std::string name;
	};
}
