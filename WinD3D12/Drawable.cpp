module;
#include <span>
module Drawable;

void ver::Drawable::Submit(wgpu::RenderPassEncoder& pass)const noexcept
{
	pass.SetPipeline(pipeline);
	pass.SetBindGroup(0, bindGroup, 0, 0);
	pass.SetVertexBuffer(0, *vBuffer, 0, 0);
	pass.SetIndexBufferWithFormat(*iBuffer, iBuffer->GetFormat(), 0, 0);
	pass.DrawIndexed(uint32_t(iBuffer->GetCount()));
}