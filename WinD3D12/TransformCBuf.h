#pragma once
#include "ConstantBuffers.h"

namespace ver
{
	class TransformCbuf : public ConstantBuffer
	{
	protected:
		struct Transforms
		{
			DirectX::XMMATRIX modelView = DirectX::XMMatrixIdentity();
			DirectX::XMMATRIX modelViewProj = DirectX::XMMatrixIdentity();
		}tr{};
	public:
		TransformCbuf(const Graphics& gfx, uint32_t slot = 0u)
			:ConstantBuffer(gfx, { wgpu::ShaderStage::Vertex, &tr, sizeof(tr), slot })
		{

		}
	public:
		void Update(const Graphics& gfx, DirectX::XMMATRIX transform) noexcept
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
	};
}
