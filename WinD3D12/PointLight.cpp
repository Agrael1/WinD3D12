#include "PointLight.h"

using namespace ver;

ver::PointLight::PointLight(const Graphics& gfx, float radius)
	:mesh(gfx, radius), cbuf(gfx, 1)
{
	BindGroup bg{ gfx, bindGroup, PhongLightLayout::Get(gfx) };
	bg.BindResource(cbuf);
	Reset();
}

void ver::PointLight::Reset() noexcept
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

void ver::PointLight::Submit(wgpu::RenderPassEncoder& pass) const noexcept
{
	pass.SetBindGroup(1, bindGroup, 0, 0);
	mesh.Submit(pass);
}

void ver::PointLight::Bind(Graphics& gfx, DirectX::FXMMATRIX view) const noexcept
{
	auto dataCopy = cbData;
	const auto pos = DirectX::XMLoadFloat3(&cbData.pos);
	DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, view));
	cbuf.Update(gfx, dataCopy);

	mesh.SetPos(cbData.pos);
	mesh.Step(gfx, 0);
}
