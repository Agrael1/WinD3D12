#pragma once
#include "Bindable.h"

namespace ver
{
	class Sampler : public Bindable
	{
	public:
		Sampler(const Graphics& gfx, wgpu::FilterMode type = wgpu::FilterMode::Linear)
		{

			wgpu::SamplerDescriptorDummyAnisotropicFiltering y{};
			y.maxAnisotropy = 16.0f;

			wgpu::SamplerDescriptor x
			{
				.nextInChain = nullptr,
				.label = nullptr,
				.addressModeU = wgpu::AddressMode::ClampToEdge,
				.addressModeV = wgpu::AddressMode::ClampToEdge,
				.addressModeW = wgpu::AddressMode::ClampToEdge,
				.magFilter = type,
				.minFilter = type,
				.mipmapFilter = type,
				.lodMinClamp = 0.0f,
				.lodMaxClamp = 1000.0f,
				.compare = wgpu::CompareFunction::Never,
			};
			sampler = GetDevice(gfx).CreateSampler(&x);
		}
	private:
		wgpu::Sampler sampler;
	};
}