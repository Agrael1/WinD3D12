#include "pch.h"
#include "Shaders.h"
#include "FileReadWrite.h"

using namespace ver;

ver::Shader::Shader(const Graphics& gfx, std::string shader, std::string_view entry)
{
	std::filesystem::path path{ Codex::shader_folder };
	path /= shader + Codex::shader_extension.data();
	BasicReaderWriter read;
	auto data = read.ReadData(winrt::to_hstring(path.string().c_str()));
	Create(gfx, std::span<const uint32_t>{ (const uint32_t*)data.data(), data.size() / 4 }, path.string(), entry);
}

concurrency::task<std::shared_ptr<Shader>>
ver::Shader::MakeAsync(const Graphics& gfx, std::string shader, std::string_view entry)
{
	std::filesystem::path path{ Codex::shader_folder };
	path /= shader + Codex::shader_extension.data();
	BasicReaderWriter read;
	auto data = co_await read.ReadDataAsync(winrt::to_hstring(path.string().c_str()));
	co_return std::make_shared<Shader>(gfx, std::span<const uint32_t>{ (const uint32_t*)data.data(), data.Length()/4 }, path.string(), entry);
}
