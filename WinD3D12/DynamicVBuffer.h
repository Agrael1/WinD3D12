#pragma once
#include "DynamicVertex.h"
#include "AlignedAllocator.h"
#include <vector>

namespace ver::dv
{


	class VertexBuffer
	{
	public:
		VertexBuffer(VertexLayout&& layout, size_t size = 0);
		VertexBuffer(VertexLayout&& layout, const aiMesh& mesh);
	public:
		//	const VertexLayout& GetLayout() const noexcept;
		//	size_t Count()const noxnd;
		//	size_t Size() const noxnd;
		//	const unsigned char* data()const noxnd;

		//	template<typename ...Params>
		//	void EmplaceBack(Params&&... params) noxnd
		//	{
		//		assert(sizeof...(params) == layout.GetElementCount() && "Param count doesn't match number of vertex elements");
		//		buffer.resize(buffer.size() + layout.Size());
		//		Back().SetAttributeByIndex(0u, std::forward<Params>(params)...);
		//	}
		void Resize(size_t size)
		{
			buffer.resize(layout.Size() * size);
		}
		//	Vertex Back() noxnd;
		//	Vertex Front() noxnd;
		//	Vertex operator[](size_t i)noxnd;

		//	ConstVertex Back() const noxnd;
		//	ConstVertex Front() const noxnd;
		//	ConstVertex operator[](size_t i) const noxnd
		//	{
		//		return const_cast<VertexBuffer&>(*this)[i];
		//	}
	private:
		VertexLayout layout;
		std::vector<uint8_t, AlignedAllocator<uint8_t>> buffer;
	};
}

