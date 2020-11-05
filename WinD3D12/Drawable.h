#pragma once
#include <dawn/webgpu_cpp.h>
#include "Buffers.h"
#include <optional>

namespace ver
{
	class Drawable
	{
	public:
		virtual void Step(const Graphics&, float){}
		virtual void Submit(wgpu::RenderPassEncoder& pass)const noexcept
		{
			pass.SetPipeline(pipeline);
			pass.SetBindGroup(0, bindGroup, 0, 0);
			pass.SetVertexBuffer(0, *vBuffer, 0, 0);
			pass.SetIndexBufferWithFormat(*iBuffer, iBuffer->GetFormat(), 0, 0);
			pass.DrawIndexed(uint32_t(iBuffer->GetCount()));
		}
	protected:
		std::optional<VertexBuffer> vBuffer;
		std::optional<IndexBuffer> iBuffer;

		wgpu::BindGroup bindGroup;
		wgpu::RenderPipeline pipeline;
	};
}
