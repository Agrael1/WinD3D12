module;
#include "DawnAdapter.h"
module Sampler;

using namespace ver;

Sampler::Sampler(const Graphics& gfx, uint32_t xslot, wgpu::FilterMode type)
	:slot(xslot)
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

wgpu::BindGroupLayoutEntry ver::Sampler::GetLayout() const noexcept
{
	return
	{
		.binding = slot,
		.visibility = wgpu::ShaderStage::Fragment,
		.type = wgpu::BindingType::ComparisonSampler,
		.hasDynamicOffset = false,
		.minBufferBindingSize = 0,
		.multisampled = false,
		.viewDimension = wgpu::TextureViewDimension::Undefined,
		.textureComponentType = wgpu::TextureComponentType::Float,
		.storageTextureFormat = wgpu::TextureFormat::Undefined
	};
}

wgpu::BindGroupEntry ver::Sampler::GetEntryDesc() const noexcept
{
	return
	{
		.binding = slot,
		.buffer = nullptr,
		.offset = 0,
		.size = 0,
		.sampler = sampler,
		.textureView = nullptr,
	};
}
