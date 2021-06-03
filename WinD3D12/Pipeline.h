#pragma once
#include "BindGroup.h"
#include "Shaders.h"
#include "RasterizerState.h"
#include <optional>

namespace ver
{
	class Pipeline : public Bindable
	{
	public:
		Pipeline()
			:dssd(
				{
				.nextInChain = nullptr,
				.format = wgpu::TextureFormat::Depth24PlusStencil8,
				.depthWriteEnabled = true,
				.depthCompare = wgpu::CompareFunction::Less,
					
				.stencilReadMask = 0xFFFFFFFF,
				.stencilWriteMask = 0xFFFFFFFF
				}
			)
		{}
	public:
		void BindVertexLayout(const ver::dv::VertexLayout& vb)
		{
			pVL = &vb;
		}		
		void BindRasterLayout(const RasterizerState& r)
		{
			raster.emplace(r.Get());
		}
		void BindVertexShader(const Shader& vs)
		{
			desc.vertexStage = vs.GetStageDescriptor();
		}
		void BindPixelShader(const Shader& ps)
		{
			PSDesc.emplace(ps.GetStageDescriptor());
		}
		void SetBindGroup(const wgpu::BindGroupLayout& bg)
		{
			bindGroupLayouts[counter++] = bg;
		}
		void SetRawLayout(const wgpu::BindGroupLayout& in)
		{
			bindGroupLayouts[counter++] = in;
		}
		[[nodiscard]]
		wgpu::RenderPipeline CookPipeline(const Graphics& gfx)const noexcept
		{
			// pipeline layout (used by the render pipeline, released after its creation)
			wgpu::PipelineLayoutDescriptor layoutDesc = {};
			layoutDesc.bindGroupLayoutCount = counter;
			layoutDesc.bindGroupLayouts = bindGroupLayouts.data();

			// begin pipeline set-up
			desc.layout = GetDevice(gfx).CreatePipelineLayout(&layoutDesc);

			if (PSDesc)desc.fragmentStage = &PSDesc.value();
			if (raster)desc.rasterizationState = &raster.value();

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
			colorDesc.format = gfx.GetSwapChainFormat();
			colorDesc.alphaBlend = blendDesc;
			colorDesc.colorBlend = blendDesc;
			colorDesc.writeMask = wgpu::ColorWriteMask::All;

			desc.colorStateCount = 1;
			desc.colorStates = &colorDesc;

			desc.depthStencilState = &dssd;

			desc.sampleMask = 0xFFFFFFFF; // <-- Note: this currently causes Emscripten to fail (sampleMask ends up as -1, which trips an assert)

			return GetDevice(gfx).CreateRenderPipeline(&desc);
		}
	private:
		const ver::dv::VertexLayout* pVL;
		std::optional<wgpu::ProgrammableStageDescriptor> PSDesc;
		std::optional<wgpu::RasterizationStateDescriptor> raster;
		std::array<wgpu::BindGroupLayout, 4> bindGroupLayouts;
 		mutable wgpu::RenderPipelineDescriptor desc = {};
		wgpu::DepthStencilStateDescriptor dssd;
		uint32_t counter = 0;
	};
}
