#pragma once
#include <DirectXPackedVector.h>
#include <assimp/scene.h>
#include <dawn/webgpu_cpp.h>
#include <array>
#include <span>

#define DVTX_ELEMENT_AI_EXTRACTOR(member) static SysType Extract( const aiMesh& mesh, size_t i ) noexcept {return *reinterpret_cast<const SysType*>(&mesh.member[i]);}

#define LAYOUT_ELEMENT_TYPES \
	X( Invalid )\
	X( Position2D ) \
	X( Position3D ) \
	X( Texture2D ) \
	X( Normal ) \
	X( Tangent ) \
	X( Bitangent ) \
	X( Float3Color ) \
	X( Float4Color ) \
	X( RGBAColor ) 

namespace ver::dv
{
	constexpr const size_t maxAttributes = 16;

	class VertexLayout
	{
	public:
		enum class ElementType : uint16_t
		{
		#define X(el) el,
			LAYOUT_ELEMENT_TYPES
		#undef X
		};
	public:
		template<ElementType> struct Map;
		template<> struct Map<ElementType::Position2D>
		{
			using SysType = DirectX::XMFLOAT2;
			static constexpr wgpu::VertexFormat dxgiFormat = wgpu::VertexFormat::Float2;
			static constexpr const char* semantic = "Position";
			static constexpr const char* code = "P2";
			DVTX_ELEMENT_AI_EXTRACTOR(mVertices)
		};
		template<> struct Map<ElementType::Position3D>
		{
			using SysType = DirectX::XMFLOAT3;
			static constexpr wgpu::VertexFormat dxgiFormat = wgpu::VertexFormat::Float3;
			static constexpr const char* semantic = "Position";
			static constexpr const char* code = "P3";
			DVTX_ELEMENT_AI_EXTRACTOR(mVertices)
		};
		template<> struct Map<ElementType::Texture2D>
		{
			using SysType = DirectX::XMFLOAT2;
			static constexpr wgpu::VertexFormat dxgiFormat = wgpu::VertexFormat::Float2;
			static constexpr const char* semantic = "Texcoord";
			static constexpr const char* code = "T2";
			DVTX_ELEMENT_AI_EXTRACTOR(mTextureCoords[0])
		};
		template<> struct Map<ElementType::Normal>
		{
			using SysType = DirectX::XMFLOAT3;
			static constexpr wgpu::VertexFormat dxgiFormat = wgpu::VertexFormat::Float3;
			static constexpr const char* semantic = "Normal";
			static constexpr const char* code = "N";
			//DVTX_ELEMENT_AI_EXTRACTOR(mNormals)
			static SysType Extract(const aiMesh& mesh, size_t i) noexcept {
				using namespace DirectX;
				SysType a;
				DirectX::XMStoreFloat3(&a, DirectX::XMVectorZero() - 
					DirectX::XMLoadFloat3(reinterpret_cast<const SysType*>(&mesh.mNormals[i])));
				return a; 
			}
		};
		template<> struct Map<ElementType::Tangent>
		{
			using SysType = DirectX::XMFLOAT3;
			static constexpr wgpu::VertexFormat dxgiFormat = wgpu::VertexFormat::Float3;
			static constexpr const char* semantic = "Tangent";
			static constexpr const char* code = "Nt";
			DVTX_ELEMENT_AI_EXTRACTOR(mTangents)
		};
		template<> struct Map<ElementType::Bitangent>
		{
			using SysType = DirectX::XMFLOAT3;
			static constexpr wgpu::VertexFormat dxgiFormat = wgpu::VertexFormat::Float3;
			static constexpr const char* semantic = "Bitangent";
			static constexpr const char* code = "Nb";
			DVTX_ELEMENT_AI_EXTRACTOR(mBitangents)
		};
		template<> struct Map<ElementType::Float3Color>
		{
			using SysType = DirectX::XMFLOAT3;
			static constexpr wgpu::VertexFormat dxgiFormat = wgpu::VertexFormat::Float3;
			static constexpr const char* semantic = "Color";
			static constexpr const char* code = "C3";
			DVTX_ELEMENT_AI_EXTRACTOR(mColors[0])
		};
		template<> struct Map<ElementType::Float4Color>
		{
			using SysType = DirectX::XMFLOAT4;
			static constexpr wgpu::VertexFormat dxgiFormat = wgpu::VertexFormat::Float4;
			static constexpr const char* semantic = "Color";
			static constexpr const char* code = "C4";
			DVTX_ELEMENT_AI_EXTRACTOR(mColors[0])
		};
		template<> struct Map<ElementType::RGBAColor>
		{
			using SysType = DirectX::PackedVector::XMCOLOR;
			static constexpr wgpu::VertexFormat dxgiFormat = wgpu::VertexFormat::UChar4Norm;
			static constexpr const char* semantic = "Color";
			static constexpr const char* code = "C8";
			DVTX_ELEMENT_AI_EXTRACTOR(mColors[0])
		};
		template<> struct Map<ElementType::Invalid>
		{
			using SysType = long double;
			static constexpr wgpu::VertexFormat dxgiFormat = wgpu::VertexFormat::UChar2;
			static constexpr const char* semantic = "!INVALID!";
			static constexpr const char* code = "!INV!";
			DVTX_ELEMENT_AI_EXTRACTOR(mFaces)
		};
	public:
		template<template<ElementType> class F, typename... Args>
		static constexpr auto Bridge(ElementType type, Args&&... args) noexcept
		{
			switch (type)
			{
			#define X(el) case ElementType::el: return F<ElementType::el>::Exec( std::forward<Args>( args )... );
				LAYOUT_ELEMENT_TYPES
			#undef X
			}
			assert("Invalid element type" && false);
			return F<ElementType::Invalid>::Exec(std::forward<Args>(args)...);
		}
	public:
		template<VertexLayout::ElementType type>
		struct SysSizeLookup
		{
			static constexpr auto Exec() noexcept
			{
				return sizeof(VertexLayout::Map<type>::SysType);
			}
		};
		template<VertexLayout::ElementType type>
		struct CodeLookup
		{
			static constexpr auto Exec() noexcept
			{
				return VertexLayout::Map<type>::code;
			}
		};
		template<VertexLayout::ElementType type>
		struct DescGenerate
		{
			static constexpr wgpu::VertexAttributeDescriptor Exec(size_t offset) noexcept
			{
				return {
					VertexLayout::Map<type>::dxgiFormat,
					offset,0
				};
			}
		};
	public:
		class Element
		{
		public:
			constexpr Element() = default;
			constexpr Element(ElementType type, size_t offset)
				: type(type), offset(uint16_t(offset))
			{
			}
		public:
			constexpr bool operator==(const Element& other)const //for equality check
			{
				return other.type == type;
			}
			constexpr operator bool()
			{
				return IsValid();
			}
		public:
			constexpr size_t GetOffsetAfter()const noexcept
			{
				return offset + Size();
			}
			constexpr size_t GetOffset()const noexcept
			{
				return offset;
			}
			constexpr size_t Size()const noexcept
			{
				return SizeOf(type);
			}
			constexpr ElementType GetType()const noexcept
			{
				return type;
			}
			constexpr const char* GetCode() const noexcept
			{
				return Bridge<CodeLookup>(type);
			}
			constexpr bool IsValid()const noexcept
			{
				return type != ElementType::Invalid;
			}
		public:
			static constexpr size_t SizeOf(ElementType type)noexcept
			{
				return Bridge<SysSizeLookup>(type);
			}
		public:
			constexpr wgpu::VertexAttributeDescriptor GetIntermediateDesc() const noexcept
			{
				return Bridge<DescGenerate>(type, GetOffset());
			}
		private:
			ElementType type = ElementType::Invalid;
			uint16_t offset = 0;
		};
		struct VertexAttributeDesc :wgpu::VertexAttributeDescriptor
		{
			constexpr VertexAttributeDesc()
				:wgpu::VertexAttributeDescriptor()
			{

			}
			constexpr VertexAttributeDesc(wgpu::VertexAttributeDescriptor in)
				: wgpu::VertexAttributeDescriptor(in)
			{

			}
		};
	public:
		constexpr VertexLayout()
			:attributes({})
		{

		}
		constexpr VertexLayout(std::initializer_list<ElementType> elements)
			:attributes({})
		{
			size_t max = elements.size() > maxAttributes ? maxAttributes : elements.size();
			auto* x = attributes.data();
			
			for (size_t i = 0; i < max; i++)
			{
				if (!Has(elements.begin()[i]))
				{
					Element el = { elements.begin()[i], Size() };
					*x++ = el;
					current++;
				}
			}
		}
	public:
		constexpr size_t Size()const noexcept
		{
			return current == 0 ? 0u : attributes[current - 1].GetOffsetAfter();
		}
		constexpr bool Has(ElementType el)const noexcept
		{
			for (size_t i = 0; i < maxAttributes; i++)
			{
				if (attributes[i].GetType() == el)
					return true;
			}
			return false;
		}
		constexpr auto GetDescs()const noexcept
		{
			std::array<VertexAttributeDesc, maxAttributes> attrDescs;
			auto* y = attrDescs.data();
			for (size_t i = 0; i < current; i++)
			{
				*y = attributes[i].GetIntermediateDesc();
				y->shaderLocation = uint32_t(i);
				y++;
			}
			return attrDescs;
		}
		constexpr void Add(ElementType el)
		{
			if(current != maxAttributes)
				if (!Has(el))
				{
					attributes[current++] = { el, Size() };
				}	
		}
		constexpr size_t GetElementCount() const noexcept
		{
			return current;
		}
		constexpr Element ResolveByIndex(size_t index) const noexcept
		{
			return attributes[index];
		}
		constexpr Element Resolve(ElementType el)const noexcept
		{
			for (size_t i = 0; i < maxAttributes; i++)
			{
				if (attributes[i].GetType() == el)
					return attributes[i];
			}
			return {};
		}
	private:
		std::array<Element, maxAttributes> attributes;
		size_t current = 0;
	};
}

 namespace ver
{
	using VType = ver::dv::VertexLayout::ElementType;
}

