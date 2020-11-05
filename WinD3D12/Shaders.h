#pragma once
#include "Codex.h"
#include "ShaderPair.h"
#include <fmt/printf.h>

namespace ver
{
	class Shader : public Bindable
	{
	public:
		Shader(const Graphics& gfx, std::span<const uint32_t> xshader, std::string_view tag, std::string_view entry)
		{
			Create(gfx, xshader, tag, entry);
		}
		Shader(const Graphics& gfx, ShaderPair pair, ShaderPair::Type ty)
		{
			std::span<const uint32_t> xshader = pair.Get(ty);
			std::string_view tag = pair.GetTag(ty);
			std::string_view entry = pair.GetEntry(ty);

			Create(gfx, xshader, tag, entry);
		}
	private:
		void Create(const Graphics& gfx, std::span<const uint32_t> xshader, std::string_view tag, std::string_view entry)
		{
			wgpu::ShaderModuleSPIRVDescriptor spirvDesc;
			spirvDesc.codeSize = static_cast<uint32_t>(xshader.size());
			spirvDesc.code = xshader.data();

			wgpu::ShaderModuleDescriptor descriptor;
			descriptor.nextInChain = &spirvDesc;

			desc.Module = GetDevice(gfx).CreateShaderModule(&descriptor);
			desc.nextInChain = nullptr;
			desc.entryPoint = entry.data();
		}
	public:
		operator wgpu::ShaderModule()
		{
			return desc.Module;
		}
		const wgpu::ProgrammableStageDescriptor& GetStageDescriptor()const noexcept
		{
			return desc;
		}
	public:
		static std::string GenerateUID(ShaderPair pair, ShaderPair::Type t)noexcept
		{
			std::string_view tag = pair.GetTag(t), entry = pair.GetEntry(t);
			return fmt::sprintf("%s-%s", tag, entry);
		}
		static std::string GenerateUID(std::span<const uint32_t> xshader, std::string_view tag, std::string_view entry = "main")noexcept
		{
			return fmt::sprintf("%s-%s", tag, entry);
		}
		[[nodiscard]] static auto Resolve(const Graphics& gfx, ShaderPair pair, ShaderPair::Type t)noexcept
		{
			return Codex::Resolve<Shader>(gfx, pair, t);
		}
		[[nodiscard]] static auto Resolve(const Graphics& gfx, std::span<const uint32_t> xshader, std::string_view tag, std::string_view entry = "main")noexcept
		{
			return Codex::Resolve<Shader>(gfx, xshader, tag, entry);
		}
	private:
		wgpu::ProgrammableStageDescriptor desc{};
	};
}

