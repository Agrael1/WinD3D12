#pragma once
#include "Bindable.h"
#include <string_view>
#include <span>

namespace ver
{
	class Shader : public Bindable
	{
	public:
		Shader(const Graphics& gfx, std::span<uint32_t> xshader, std::string_view entry = "main")
		{
			wgpu::ShaderModuleSPIRVDescriptor spirvDesc;
			spirvDesc.codeSize = static_cast<uint32_t>(xshader.size());
			spirvDesc.code = xshader.data();

			wgpu::ShaderModuleDescriptor descriptor;
			descriptor.nextInChain = &spirvDesc;

			shader = GetDevice(gfx).CreateShaderModule(&descriptor);

			desc.nextInChain = nullptr;
			desc.Module = shader;
			desc.entryPoint = entry.data();
		}
	public:
		operator wgpu::ShaderModule()
		{
			return shader;
		}
		const wgpu::ProgrammableStageDescriptor& GetStageDescriptor()const noexcept
		{
			return desc;
		}
	private:
		wgpu::ShaderModule shader;
		wgpu::ProgrammableStageDescriptor desc;
	};
}

