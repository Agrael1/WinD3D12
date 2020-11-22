#pragma once
#include "Drawable.h"
#include "Sphere.h"
#include "Pipeline.h"
#include "SolidColor.h"
#include "TransformCBuf.h"
#include "DynamicConstant.h"

namespace ver
{
	class SolidSphere : public Drawable
	{
	public:
		SolidSphere(const Graphics& gfx, float radius, DirectX::XMFLOAT4 xcolor = { 1.0f,1.0f,0.0f,1.0f })
			:color(gfx, { wgpu::ShaderStage::Fragment, &colorConst, sizeof(colorConst), 1 }),
			transforms(gfx),
			colorConst{xcolor}
		{
			std::shared_ptr<Shader> rvs = Shader::Resolve(gfx, SolidColor, ShaderPair::Type::Vertex);
			std::shared_ptr<Shader> rps = Shader::Resolve(gfx, SolidColor, ShaderPair::Type::Pixel);

			constexpr dv::VertexLayout vl
			{ {
				VType::Position3D
			} };

			auto a = Sphere::Make(vl);
			a.Deform(DirectX::XMMatrixScalingFromVector(DirectX::XMVectorReplicate(radius)));
			vBuffer.emplace(gfx, a.vertices.data());
			iBuffer.emplace(gfx, a.indices);

			BindGroup bg{ gfx, bindGroup };
			bg.BindResource(color);
			bg.BindResource(transforms);

			Pipeline pipe{ gfx };
			pipe.BindPixelShader(*rps);
			pipe.BindVertexShader(*rvs);
			pipe.BindVertexLayout(vl);
			pipeline = pipe.CookPipeline(bg);
		}
	public:
		void SetPos(DirectX::XMFLOAT3 xpos)noexcept
		{
			pos = xpos;
		}
		void Step(const Graphics& gfx, float) noexcept override
		{
			transforms.Update(gfx, DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z));
		}
	private:
		DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
		struct PSColorConstant
		{
			alignas(16)DirectX::XMFLOAT4 color;
		}colorConst;
		ConstantBuffer color;
		TransformCbuf transforms;
	};
}