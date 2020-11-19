#pragma once
#include <vector>
#include <DirectXMath.h>
#include "DynamicVBuffer.h"

//only for 3d
class IndexedTriangleList
{
public:
	IndexedTriangleList() = default;
	IndexedTriangleList(ver::dv::VertexBuffer verts, std::vector<unsigned short> inds)
		:
		vertices(std::move(verts)),
		indices(std::move(inds))
	{
		assert(vertices.Size() > 2);
		assert(indices.size() % 3 == 0);
	}
public:
	void Deform(DirectX::FXMMATRIX matrix)noexcept;
	void CalcNormalsIndependentFlat()noexcept;
public:
	ver::dv::VertexBuffer vertices;
	std::vector<unsigned short> indices;
};