#pragma once
#include "BindGroup.h"
#include "Shaders.h"
#include <optional>

namespace ver
{
	class Pipeline : public Bindable
	{
	public:
		Pipeline(const Graphics& gfx)
			:gfx(gfx)
		{
		}
	public:
		void BindVertexLayout(const ver::dv::VertexLayout& vb)
		{
			pVL = &vb;
		}
		void BindVertexShader(const Shader& vs)
		{
			desc.vertexStage = vs.GetStageDescriptor();
		}
		void BindPixelShader(const Shader& ps)
		{
			PSDesc.emplace(ps.GetStageDescriptor());
		}
		[[nodiscard]]wgpu::RenderPipeline CookPipeline(const BindGroup& bg)const noexcept
		{
			// pipeline layout (used by the render pipeline, released after its creation)
			wgpu::PipelineLayoutDescriptor layoutDesc = {};
			layoutDesc.bindGroupLayoutCount = 1;
			layoutDesc.bindGroupLayouts = &bg.CookLayout();

			// begin pipeline set-up
			desc.layout = GetDevice(gfx).CreatePipelineLayout(&layoutDesc);

			if (PSDesc)
				desc.fragmentStage = &PSDesc.value();

			if (pVL)
			{
				wgpu::VertexBufferLayoutDescriptor vertDesc = {};
				vertDesc.arrayStride = pVL->Size();
				vertDesc.attributeCount = uint32_t(pVL->GetElementCount());
				vertDesc.attributes = pVL->GetDescs().data();
				wgpu::VertexStateDescriptor vertState = {};
				vertState.vertexBufferCount = 1;
				vertState.vertexBuffers = &vertDesc;
				desc.vertexState = &vertState;
			}

			desc.primitiveTopology = wgpu::PrimitiveTopology::TriangleList;

			desc.sampleCount = 1;

			// describe blend
			wgpu::BlendDescriptor blendDesc = {};
			blendDesc.operation = wgpu::BlendOperation::Add;
			blendDesc.srcFactor = wgpu::BlendFactor::SrcAlpha;
			blendDesc.dstFactor = wgpu::BlendFactor::OneMinusSrcAlpha;
			wgpu::ColorStateDescriptor colorDesc = {};
			colorDesc.format = VFactory::GetSwapChainFormat();
			colorDesc.alphaBlend = blendDesc;
			colorDesc.colorBlend = blendDesc;
			colorDesc.writeMask = wgpu::ColorWriteMask::All;

			desc.colorStateCount = 1;
			desc.colorStates = &colorDesc;

			desc.sampleMask = 0xFFFFFFFF; // <-- Note: this currently causes Emscripten to fail (sampleMask ends up as -1, which trips an assert)

			return GetDevice(gfx).CreateRenderPipeline(&desc);
		}
	private:
		const ver::dv::VertexLayout* pVL;
		std::optional<wgpu::ProgrammableStageDescriptor> PSDesc;
		mutable wgpu::RenderPipelineDescriptor desc = {};
		const Graphics& gfx;
	};
}
