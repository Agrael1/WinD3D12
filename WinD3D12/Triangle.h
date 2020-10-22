#pragma once
#include "DynamicVBuffer.h"
#include <optional>

class Triangle
{
public:
	static ver::dv::VertexBuffer MakeVertices(ver::dv::VertexLayout layout)
	{
		ver::dv::VertexBuffer x{ std::move(layout),3 };
		x[0].SetAttributeByIndex(0, DirectX::XMFLOAT2{ -0.8f, -0.8f });
		x[0].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 0.0f, 1.0f });

		x[1].SetAttributeByIndex(0, DirectX::XMFLOAT2{ 0.8f, -0.8f });
		x[1].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f });

		x[2].SetAttributeByIndex(0, DirectX::XMFLOAT2{ -0.0f, 0.8f });
		x[2].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 1.0f, 0.0f, 0.0f });

		return x;
	};
};
