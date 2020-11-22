#pragma once
#include "DynamicVertex.h"
#include "AlignedAllocator.h"
#include <vector>


namespace ver::dv
{
	template<VertexLayout::ElementType type>
	concept has_code_map = requires{VertexLayout::Map<type>::code != "!INV!"; };

	template<VertexLayout::ElementType type, typename T>
	concept is_map_type = requires{  std::is_same_v<typename VertexLayout::Map<type>::SysType, T>; };

	class VertexBuffer;

	class Vertex
	{
		friend ver::dv::VertexBuffer;
	private:
		template<VertexLayout::ElementType type> requires has_code_map<type>
		struct AttributeSetting
		{
			template<typename T> requires is_map_type<type, T>
			static constexpr void Exec(uint8_t* pAttribute, T&& val) noexcept
			{
				*reinterpret_cast<T*>(pAttribute) = val;
			}
		};
	public:
		template <VertexLayout::ElementType Type> requires has_code_map<Type>
		constexpr auto& Attr()const noexcept
		{
			auto pAttribute = pData + layout.Resolve(Type).GetOffset();
			return *reinterpret_cast<typename VertexLayout::Map<Type>::SysType*>(pAttribute);
		}
		template<typename T>
		constexpr void SetAttributeByIndex(size_t i, T&& val) noexcept //strengthened already
		{
			const auto element = layout.ResolveByIndex(i);
			if (element.IsValid())
			{
				auto pAttribute = pData + element.GetOffset();
				VertexLayout::Bridge<AttributeSetting>(
					element.GetType(), pAttribute, std::forward<T>(val)
					);
			}
		}
	private:
		constexpr Vertex(uint8_t* pData, const VertexLayout& layout) : pData(pData), layout(layout) {};
	private:
		template<typename First, typename ...Rest>
		constexpr void SetAttributeByIndex(size_t i, First&& first, Rest&&... rest)noexcept 
		{
			SetAttributeByIndex(i, std::forward<First>(first));
			SetAttributeByIndex(i + 1, std::forward<Rest>(rest)...);
		}
	private:
		uint8_t* pData = nullptr;
		const VertexLayout& layout;
	};
	template<VertexLayout::ElementType type>
	struct AttributeAiMeshFill
	{
		static constexpr void Exec(VertexBuffer* pBuf, const aiMesh& mesh) noexcept
		{
			for (auto end = mesh.mNumVertices, i = 0u; i < end; i++)
			{
				(*pBuf)[i].Attr<type>() = VertexLayout::Map<type>::Extract(mesh, i);
			}
		}
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(VertexLayout layout, size_t size = 0)
			:layout(std::move(layout))
		{
			if (size) Resize(size);
		}
		VertexBuffer(VertexLayout layout, const aiMesh& mesh)
			: layout(layout)
		{
			Resize(mesh.mNumVertices);
			for (size_t i = 0, end = layout.GetElementCount(); i < end; i++)
			{
				VertexLayout::Bridge<AttributeAiMeshFill>(layout.ResolveByIndex(i).GetType(), this, mesh);
			}
		}
	public:
		constexpr const VertexLayout& GetLayout() const noexcept
		{
			return layout;
		}
		size_t Size()const noexcept
		{
			return buffer.size() / layout.Size();
		}
		size_t SizeBytes() const noexcept
		{
			return buffer.size();
		}
		std::span<const uint8_t> data()const noexcept
		{
			return { buffer };
		}

		void Resize(size_t size)
		{
			buffer.resize(layout.Size() * size);
		}
		constexpr Vertex Back()noexcept
		{
			return Vertex{ buffer.data() + buffer.size() - layout.Size(), layout };
		}
		constexpr Vertex Front()noexcept
		{
			return Vertex{ buffer.data(), layout };
		}
		constexpr Vertex operator[](size_t i)noexcept
		{
			return Vertex{ buffer.data() + layout.Size() * i,layout };
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

