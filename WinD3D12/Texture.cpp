module;
#include <SurfaceLoader.h>
#include "DawnAdapter.h"
module Texture;

ver::Texture::Texture(const Graphics& gfx, std::string_view path, uint32_t bindingslot)
	:name(path), slot(bindingslot)
{
	SurfaceLoader sl;
	sl.LoadTexture(gfx, path);

	wgpu::TextureDescriptor tdesc
	{
		.nextInChain = nullptr,
		.label = name.c_str(),
		.usage = wgpu::TextureUsage::CopyDst | wgpu::TextureUsage::Sampled,
		.dimension = wgpu::TextureDimension::e2D,
		.size = {
			.width = sl.GetWidth(),
			.height = sl.GetHeight(),
			.depth = 1
	},
		.format = wgpu::TextureFormat::BGRA8Unorm,
		.mipLevelCount = sl.GetMipCount(),
		.sampleCount = 1,
	};
	texture = GetDevice(gfx).CreateTexture(&tdesc);
	fullsize = sl.GetFullSize();

	for (uint32_t i = 0; i < tdesc.mipLevelCount; i++)
	{
		wgpu::TextureCopyView tcv
		{
			.nextInChain = nullptr,
			.texture = texture,
			.mipLevel = i,
			.origin = wgpu::Origin3D{},
			.aspect = wgpu::TextureAspect::All
		};
		auto mip = sl.GetImageDesc(i);
		wgpu::TextureDataLayout tdl
		{
			.nextInChain = nullptr,
			.offset = 0,
			.bytesPerRow = uint32_t(mip.rowPitch),
			.rowsPerImage = mip.height,
		};
		wgpu::Extent3D dims
		{
			.width = mip.width,
			.height = mip.height,
			.depth = 1
		};
		GetQueue(gfx).WriteTexture(&tcv, mip.pixels, mip.dataSize, &tdl, &dims);
	}
}

std::string_view ver::Texture::GetName() const noexcept
{
	return name;
}
bool ver::Texture::UsesAlpha() const noexcept
{
	return usesalpha;
}
wgpu::BindGroupLayoutEntry ver::Texture::GetLayout() const noexcept
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
wgpu::BindGroupEntry ver::Texture::GetEntryDesc() const noexcept
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
