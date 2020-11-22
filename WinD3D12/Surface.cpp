#include "pch.h"
#include "Surface.h"




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
	bool SurfaceLoader::UsesAlpha()const noexcept
	{
		return !image.IsAlphaAllOpaque();
	}
	void* SurfaceLoader::GetBufferPtr()const noexcept
	{
		return image.GetPixels();
	}
	winrt::Windows::Foundation::IAsyncAction
		SurfaceLoader::LoadTextureAsync(const ver::Graphics& gfx, std::string_view tex_name, Texture* out)
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
		std::construct_at(out, gfx);
	}
}