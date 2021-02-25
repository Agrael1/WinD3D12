module;
#include <optional>
export module Drawable;
export import Bindables;

export namespace ver
{
	class Drawable
	{
	public:
		virtual void Step(const Graphics&, float) {}
		virtual void Submit(wgpu::RenderPassEncoder& pass)const noexcept;
	protected:
		std::optional<VertexBuffer> vBuffer;
		std::optional<IndexBuffer> iBuffer;

		wgpu::BindGroup bindGroup;
		wgpu::RenderPipeline pipeline;
	};
}