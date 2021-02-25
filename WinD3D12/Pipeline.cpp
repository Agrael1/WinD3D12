module;
#include "DawnAdapter.h"
module Pipeline;

ver::Pipeline::Pipeline(const Graphics& gfx)
	:gfx(gfx)
{
}

void ver::Pipeline::BindVertexLayout(const ver::dv::VertexLayout& vb)
{
	pVL = &vb;
}

void ver::Pipeline::BindVertexShader(const Shader& vs)
{
	desc.vertexStage = vs.GetStageDescriptor();
}

void ver::Pipeline::SetBindGroup(const BindGroup& bg)
{
	bindGroupLayouts[counter++] = bg.CookLayout();
}

void ver::Pipeline::SetRawLayout(const wgpu::BindGroupLayout& in)
{
	bindGroupLayouts[counter++] = in;
}

[[nodiscard]]
wgpu::RenderPipeline ver::Pipeline::CookPipeline() const noexcept
{
	// pipeline layout (used by the render pipeline, released after its creation)
	wgpu::PipelineLayoutDescriptor layoutDesc = {};
	layoutDesc.bindGroupLayoutCount = counter;
	layoutDesc.bindGroupLayouts = bindGroupLayouts.data();

	// begin pipeline set-up
	desc.layout = GetDevice(gfx).CreatePipelineLayout(&layoutDesc);

	if (PSDesc)
		desc.fragmentStage = &PSDesc.value();

	if (pVL)
	{
		wgpu::VertexBufferLayoutDescriptor vertDesc = {};
		vertDesc.arrayStride = pVL->Size();
		vertDesc.attributeCount = uint32_t(pVL->GetElementCount());
		vertDesc.attributes = pVL->GetDescs().data();
		wgpu::VertexStateDescriptor vertState = {};
		vertState.vertexBufferCount = 1;
		vertState.vertexBuffers = &vertDesc;
		desc.vertexState = &vertState;
	}

	desc.primitiveTopology = wgpu::PrimitiveTopology::TriangleList;

	desc.sampleCount = 1;

	// describe blend
	wgpu::BlendDescriptor blendDesc = {};
	blendDesc.operation = wgpu::BlendOperation::Add;
	blendDesc.srcFactor = wgpu::BlendFactor::SrcAlpha;
	blendDesc.dstFactor = wgpu::BlendFactor::OneMinusSrcAlpha;
	wgpu::ColorStateDescriptor colorDesc = {};
	colorDesc.format = gfx.GetSwapChainFormat();
	colorDesc.alphaBlend = blendDesc;
	colorDesc.colorBlend = blendDesc;
	colorDesc.writeMask = wgpu::ColorWriteMask::All;

	desc.colorStateCount = 1;
	desc.colorStates = &colorDesc;

	desc.sampleMask = 0xFFFFFFFF; // <-- Note: this currently causes Emscripten to fail (sampleMask ends up as -1, which trips an assert)

	return GetDevice(gfx).CreateRenderPipeline(&desc);
}
