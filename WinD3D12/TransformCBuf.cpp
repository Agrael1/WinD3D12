module;
#include <cstdint>
module TransformCBuf;

using namespace ver;

TransformCbuf::TransformCbuf(const Graphics& gfx, uint32_t slot)
	:ConstantBuffer(gfx, { wgpu::ShaderStage::Vertex, &tr, sizeof(tr), slot })
{

}

void ver::TransformCbuf::Update(const Graphics& gfx, DirectX::XMMATRIX transform) noexcept
{
	const auto modelView = transform * gfx.GetCamera();
	tr = {
		DirectX::XMMatrixTranspose(modelView),
		DirectX::XMMatrixTranspose(
			modelView *
			gfx.GetProjection()
		)
	};
	ConstantBuffer::Update(gfx, &tr, sizeof(tr));
}
