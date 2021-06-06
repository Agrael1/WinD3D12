#include "pch.h"
#include "Texture.h"

using namespace ver;

ver::Texture::Texture(const Graphics& gfx, std::string_view path, uint32_t bindingslot)
	:name(path)
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
	slot = bindingslot;
}

Foundation::IAsyncAction 
ver::Texture::MakeAsync(Texture& tex, const Graphics& gfx, std::string path, uint32_t bindingslot)
{
	tex.name = path;
	SurfaceLoader sl;
	co_await sl.LoadTextureAsync(gfx, tex.name);

	wgpu::TextureDescriptor tdesc
	{
		.nextInChain = nullptr,
		.label = nullptr,
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
	tex.texture = GetDevice(gfx).CreateTexture(&tdesc);
	tex.fullsize = sl.GetFullSize();

	wgpu::TextureCopyView tcv
	{
		.nextInChain = nullptr,
		.texture = tex.texture,
		.mipLevel = 0,
		.origin = wgpu::Origin3D{},
		.aspect = wgpu::TextureAspect::All
	};

	for (; tcv.mipLevel < tdesc.mipLevelCount; tcv.mipLevel++)
	{
		auto mip = sl.GetImageDesc(tcv.mipLevel);
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

	tex.slot = bindingslot;
}
