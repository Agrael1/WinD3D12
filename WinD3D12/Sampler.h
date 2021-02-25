#pragma once
#include "ConstantBinding.h"

namespace ver
{
	class Sampler : public ConstantBinding<Sampler>
	{
	public:
		Sampler(const Graphics& gfx, uint32_t xslot = 0, wgpu::FilterMode type = wgpu::FilterMode::Linear);
	public:
		wgpu::BindGroupLayoutEntry GetLayout()const noexcept;
		wgpu::BindGroupEntry GetEntryDesc()const noexcept;
	private:
		wgpu::Sampler sampler;
		uint32_t slot;
	};
}