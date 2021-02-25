#pragma once
#include <DirectXTex.h>

namespace ver
{
	class Graphics;

	class SurfaceLoader
	{
		struct MipDescriptor
		{
			uint32_t      width;
			uint32_t      height;
			size_t      rowPitch;
			size_t      dataSize;
			uint8_t* pixels;
		};
	public:
		void LoadTexture(const ver::Graphics& gfx, std::string_view tex_name);
	public:
		UINT GetWidth()const noexcept;
		UINT GetHeight()const noexcept;
		UINT GetStride()const noexcept;
		uint32_t GetMipCount()const noexcept;
		bool UsesAlpha()const noexcept;
		size_t GetFullSize()const noexcept;
		uint8_t* GetImage(size_t mip)const noexcept;
		MipDescriptor GetImageDesc(size_t mip)const noexcept;
	private:
		DirectX::ScratchImage image;
		static class BasicReaderWriter loader;
		static constexpr DXGI_FORMAT format = DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
	};
}
