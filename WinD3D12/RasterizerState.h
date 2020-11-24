#pragma once
#include "Bindable.h"

namespace ver
{
	class RasterizerState : public Bindable
	{
	public:
		RasterizerState(const Graphics& gfx, bool twosided)
			:raster{
				.nextInChain = nullptr,
				.frontFace = wgpu::FrontFace::CCW,
				.cullMode = twosided ? wgpu::CullMode::None: wgpu::CullMode::Back,
				.depthBias = 0,
				.depthBiasSlopeScale = 0.0f,
				.depthBiasClamp = 0.0f
			}
		{

		}
	public:
		const wgpu::RasterizationStateDescriptor& Get()const noexcept
		{
			return raster;
		}
	private:
		wgpu::RasterizationStateDescriptor raster;
	};
}
