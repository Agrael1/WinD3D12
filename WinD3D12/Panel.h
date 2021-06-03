#pragma once
#include "Drawable.h"
#include "Pipeline.h"
#include "TransformCBuf.h"
#include "PhongDif.h"
#include "Sampler.h"
#include "PhongLightLayout.h"
#include "Texture.h"

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

			x[0].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 0.0f, 0.0f });
			x[1].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 0.0f, 1.0f });
			x[2].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 1.0f, 1.0f });
			x[3].SetAttributeByIndex(2, DirectX::XMFLOAT2{ 1.0f, 0.0f });
			return x;
		}
	public:
		Panel(const Graphics& gfx)
			:pixelBuf(gfx, colorConst, 2),
			cbuf(gfx)
		{
			std::shared_ptr<Shader> rvs = Shader::Resolve(gfx, PhongDif, ShaderPair::Type::Vertex);
			std::shared_ptr<Shader> rps = Shader::Resolve(gfx, PhongDif, ShaderPair::Type::Pixel);

			constexpr dv::VertexLayout vl
			{ {
				VType::Position3D,
				VType::Normal,
				VType::Texture2D
			} };

			constexpr uint16_t indxData[] = {
				0, 2, 1, 0, 3, 2
			};

			auto a = Panel::MakeVertices(vl);
			vBuffer.emplace(gfx, a.data());
			iBuffer.emplace(gfx, indxData);

			Texture t(gfx, "Assets\\Textures\\brick_wall_diffuse.jpg", 3);
			Sampler sample(gfx, 4);
	

			BindGroup xbg1{ gfx, bindGroup };
			xbg1.BindResource(cbuf);
			xbg1.BindResource(pixelBuf);
			xbg1.BindResource(t);
			xbg1.BindResource(sample);

			Pipeline pipe{ gfx };
			pipe.BindPixelShader(*rps);
			pipe.BindVertexShader(*rvs);
			pipe.BindVertexLayout(vl);
			pipe.SetBindGroup(xbg1);
			pipe.SetRawLayout(PhongLightLayout::Get(gfx));
			pipeline = pipe.CookPipeline();
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
			DirectX::XMFLOAT3A materialColor{ 1.0f, 0.0f, 0.0f };
			DirectX::XMFLOAT3 specularColor{ 1.0f, 0.0f, 0.0f };
			float specularWeight;
			float specularGloss;
		}colorConst;
		PixelConstantBuffer<PSColorConstant> pixelBuf;
		TransformCbuf cbuf;
		float rotDeg = 0.0f;
	};
}

