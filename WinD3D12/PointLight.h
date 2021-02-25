#pragma once
#include "SolidSphere.h"

namespace ver
{
	class PointLight
	{

	public:
		PointLight(const Graphics& gfx, float radius = 0.5f);
		void SpawnControlWindow()noexcept
		{

		}
		void Reset()noexcept;
		void Submit(wgpu::RenderPassEncoder& pass) const noexcept;
		void Bind(Graphics& gfx, DirectX::FXMMATRIX view)const noexcept;
	private:
		struct PointLightCBuf
		{
			DirectX::XMFLOAT3A pos{ 0.0f,0.0f,0.5f };
			DirectX::XMFLOAT3A ambient{ 0.05f,0.05f,0.05f };
			DirectX::XMFLOAT3 diffuse{ 1.0f,1.0f,1.0f };
			float diffuseIntensity{ 1.0f };
			float attConst{ .5f };
			float attLin{ 0.045f };
			float attQuad{ 0.0075f };
		}cbData;
	private:
		mutable SolidSphere mesh;
		mutable PixelConstantBuffer<PointLightCBuf> cbuf;
		wgpu::BindGroup bindGroup;
	};
}

