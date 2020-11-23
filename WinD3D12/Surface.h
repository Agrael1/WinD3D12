#pragma once
#include <DirectXTex.h>
#include "Texture.h"
#include "FileReadWrite.h"

namespace ver
{
	class SurfaceLoader
	{
	public:
		winrt::Windows::Foundation::IAsyncAction
			LoadTextureAsync(const ver::Graphics& gfx, std::string_view tex_name, Texture* out);
		void LoadTexture(const ver::Graphics& gfx, std::string_view tex_name, Texture* out);
	public:
		UINT GetWidth()const noexcept;
		UINT GetHeight()const noexcept;
		UINT GetStride()const noexcept;
		bool UsesAlpha()const noexcept;
		uint8_t* GetBufferPtr()const noexcept;
	private:
		DirectX::ScratchImage image;
		static BasicReaderWriter loader;
		static constexpr DXGI_FORMAT format = DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
	};
}
