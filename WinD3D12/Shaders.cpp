#include "pch.h"
#include "Shaders.h"
#include "FileReadWrite.h"

using namespace ver;

concurrency::task<std::shared_ptr<Shader>> 
ver::Shader::MakeAsync(const Graphics& gfx, std::filesystem::path shader, std::string_view entry)
{
	BasicReaderWriter read;
	auto data = co_await read.ReadDataAsync(shader.wstring().c_str());
	co_return std::make_shared<Shader>(gfx, std::span<const uint32_t>{ (const uint32_t*)data.data(), data.Length()/4 }, shader.string(), entry);
}
