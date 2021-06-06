#pragma once
#include "Drawable.h"
#include "Pipeline.h"
#include "TransformCBuf.h"
#include "PhongDif.h"
#include "Sampler.h"
#include "PhongLightLayout.h"
#include "Texture.h"

#include "Model.h"

namespace ver
{
	class Panel : public Drawable, public Bindable
	{
	public:
		static dv::VertexBuffer MakeVertices(dv::VertexLayout layout)
		{
			ver::dv::VertexBuffer x{ std::move(layout), 4 };
			x[0].SetAttributeByIndex(0, DirectX::XMFLOAT3{ -2.5f, -2.5f, 1.0f });
			x[1].SetAttributeByIndex(0, DirectX::XMFLOAT3{ -2.5f,  2.5f, 1.0f });
			x[2].SetAttributeByIndex(0, DirectX::XMFLOAT3{  2.5f,  2.5f, 1.0f });
			x[3].SetAttributeByIndex(0, DirectX::XMFLOAT3{  2.5f, -2.5f, 1.0f });

			x[0].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 0.0f, -1.0f });
			x[1].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 0.0f, -1.0f });
			x[2].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 0.0f, -1.0f });
			x[3].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 0.0f, -1.0f });

			x[0].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 0.0f, 0.0f });
			x[1].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 0.0f, 1.0f });
			x[2].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 1.0f, 1.0f });
			x[3].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 1.0f, 0.0f });

			x[0].SetAttributeByIndex(3, DirectX::XMFLOAT3{ 1.0f, 0.0f, 0.0f });
			x[1].SetAttributeByIndex(3, DirectX::XMFLOAT3{ 1.0f, 0.0f, 0.0f });
			x[2].SetAttributeByIndex(3, DirectX::XMFLOAT3{ 1.0f, 0.0f, 0.0f });
			x[3].SetAttributeByIndex(3, DirectX::XMFLOAT3{ 1.0f, 0.0f, 0.0f });

			x[0].SetAttributeByIndex(4, DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f });
			x[1].SetAttributeByIndex(4, DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f });
			x[2].SetAttributeByIndex(4, DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f });
			x[3].SetAttributeByIndex(4, DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f });
			return x;
		}
	public:
		Panel(const Graphics& gfx)
			:pixelBuf(gfx, colorConst, 2),
			cbuf(gfx)
		{
			auto rvs = Shader::Resolve(gfx, "PhongDifNrm.vs", "main");
			auto rps = Shader::Resolve(gfx, "PhongDifNrm.ps", "main");

			constexpr dv::VertexLayout vl
			{ {
				VType::Position3D,
				VType::Normal,
				VType::Texture2D,
				VType::Tangent,
				VType::Bitangent,
			} };

			constexpr uint16_t indxData[] = {
				0, 2, 1, 0, 3, 2
			};

			auto a = Panel::MakeVertices(vl);
			vBuffer.emplace(gfx, a.data());
			iBuffer.emplace(gfx, indxData);

			Texture t1(gfx, "Assets\\Textures\\brick_wall_diffuse.jpg", 3);
			Texture t2(gfx, "Assets\\Textures\\brick_wall_normal.jpg", 4);
			Sampler sample(gfx, 5);
	

			BindGroup xbg1;
			xbg1.BindResource(cbuf);
			xbg1.BindResource(pixelBuf);
			xbg1.BindResource(t1);
			xbg1.BindResource(t2);
			xbg1.BindResource(sample);
			bindGroup = xbg1.MakeBindGroup(gfx);

			Pipeline pipe;
			pipe.BindRasterLayout(RasterizerState(gfx, false));
			pipe.BindPixelShader(*rps);
			pipe.BindVertexShader(*rvs);
			pipe.BindVertexLayout(vl);
			pipe.AppendBindGroup(xbg1.CookLayout(gfx));
			pipe.AppendBindGroup(PhongLightLayout::Get(gfx));
			pipeline = pipe.CookPipeline(gfx);
		}
		virtual void Submit(wgpu::RenderPassEncoder& pass)const noexcept override
		{
			pass.SetPipeline(pipeline);
			pass.SetBindGroup(0, bindGroup, 0, 0);

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
			DirectX::XMFLOAT3 specularColor{ 0.18f,0.18f,0.18f };
			float specularWeight = 1.0f;
			float specularGloss = 18.0f;
			int use = 1;
			float nmw = 1.0f;
		}colorConst;
		PixelConstantBuffer<PSColorConstant> pixelBuf;
		TransformCbuf cbuf;
		float rotDeg = 0.0f;
	};
}

