#pragma once
#include "Drawable.h"
#include "Pipeline.h"
#include "ColorBlend.h"

namespace ver
{
	class Triangle : public Drawable
	{
	public:
		static dv::VertexBuffer MakeVertices(dv::VertexLayout layout)
		{
			ver::dv::VertexBuffer x{ std::move(layout),3 };
			x[0].SetAttributeByIndex(0, DirectX::XMFLOAT3{ -0.8f, -0.8f, 1.0f });
			x[0].SetAttributeByIndex(1, DirectX::XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f });

			x[1].SetAttributeByIndex(0, DirectX::XMFLOAT3{ 0.8f, -0.8f , 1.0f });
			x[1].SetAttributeByIndex(1, DirectX::XMFLOAT4{ 0.0f, 1.0f, 0.0f, 1.0f });

			x[2].SetAttributeByIndex(0, DirectX::XMFLOAT3{ -0.0f, 0.8f, 1.0f });
			x[2].SetAttributeByIndex(1, DirectX::XMFLOAT4{ 1.0f, 0.0f, 0.0f, 1.0f });

			return x;
		};
	public:
		Triangle(const Graphics& gfx)
			:uRotBuf(gfx, { wgpu::ShaderStage::Vertex, &transformCBuf, sizeof(transformCBuf), 0 })
		{
			std::shared_ptr<Shader> rvs = Shader::Resolve(gfx, ColorBlend, ShaderPair::Type::Vertex);
			std::shared_ptr<Shader> rps = Shader::Resolve(gfx, ColorBlend, ShaderPair::Type::Pixel);

			constexpr dv::VertexLayout vl
			{ {
				VType::Position3D,
				VType::Float4Color
			} };

			constexpr uint16_t indxData[] = {
				0, 1, 2, 0
			};

			auto a = Triangle::MakeVertices(vl);
			vBuffer.emplace(gfx, a.data());
			iBuffer.emplace(gfx, indxData, 4, wgpu::IndexFormat::Uint16);

			BindGroup bg{ gfx, bindGroup };
			bg.BindResource(uRotBuf);

			Pipeline pipe{ gfx };
			pipe.BindPixelShader(*rps);
			pipe.BindVertexShader(*rvs);
			pipe.BindVertexLayout(vl);
			pipeline = pipe.CookPipeline(bg);
		}
	public:
		void Step(const Graphics& gfx, float time)override
		{
			rotDeg += 0.05f * time;
			transformCBuf.transform = DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, rotDeg);
			uRotBuf.Update(gfx, &transformCBuf, sizeof(transformCBuf));
		}
	private:
		struct
		{
			DirectX::XMMATRIX transform;
		}transformCBuf;
		ConstantBuffer uRotBuf;
		float rotDeg = 0.0f;
	};

}

