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

concurrency::task<std::shared_ptr<Texture>> 
ver::Texture::MakeAsync(const Graphics& gfx, std::string_view path, uint32_t bindingslot)
{
	std::shared_ptr<Texture> in = std::make_shared<Texture>();
	in->name = path;
	SurfaceLoader sl;
	co_await sl.LoadTextureAsync(gfx, path);

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
	in->texture = GetDevice(gfx).CreateTexture(&tdesc);
	in->fullsize = sl.GetFullSize();

	for (uint32_t i = 0; i < tdesc.mipLevelCount; i++)
	{
		wgpu::TextureCopyView tcv
		{
			.nextInChain = nullptr,
			.texture = in->texture,
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

	in->slot = bindingslot;
	co_return std::move(in);
}
