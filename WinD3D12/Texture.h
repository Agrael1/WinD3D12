#pragma once
#include "Bindable.h"

namespace ver
{
	class Texture : public Bindable
	{
	public:
		Texture(const Graphics& gfx)
		{
			wgpu::TextureDescriptor desc;
			desc.dimension = wgpu::TextureDimension::e2D;
			//desc.format = wgpu::TextureFormat::
			tex = GetDevice(gfx).CreateTexture(&desc);
		}

	private:
		wgpu::Texture tex;
	};
}