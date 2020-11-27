#pragma once
#include "Drawable.h"
#include "Pipeline.h"
#include "TransformCBuf.h"
#include "Phong.h"
#include "Surface.h"
#include "Sampler.h"

namespace ver
{
	class Panel : public Drawable, public Bindable
	{
	public:
		static dv::VertexBuffer MakeVertices(dv::VertexLayout layout)
		{
			ver::dv::VertexBuffer x{ std::move(layout), 4 };
			x[0].SetAttributeByIndex(0, DirectX::XMFLOAT3{ -0.5f, -0.5f, 1.0f });
			x[1].SetAttributeByIndex(0, DirectX::XMFLOAT3{ -0.5f,  0.5f, 1.0f });
			x[2].SetAttributeByIndex(0, DirectX::XMFLOAT3{  0.5f,  0.5f, 1.0f });
			x[3].SetAttributeByIndex(0, DirectX::XMFLOAT3{  0.5f, -0.5f, 1.0f });

			x[0].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 0.0f, -1.0f });
			x[1].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 0.0f, -1.0f });
			x[2].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 0.0f, -1.0f });
			x[3].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 0.0f, -1.0f });

			//x[0].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 0.0f, 0.0f });
			//x[1].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 0.0f, 1.0f });
			//x[2].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 1.0f, 1.0f });
			//x[3].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 1.0f, 0.0f });
			return x;
		}
	public:
		Panel(const Graphics& gfx)
			:pixelBuf(gfx, colorConst, 2),
			cbuf(gfx), ccbuf(gfx, rce, 1)
		{
			std::shared_ptr<Shader> rvs = Shader::Resolve(gfx, Phong, ShaderPair::Type::Vertex);
			std::shared_ptr<Shader> rps = Shader::Resolve(gfx, Phong, ShaderPair::Type::Pixel);

			constexpr dv::VertexLayout vl
			{ {
				VType::Position3D,
				VType::Normal
			} };

			constexpr uint16_t indxData[] = {
				0, 2, 1, 0, 3, 2
			};

			auto a = Panel::MakeVertices(vl);
			vBuffer.emplace(gfx, a.data());
			iBuffer.emplace(gfx, indxData);

			//Texture t;
			//SurfaceLoader sl;
			//sl.LoadTexture(gfx, "Assets\\Textures\\brick_wall_diffuse.jpg", &t, 0);
			//Sampler sample(gfx);

			

			BindGroup xbg2{ gfx, bindGroup };
			xbg2.BindResource(cbuf);
			xbg2.BindResource(pixelBuf);

			BindGroup xbg1{ gfx, bg2 };
			xbg1.BindResource(ccbuf);

			//bg.BindResource(cbuf);
			//bg.BindResource(pixelBuf);
			//bg.BindResource(t);
			//bg.BindResource(sample);



			Pipeline pipe{ gfx };
			pipe.BindPixelShader(*rps);
			pipe.BindVertexShader(*rvs);
			pipe.BindVertexLayout(vl);
			pipeline = pipe.CookPipeline(xbg1, xbg2);
		}
		virtual void Submit(wgpu::RenderPassEncoder& pass)const noexcept override
		{
			pass.SetPipeline(pipeline);

			pass.SetBindGroup(1, bindGroup, 0, 0);
			pass.SetBindGroup(0, bg2, 0, 0);

			pass.SetVertexBuffer(0, *vBuffer, 0, 0);
			pass.SetIndexBufferWithFormat(*iBuffer, iBuffer->GetFormat(), 0, 0);
			pass.DrawIndexed(uint32_t(iBuffer->GetCount()));
		}
	public:
		void Step(const Graphics& gfx, float time)override
		{
			rotDeg += 0.05f * time;
			cbuf.Update(gfx, DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, rotDeg));
		}
	private:
		struct PSColorConstant
		{
			DirectX::XMFLOAT3A materialColor{ 1.0f, 0.0f, 0.0f };
			DirectX::XMFLOAT3 specularColor{ 1.0f, 0.0f, 0.0f };
			float specularWeight;
			float specularGloss;
		}colorConst;
		struct PointLightCBuf
		{
			DirectX::XMFLOAT3A pos{ 0.0f,0.0f,0.5f };
			DirectX::XMFLOAT3A ambient{ 0.05f,0.05f,0.05f };
			DirectX::XMFLOAT3 diffuse{1.0f,1.0f,1.0f};
			float diffuseIntensity{ 1.0f };
			float attConst{ .5f };
			float attLin{ 0.045f };
			float attQuad{ 0.0075f };
		}rce;
		PixelConstantBuffer<PSColorConstant> pixelBuf;
		wgpu::BindGroup bg2;
		PixelConstantBuffer<PointLightCBuf> ccbuf;
		TransformCbuf cbuf;
		float rotDeg = 0.0f;
	};
}

