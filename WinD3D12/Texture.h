#pragma once
#include "Bindable.h"

namespace ver
{
	class Texture : public Bindable
	{
	public:
		Texture()noexcept = default;
		Texture(const Graphics& gfx, wgpu::TextureDescriptor& desc, const uint8_t* data, size_t dataSize)
			:
			texview {
				.nextInChain = nullptr,
				.texture = GetDevice(gfx).CreateTexture(&desc),
				.mipLevel = 0,
				.origin{0,0,0},
				.aspect = wgpu::TextureAspect::All
			}
			
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
			GetQueue(gfx).WriteTexture(&texview, data, dataSize, nullptr, nullptr);
		}
	private:
		const wgpu::TextureCopyView texview;
		std::string name;
	};
}