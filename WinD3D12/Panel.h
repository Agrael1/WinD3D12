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

			

			BindGroup bg{ gfx, bindGroup };
			//bg.BindResource(ccbuf);
			bg.BindResource(cbuf);
			bg.BindResource(pixelBuf);
			bg.BindResource(ccbuf);

			std::array<wgpu::BindGroupLayoutEntry,3> cbufa = 
			{ cbuf.GetLayout(),pixelBuf.GetLayout(), ccbuf.GetLayout() };
			std::array <wgpu::BindGroupEntry, 3> cbufb = 
			{ cbuf.GetEntryDesc(),pixelBuf.GetEntryDesc(), ccbuf.GetEntryDesc() };

			wgpu::BindGroupLayoutDescriptor bglDesc = {};
			bglDesc.entryCount = 3;
			bglDesc.entries = cbufa.data();

			wgpu::BindGroupLayout bgl = GetDevice(gfx).CreateBindGroupLayout(&bglDesc);

			wgpu::BindGroupDescriptor bgDesc = {};
			bgDesc.layout = bgl;
			bgDesc.entryCount = 3;
			bgDesc.entries = cbufb.data();

			bg2 = GetDevice(gfx).CreateBindGroup(&bgDesc);

			/// //////////////////////////////////////////

			std::array<wgpu::BindGroupLayout, 2>  bgls = 
			{ bgl , bg.CookLayout() };

			wgpu::RenderPipelineDescriptor desc = {};

			wgpu::PipelineLayoutDescriptor layoutDesc = {};
			layoutDesc.bindGroupLayoutCount = 2;
			layoutDesc.bindGroupLayouts = bgls.data();

			// begin pipeline set-up
			desc.layout = GetDevice(gfx).CreatePipelineLayout(&layoutDesc);

			desc.fragmentStage = &rps->GetStageDescriptor();
			desc.vertexStage = rvs->GetStageDescriptor();
			wgpu::VertexBufferLayoutDescriptor vertDesc = {};
			vertDesc.arrayStride = vl.Size();
			vertDesc.attributeCount = uint32_t(vl.GetElementCount());
			vertDesc.attributes = vl.GetDescs().data();
			wgpu::VertexStateDescriptor vertState = {};
			vertState.vertexBufferCount = 1;
			vertState.vertexBuffers = &vertDesc;
			desc.vertexState = &vertState;

			desc.primitiveTopology = wgpu::PrimitiveTopology::TriangleList;

			desc.sampleCount = 1;

			// describe blend
			wgpu::BlendDescriptor blendDesc = {};
			blendDesc.operation = wgpu::BlendOperation::Add;
			blendDesc.srcFactor = wgpu::BlendFactor::SrcAlpha;
			blendDesc.dstFactor = wgpu::BlendFactor::OneMinusSrcAlpha;
			wgpu::ColorStateDescriptor colorDesc = {};
			colorDesc.format = gfx.GetSwapChainFormat();
			colorDesc.alphaBlend = blendDesc;
			colorDesc.colorBlend = blendDesc;
			colorDesc.writeMask = wgpu::ColorWriteMask::All;

			desc.colorStateCount = 1;
			desc.colorStates = &colorDesc;

			desc.sampleMask = 0xFFFFFFFF; // <-- Note: this currently causes Emscripten to fail (sampleMask ends up as -1, which trips an assert)

			pipeline =  GetDevice(gfx).CreateRenderPipeline(&desc);

			//BindGroup xbg2{ gfx, bg2 };
			//xbg2.BindResource(cbuf);
			//xbg2.BindResource(pixelBuf);
			//xbg2.BindResource(ccbuf);
			//xbg2.BindResource(ccbuf);
			//bg.BindResource(cbuf);
			//bg.BindResource(pixelBuf);
			//bg.BindResource(t);
			//bg.BindResource(sample);



			//Pipeline pipe{ gfx };
			//pipe.BindPixelShader(*rps);
			//pipe.BindVertexShader(*rvs);
			//pipe.BindVertexLayout(vl);
			//pipeline = pipe.CookPipeline(bg2);
		}
		virtual void Submit(wgpu::RenderPassEncoder& pass)const noexcept override
		{
			pass.SetPipeline(pipeline);

			pass.SetBindGroup(0, bindGroup, 0, 0);
			//pass.SetBindGroup(1, bg2, 0, 0);

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

