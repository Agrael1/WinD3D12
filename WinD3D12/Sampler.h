#pragma once
#include "ConstantBinding.h"

namespace ver
{
	class Sampler : public XConstantBinding<Sampler>
	{
	public:
		Sampler(const Graphics& gfx, uint32_t xslot = 0, wgpu::FilterMode type = wgpu::FilterMode::Linear)
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
			slot = xslot;
		}
	public:
		wgpu::BindGroupLayoutEntry GetLayout()const noexcept
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
		wgpu::BindGroupEntry GetEntryDesc()const noexcept
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
	private:
		wgpu::Sampler sampler;
	};
}