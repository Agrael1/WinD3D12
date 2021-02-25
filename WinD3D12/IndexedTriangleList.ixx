module;
#include <vector>
#include <cassert>
export module IndexedTriangleList;
export import Dynamic;

//only for 3d
export class IndexedTriangleList
{
public:
	IndexedTriangleList() = default;
	IndexedTriangleList(ver::dv::VertexBuffer verts, std::vector<unsigned short> inds);
public:
	void Deform(DirectX::FXMMATRIX matrix)noexcept;
	void CalcNormalsIndependentFlat()noexcept;
public:
	ver::dv::VertexBuffer vertices;
	std::vector<unsigned short> indices;
};