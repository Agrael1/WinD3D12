#include <memory>
#include <vector>
#include "SolidSphere.h"


using namespace ver;

SolidSphere::SolidSphere(const Graphics& gfx, float radius, DirectX::XMFLOAT4 xcolor)
	:color(gfx, { wgpu::ShaderStage::Fragment, &colorConst, sizeof(colorConst), 1 }),
	transforms(gfx),
	colorConst{ xcolor }
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
	iBuffer.emplace(gfx, std::span<const uint16_t>(a.indices));

	BindGroup bg{ gfx, bindGroup };
	bg.BindResource(color);
	bg.BindResource(transforms);

	Pipeline pipe{ gfx };
	pipe.BindPixelShader(*rps);
	pipe.BindVertexShader(*rvs);
	pipe.BindVertexLayout(vl);
	pipe.SetBindGroup(bg);
	pipeline = pipe.CookPipeline();
}

void ver::SolidSphere::SetPos(DirectX::XMFLOAT3 xpos) noexcept
{
	pos = xpos;
}

void ver::SolidSphere::Step(const Graphics& gfx, float) noexcept
{
	transforms.Update(gfx, DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z));
}
