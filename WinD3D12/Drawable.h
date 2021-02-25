#pragma once
import Bindables;

namespace ver
{
	class Drawable
	{
	public:
		virtual void Step(const Graphics&, float){}
		virtual void Submit(wgpu::RenderPassEncoder& pass)const noexcept;
	protected:
		std::optional<VertexBuffer> vBuffer;
		std::optional<IndexBuffer> iBuffer;

		wgpu::BindGroup bindGroup;
		wgpu::RenderPipeline pipeline;
	};
}
