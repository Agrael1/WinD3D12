module RasterizerState;

using namespace ver;

RasterizerState::RasterizerState(const Graphics&, bool twosided)
	:raster{
		.nextInChain = nullptr,
		.frontFace = wgpu::FrontFace::CCW,
		.cullMode = twosided ? wgpu::CullMode::None : wgpu::CullMode::Back,
		.depthBias = 0,
		.depthBiasSlopeScale = 0.0f,
		.depthBiasClamp = 0.0f
}
{

}

const wgpu::RasterizationStateDescriptor& ver::RasterizerState::Get() const noexcept
{
	return raster;
}
