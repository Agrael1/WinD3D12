#include "pch.h"
#include "Surface.h"
#include <chrono>


namespace ver
{
	BasicReaderWriter ver::SurfaceLoader::loader;

	UINT SurfaceLoader::GetWidth()const noexcept
	{
		return (UINT)image.GetMetadata().width;
	}
	UINT SurfaceLoader::GetHeight()const noexcept
	{
		return (UINT)image.GetMetadata().height;
	}
	UINT SurfaceLoader::GetStride()const noexcept
	{
		return (UINT)image.GetPixelsSize() / GetHeight();
	}
	uint32_t SurfaceLoader::GetMipCount() const noexcept
	{
		return uint32_t(image.GetImageCount());
	}
	bool SurfaceLoader::UsesAlpha()const noexcept
	{
		return !image.IsAlphaAllOpaque();
	}
	size_t SurfaceLoader::GetFullSize() const noexcept
	{
		return image.GetPixelsSize();
	}
	uint8_t* SurfaceLoader::GetImage(size_t mip) const noexcept
	{
		return image.GetImage(mip, 0, 0)->pixels;
	}

	SurfaceLoader::MipDescriptor SurfaceLoader::GetImageDesc(size_t mip) const noexcept
	{
		auto x = image.GetImage(mip, 0, 0);

		return
		{
			.width = uint32_t(x->width),
			.height = uint32_t(x->height),
			.rowPitch = x->rowPitch,
			.dataSize = x->slicePitch,
			.pixels = x->pixels
		};
	}
	
	void SurfaceLoader::LoadTexture(const ver::Graphics& gfx, std::string_view tex_name)
	{
		auto textureData = loader.ReadData(winrt::to_hstring(tex_name.data()));
		HRESULT hr = DirectX::LoadFromWICMemory(textureData.data(), textureData.size(),
			DirectX::WIC_FLAGS_NONE, nullptr, image);

		winrt::check_hresult(hr);//remove

		if (image.GetImage(0, 0, 0)->format != format)
		{
			DirectX::ScratchImage converted;
			hr = DirectX::Convert(
				*image.GetImage(0, 0, 0),
				format,
				DirectX::TEX_FILTER_DEFAULT,
				DirectX::TEX_THRESHOLD_DEFAULT,
				converted
			);

			winrt::check_hresult(hr);//remove
			image = std::move(converted);
		}
		DirectX::ScratchImage mipped;
		DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), 
			image.GetMetadata(), DirectX::TEX_FILTER_DEFAULT, 0, mipped);
		image = std::move(mipped);
	}
	Windows::Foundation::IAsyncAction SurfaceLoader::LoadTextureAsync(const ver::Graphics& gfx, std::string_view tex_name)
	{
		auto textureData = co_await loader.ReadDataAsync(winrt::to_hstring(tex_name.data()));
		HRESULT hr = DirectX::LoadFromWICMemory(textureData.data(), textureData.Length(),
			DirectX::WIC_FLAGS_NONE, nullptr, image);

		winrt::check_hresult(hr);//remove

		if (image.GetImage(0, 0, 0)->format != format)
		{
			DirectX::ScratchImage converted;
			hr = DirectX::Convert(
				*image.GetImage(0, 0, 0),
				format,
				DirectX::TEX_FILTER_DEFAULT,
				DirectX::TEX_THRESHOLD_DEFAULT,
				converted
			);

			winrt::check_hresult(hr);//remove
			image = std::move(converted);
		}
		DirectX::ScratchImage mipped;
		DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(),
			image.GetMetadata(), DirectX::TEX_FILTER_DEFAULT, 0, mipped);
		image = std::move(mipped);
	}
}
