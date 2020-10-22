#pragma once
#include "DynamicVertex.h"
#include "AlignedAllocator.h"
#include <vector>

namespace ver::dv
{
	template<VertexLayout::ElementType type>
	concept has_code_map = requires{VertexLayout::Map<type>::code != "!INV!"; };

	template<typename T, VertexLayout::ElementType type>
	concept is_map_type = requires{std::is_same_v<typename VertexLayout::Map<type>::SysType, T>; };

	class Vertex
	{
	private:
		template<VertexLayout::ElementType type> requires has_code_map<type>
		struct AttributeSetting
		{
			template<typename T> requires is_map_type<type, T>
			static constexpr void Exec(Vertex* pVertex, uint8_t* pAttribute, T&& val) noexcept
			{
				*reinterpret_cast<T*>(pAttribute) = val;
			}
		};
	public:
		template <VertexLayout::ElementType Type> requires has_code_map<Type>
		constexpr auto& Attr()const noexcept
		{
			auto pAttribute = pData + layout->Resolve(Type).GetOffset();
			return *reinterpret_cast<typename VertexLayout::Map<Type>::SysType*>(pAttribute);
		}
		template<typename T>
		constexpr void SetAttributeByIndex(size_t i, T&& val) noexcept //strengthened already
		{
			const auto element = layout.ResolveByIndex(i);
			auto pAttribute = pData + element.GetOffset();
			VertexLayout::Bridge<AttributeSetting>(
				element.GetType(), this, pAttribute, std::forward<T>(val)
				);
		}
	public:
		constexpr Vertex(uint8_t* pData, const VertexLayout* layout) : pData(pData), layout(layout) {};
		constexpr Vertex(const Vertex& in)
			:pData(in.pData),layout(in.layout)
		{

		}
	private:
		template<typename First, typename ...Rest>
		constexpr void SetAttributeByIndex(size_t i, First&& first, Rest&&... rest)noexcept 
		{
			SetAttributeByIndex(i, std::forward<First>(first));
			SetAttributeByIndex(i + 1, std::forward<Rest>(rest)...);
		}
	private:
		uint8_t* pData = nullptr;
		const VertexLayout* layout;
	};


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
		constexpr Vertex Back()noexcept
		{
			return Vertex{ buffer.data() + buffer.size() - layout.Size(), &layout };
		}
		constexpr Vertex Front()noexcept
		{
			return Vertex{ buffer.data(), &layout };
		}
		constexpr Vertex operator[](size_t i)noexcept
		{
			return Vertex{ buffer.data() + layout.Size() * i,&layout };
		}

		constexpr const Vertex Back() const noexcept
		{
			return const_cast<VertexBuffer*>(this)->Back();
		}
		constexpr const Vertex Front() const noexcept
		{
			return const_cast<VertexBuffer*>(this)->Front();
		}
		constexpr const Vertex operator[](size_t i) const noexcept
		{
			return const_cast<VertexBuffer&>(*this)[i];
		}
	private:
		VertexLayout layout;
		std::vector<uint8_t, AlignedAllocator<uint8_t>> buffer;
	};
	


}

