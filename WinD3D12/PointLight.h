#pragma once
#include "SolidSphere.h"

namespace ver
{
	class PointLight
	{
	public:
		PointLight(const Graphics& gfx, float radius = 0.5f)
			:mesh(gfx, radius), cbuf(gfx)
		{
			BindGroup bg{ gfx, bindGroup };
			bg.BindResource(cbuf);

			Pipeline pipe{ gfx };
			pipeline = pipe.CookPipeline(bg);
			Reset();
		}
		void SpawnControlWindow()noexcept
		{

		}
		void Reset()noexcept
		{
			cbData = {
				{ 0.0f,0.0f,2.5f },
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
			//pass.SetPipeline(pipeline);
			//pass.SetBindGroup(0, bindGroup, 0, 0);
			//pass.DrawIndexed(0);
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
			DirectX::XMFLOAT3A pos;
			DirectX::XMFLOAT3A ambient;
			DirectX::XMFLOAT3 diffuse;
			float diffuseIntensity;
			float attConst;
			float attLin;
			float attQuad;
		};
	private:
		PointLightCBuf cbData;
		mutable SolidSphere mesh;
		mutable PixelConstantBuffer<PointLightCBuf> cbuf;
		wgpu::BindGroup bindGroup;
		wgpu::RenderPipeline pipeline;
	};
}

