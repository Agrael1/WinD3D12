#pragma once
import BindGroup;
import Shaders;

namespace ver
{
	class Pipeline : public Bindable
	{
	public:
		Pipeline(const Graphics& gfx);
	public:
		void BindVertexLayout(const ver::dv::VertexLayout& vb);
		void BindVertexShader(const Shader& vs);
		void BindPixelShader(const Shader& ps);
		void SetBindGroup(const BindGroup& bg);
		void SetRawLayout(const wgpu::BindGroupLayout& in);

		[[nodiscard]] 
		wgpu::RenderPipeline CookPipeline()const noexcept;
	private:
		const ver::dv::VertexLayout* pVL;
		std::optional<wgpu::ProgrammableStageDescriptor> PSDesc;
		std::array<wgpu::BindGroupLayout, 4> bindGroupLayouts;
 		mutable wgpu::RenderPipelineDescriptor desc = {};
		const Graphics& gfx;
		uint32_t counter = 0;
	};
}
