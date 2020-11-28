#pragma once
#include "ConstantBinding.h"

namespace ver
{
	class Texture : public XConstantBinding<Texture>
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
		Texture(const Graphics& gfx, const Descriptor& desc)
			:
			texview {
				.nextInChain = nullptr,
				.texture = GetDevice(gfx).CreateTexture(&desc.desc),
				.mipLevel = 0,
				.origin{0,0,0},
				.aspect = wgpu::TextureAspect::All
			}, dimensions(desc.desc.size), stride(desc.stride), usesalpha(desc.alpha)
		{
			Write(gfx, desc.data, desc.dataSize);
			slot = desc.bindingSlot;
		}
	public:
		std::string_view GetName()const noexcept
		{
			return name;
		}
		void Write(const Graphics& gfx, const uint8_t* data, size_t dataSize)
		{
			wgpu::TextureDataLayout x
			{
				.nextInChain = nullptr,
				.offset = 0,
				.bytesPerRow = stride,
				.rowsPerImage = dimensions.height
			};
			GetQueue(gfx).WriteTexture(&texview, data, dataSize, &x, &dimensions);
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
				.size = stride*dimensions.height,
				.sampler = nullptr,
				.textureView = texview.texture.CreateView(),
			};
		}
	private:
		wgpu::TextureCopyView texview;
		wgpu::Extent3D dimensions;
		std::string name;
		uint32_t stride = 0;
		bool usesalpha = false;
	};
}