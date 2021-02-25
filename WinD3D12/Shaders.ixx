module;
#include <string>
#include <span>
#include <memory>
#include "DawnAdapter.h"
export module Shaders;
import ShaderPair;
import Codex;


export namespace ver
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
		void Create(const Graphics& gfx, std::span<const uint32_t> xshader, std::string_view, std::string_view entry)
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
			std::string x{ tag };
			x.push_back('-');
			return x += entry;
		}
		static std::string GenerateUID(std::span<const uint32_t> xshader, std::string_view tag, std::string_view entry = "main")noexcept
		{
			(void)xshader;
			std::string x{ tag };
			x.push_back('-');
			return x += entry;
		}
		[[nodiscard]] 
		static std::shared_ptr<Shader> Resolve(const Graphics& gfx, ShaderPair pair, ShaderPair::Type t)noexcept
		{
			return Codex::Resolve<Shader>(gfx, pair, t);
		}
		[[nodiscard]] 
		static std::shared_ptr<Shader> Resolve(const Graphics& gfx, std::span<const uint32_t> xshader, std::string_view tag, std::string_view entry = "main")noexcept
		{
			return Codex::Resolve<Shader>(gfx, xshader, tag, entry);
		}
	private:
		wgpu::ProgrammableStageDescriptor desc{};
	};


}