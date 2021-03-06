#include "IndexedTriangleList.h"

void IndexedTriangleList::Deform(DirectX::FXMMATRIX matrix) noexcept
{
	using Type = ver::dv::VertexLayout::ElementType;
	for (int i = 0; i < vertices.Size(); i++)
	{
		auto& pos = vertices[i].Attr<Type::Position3D>();
		DirectX::XMStoreFloat3(
			&pos,
			DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&pos), matrix)
		);
	}
}

void IndexedTriangleList::CalcNormalsIndependentFlat() noexcept
{
	using namespace DirectX;
	using Type = ver::dv::VertexLayout::ElementType;
	if (!vertices.GetLayout().Has(Type::Normal)) //if there's no normals -> go away
		return;

	for (size_t i = 0; i < indices.size(); i += 3)
	{
		auto v0 = vertices[indices[i]];
		auto v1 = vertices[indices[i + 1]];
		auto v2 = vertices[indices[i + 2]];
		const auto p0 = XMLoadFloat3(&v0.Attr<Type::Position3D>());
		const auto p1 = XMLoadFloat3(&v1.Attr<Type::Position3D>());
		const auto p2 = XMLoadFloat3(&v2.Attr<Type::Position3D>());

		const auto n = XMVector3Normalize(XMVector3Cross((p1 - p0), (p2 - p0)));

		XMStoreFloat3(&v0.Attr<Type::Normal>(), n);
		XMStoreFloat3(&v1.Attr<Type::Normal>(), n);
		XMStoreFloat3(&v2.Attr<Type::Normal>(), n);
	}
}
