#pragma once
#include "ConstantBinding.h"
#include <SurfaceLoader.h>

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
	public:
		std::string_view GetName()const noexcept;
		bool UsesAlpha()const noexcept;
		wgpu::BindGroupLayoutEntry GetLayout()const noexcept;
		wgpu::BindGroupEntry GetEntryDesc()const noexcept;
	private:
		wgpu::Texture texture;
		size_t fullsize = 0;
		std::string name;
		uint32_t slot;
		bool usesalpha = false;
	};
}