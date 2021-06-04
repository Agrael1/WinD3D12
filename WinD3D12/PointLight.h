#pragma once
#include "SolidSphere.h"
#include "PhongLightLayout.h"

namespace ver
{
	class PointLight
	{

	public:
		PointLight(const Graphics& gfx, float radius = 0.5f)
			:mesh(gfx, radius), cbuf(gfx, 1)
		{
			BindGroup bg{PhongLightLayout::Get(gfx)};
			bg.BindResource(cbuf);
			Reset();
			bindGroup = bg.MakeBindGroup(gfx);
		}
		void SpawnControlWindow()noexcept
		{

		}
		void Reset()noexcept
		{
			cbData = {
				{ 0.0f,0.0f,0.5f },
				{ 0.05f,0.05f,0.05f },
				{ 1.0f,1.0f,1.0f },
				1.0f,
				1.0f,
				0.045f,
				0.0075f,
			};
		}
		void Submit(wgpu::RenderPassEncoder& pass) const noexcept
		{
			pass.SetBindGroup(1, bindGroup, 0, 0);
			mesh.Submit(pass);
		}
		void Bind(Graphics& gfx, DirectX::FXMMATRIX view)const noexcept
		{
			auto dataCopy = cbData;
			const auto pos = DirectX::XMLoadFloat3(&cbData.pos);
			DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, view));
			cbuf.Update(gfx, dataCopy);

			mesh.SetPos(cbData.pos);
			mesh.Step(gfx, 0);
		}
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

