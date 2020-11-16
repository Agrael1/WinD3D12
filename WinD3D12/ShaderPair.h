#pragma once
#include <string_view>
#include <span>

struct ShaderPair
{
public:
	enum class Type
	{
		Vertex,
		Pixel
	};
public:
	constexpr std::span<const uint32_t> Get(Type t)
	{
		switch (t)
		{
		case Type::Pixel:
			return PSShaderBytecode;
		case Type::Vertex:
			return VSShaderBytecode;
		}
		return{};
	}
	constexpr std::string_view GetTag(Type t)
	{
		switch (t)
		{
		case Type::Pixel:
			return PSShaderTag;
		case Type::Vertex:
			return VSShaderTag;
		}
		return{};
	}
	constexpr std::string_view GetEntry(Type t)
	{
		switch (t)
		{
		case Type::Pixel:
			return PSShaderEntry;
		case Type::Vertex:
			return VSShaderEntry;
		}
		return{};
	}
public:
	std::string_view VSShaderTag;
	std::string_view PSShaderTag;
	std::string_view VSShaderEntry;
	std::string_view PSShaderEntry;
	std::span<const uint32_t> VSShaderBytecode;
	std::span<const uint32_t> PSShaderBytecode;
};