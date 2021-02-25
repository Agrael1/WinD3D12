#include "Panel.h"

using namespace ver;

Panel::Panel(const Graphics& gfx)
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


void Panel::Step(const Graphics& gfx, float time)
{
	rotDeg += 0.05f * time;
	cbuf.Update(gfx, DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, rotDeg));
}