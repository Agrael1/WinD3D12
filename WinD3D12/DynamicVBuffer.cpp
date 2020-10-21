#include "DynamicVBuffer.h"

namespace ver::dv
{
	//template<VertexLayout::ElementType type>
	//struct AttributeAiMeshFill
	//{
	//	static constexpr void Exec(VertexBuffer* pBuf, const aiMesh& mesh) noxnd
	//	{
	//		for (auto end = mesh.mNumVertices, i = 0u; i < end; i++)
	//		{
	//			(*pBuf)[i].Attr<type>() = VertexLayout::Map<type>::Extract(mesh, i);
	//		}
	//	}
	//};

	VertexBuffer::VertexBuffer(VertexLayout&& layout, size_t size)
		:layout(std::move(layout))
	{
		if (size) Resize(size);
	}
	VertexBuffer::VertexBuffer(VertexLayout&& layout, const aiMesh& mesh)
		: layout(std::move(layout))
	{
		Resize(mesh.mNumVertices);
		for (size_t i = 0, end = layout.GetElementCount(); i < end; i++)
		{
			//VertexLayout::Bridge<AttributeAiMeshFill>(layout.ResolveByIndex(i).GetType(), this, mesh);
		}
	}
}

