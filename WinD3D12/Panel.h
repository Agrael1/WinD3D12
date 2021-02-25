#pragma once
#include <memory>
#include "PhongDif.h"


import Drawable;
//class Drawable {};

namespace ver
{
	class Panel : public Drawable
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
		Panel(const Graphics& gfx);
	public:
		void Step(const Graphics& gfx, float time)override;
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

