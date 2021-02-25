#pragma once
#include "Sphere.h"
#include "SolidColor.h"

import Drawable;


namespace ver
{
	class SolidSphere : public Drawable
	{
	public:
		SolidSphere(const Graphics& gfx, float radius, DirectX::XMFLOAT4 xcolor = { 1.0f,1.0f,0.0f,1.0f });
	public:
		void SetPos(DirectX::XMFLOAT3 xpos)noexcept;
		void Step(const Graphics& gfx, float) noexcept override;
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