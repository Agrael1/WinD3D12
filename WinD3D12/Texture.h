#pragma once
#include "Bindable.h"

namespace ver
{
	class Texture : public Bindable
	{
	public:
		Texture()noexcept = default;
		Texture(const Graphics& gfx, wgpu::TextureDescriptor& desc, const uint8_t* data, size_t dataSize, uint32_t stride, bool alpha)
			:
			texview {
				.nextInChain = nullptr,
				.texture = GetDevice(gfx).CreateTexture(&desc),
				.mipLevel = 0,
				.origin{0,0,0},
				.aspect = wgpu::TextureAspect::All
			}, dimensions(desc.size), stride(uint32_t(stride)), usesalpha(alpha)
			
		{
			Write(gfx, data, dataSize);
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
	private:
		wgpu::TextureCopyView texview;
		wgpu::Extent3D dimensions;
		std::string name;
		uint32_t stride = 0;
		bool usesalpha = false;
	};
}