#pragma once
#include "ConstantBinding.h"
#include "Surface.h"
#include <pplawait.h>

namespace ver
{
	class Texture : public ConstantBinding<Texture>
	{
	public:
		struct Descriptor
		{
			wgpu::TextureDescriptor desc;
			const uint8_t* data;
			size_t dataSize; 
			uint32_t stride; 
			uint32_t bindingSlot;
			bool alpha;
		};
	public:
		Texture()noexcept = default;
		Texture(const Graphics& gfx, std::string_view path, uint32_t bindingslot);
		static concurrency::task<std::shared_ptr<Texture>>
			MakeAsync(const Graphics& gfx, std::string_view path, uint32_t bindingslot);
	public:
		std::string_view GetName()const noexcept
		{
			return name;
		}
		bool UsesAlpha()const noexcept
		{
			return usesalpha;
		}
	public:
		wgpu::BindGroupLayoutEntry GetLayout()const noexcept
		{
			return
			{
				.binding = slot,
				.visibility = wgpu::ShaderStage::Fragment,
				.type = wgpu::BindingType::SampledTexture,
				.hasDynamicOffset = false,
				.minBufferBindingSize = 0,
				.multisampled = false,
				.viewDimension = wgpu::TextureViewDimension::e2D,
				.textureComponentType = wgpu::TextureComponentType::Float,
				.storageTextureFormat = wgpu::TextureFormat::BGRA8Unorm
			};
		}
		wgpu::BindGroupEntry GetEntryDesc()const noexcept
		{
			return
			{
				.binding = slot,
				.buffer = nullptr,
				.offset = 0,
				.size = fullsize,
				.sampler = nullptr,
				.textureView = texture.CreateView(),
			};
		}
	private:
		wgpu::Texture texture;
		size_t fullsize = 0;
		std::string name;
		uint32_t slot;
		bool usesalpha = false;
	};
}