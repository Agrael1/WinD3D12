#pragma once
#include "Bindable.h"

namespace ver
{
	class Texture : public Bindable
	{
	public:
		Texture()noexcept = default;
		Texture(const Graphics& gfx)
		{
			wgpu::TextureDescriptor desc;
			desc.dimension = wgpu::TextureDimension::e2D;
			//desc.format = wgpu::TextureFormat::
			tex = GetDevice(gfx).CreateTexture(&desc);
		}
	public:
		std::string_view GetName()const noexcept
		{
			return name;
		}
	private:
		wgpu::Texture tex;
		std::string name;
	};
}