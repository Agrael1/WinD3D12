#pragma once
#include "Bindable.h"
#include <span>

namespace ver
{
	class Shader : public Bindable
	{
	public:
		Shader(Graphics& gfx, std::span<uint32_t> xshader)
		{
			wgpu::ShaderModuleSPIRVDescriptor spirvDesc;
			spirvDesc.codeSize = static_cast<uint32_t>(xshader.size());
			spirvDesc.code = xshader.data();

			wgpu::ShaderModuleDescriptor descriptor;
			descriptor.nextInChain = &spirvDesc;

			shader = GetDevice(gfx).CreateShaderModule(&descriptor);
		}
	private:
		wgpu::ShaderModule shader;
	};
}

