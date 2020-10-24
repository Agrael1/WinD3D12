#pragma once
#include "Drawable.h"
#include "Shaders.h"
#include <optional>

static uint32_t triangle_vs[] = {
	0x07230203, 0x00010000, 0x000d0008, 0x00000043, 0x00000000, 0x00020011, 0x00000001, 0x0006000b,
	0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001,
	0x0009000f, 0x00000000, 0x00000004, 0x6e69616d, 0x00000000, 0x0000002d, 0x00000031, 0x0000003e,
	0x00000040, 0x00050048, 0x00000009, 0x00000000, 0x00000023, 0x00000000, 0x00030047, 0x00000009,
	0x00000002, 0x00040047, 0x0000000b, 0x00000022, 0x00000000, 0x00040047, 0x0000000b, 0x00000021,
	0x00000000, 0x00050048, 0x0000002b, 0x00000000, 0x0000000b, 0x00000000, 0x00050048, 0x0000002b,
	0x00000001, 0x0000000b, 0x00000001, 0x00050048, 0x0000002b, 0x00000002, 0x0000000b, 0x00000003,
	0x00050048, 0x0000002b, 0x00000003, 0x0000000b, 0x00000004, 0x00030047, 0x0000002b, 0x00000002,
	0x00040047, 0x00000031, 0x0000001e, 0x00000000, 0x00040047, 0x0000003e, 0x0000001e, 0x00000000,
	0x00040047, 0x00000040, 0x0000001e, 0x00000001, 0x00020013, 0x00000002, 0x00030021, 0x00000003,
	0x00000002, 0x00030016, 0x00000006, 0x00000020, 0x0003001e, 0x00000009, 0x00000006, 0x00040020,
	0x0000000a, 0x00000002, 0x00000009, 0x0004003b, 0x0000000a, 0x0000000b, 0x00000002, 0x00040015,
	0x0000000c, 0x00000020, 0x00000001, 0x0004002b, 0x0000000c, 0x0000000d, 0x00000000, 0x00040020,
	0x0000000e, 0x00000002, 0x00000006, 0x00040017, 0x00000018, 0x00000006, 0x00000003, 0x00040018,
	0x00000019, 0x00000018, 0x00000003, 0x0004002b, 0x00000006, 0x0000001e, 0x00000000, 0x0004002b,
	0x00000006, 0x00000022, 0x3f800000, 0x00040017, 0x00000027, 0x00000006, 0x00000004, 0x00040015,
	0x00000028, 0x00000020, 0x00000000, 0x0004002b, 0x00000028, 0x00000029, 0x00000001, 0x0004001c,
	0x0000002a, 0x00000006, 0x00000029, 0x0006001e, 0x0000002b, 0x00000027, 0x00000006, 0x0000002a,
	0x0000002a, 0x00040020, 0x0000002c, 0x00000003, 0x0000002b, 0x0004003b, 0x0000002c, 0x0000002d,
	0x00000003, 0x00040017, 0x0000002f, 0x00000006, 0x00000002, 0x00040020, 0x00000030, 0x00000001,
	0x0000002f, 0x0004003b, 0x00000030, 0x00000031, 0x00000001, 0x00040020, 0x0000003b, 0x00000003,
	0x00000027, 0x00040020, 0x0000003d, 0x00000003, 0x00000018, 0x0004003b, 0x0000003d, 0x0000003e,
	0x00000003, 0x00040020, 0x0000003f, 0x00000001, 0x00000018, 0x0004003b, 0x0000003f, 0x00000040,
	0x00000001, 0x0006002c, 0x00000018, 0x00000042, 0x0000001e, 0x0000001e, 0x00000022, 0x00050036,
	0x00000002, 0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x00050041, 0x0000000e,
	0x0000000f, 0x0000000b, 0x0000000d, 0x0004003d, 0x00000006, 0x00000010, 0x0000000f, 0x0006000c,
	0x00000006, 0x00000011, 0x00000001, 0x0000000b, 0x00000010, 0x0006000c, 0x00000006, 0x00000012,
	0x00000001, 0x0000000e, 0x00000011, 0x0006000c, 0x00000006, 0x00000017, 0x00000001, 0x0000000d,
	0x00000011, 0x0004007f, 0x00000006, 0x00000020, 0x00000017, 0x00060050, 0x00000018, 0x00000023,
	0x00000012, 0x00000017, 0x0000001e, 0x00060050, 0x00000018, 0x00000024, 0x00000020, 0x00000012,
	0x0000001e, 0x00060050, 0x00000019, 0x00000026, 0x00000023, 0x00000024, 0x00000042, 0x0004003d,
	0x0000002f, 0x00000032, 0x00000031, 0x00050051, 0x00000006, 0x00000033, 0x00000032, 0x00000000,
	0x00050051, 0x00000006, 0x00000034, 0x00000032, 0x00000001, 0x00060050, 0x00000018, 0x00000035,
	0x00000033, 0x00000034, 0x00000022, 0x00050091, 0x00000018, 0x00000036, 0x00000026, 0x00000035,
	0x00050051, 0x00000006, 0x00000037, 0x00000036, 0x00000000, 0x00050051, 0x00000006, 0x00000038,
	0x00000036, 0x00000001, 0x00050051, 0x00000006, 0x00000039, 0x00000036, 0x00000002, 0x00070050,
	0x00000027, 0x0000003a, 0x00000037, 0x00000038, 0x00000039, 0x00000022, 0x00050041, 0x0000003b,
	0x0000003c, 0x0000002d, 0x0000000d, 0x0003003e, 0x0000003c, 0x0000003a, 0x0004003d, 0x00000018,
	0x00000041, 0x00000040, 0x0003003e, 0x0000003e, 0x00000041, 0x000100fd, 0x00010038
};
static uint32_t triangle_ps[] = {
	0x07230203, 0x00010000, 0x000d0007, 0x00000013, 0x00000000, 0x00020011, 0x00000001, 0x0006000b,
	0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001,
	0x0007000f, 0x00000004, 0x00000004, 0x6e69616d, 0x00000000, 0x00000009, 0x0000000c, 0x00030010,
	0x00000004, 0x00000007, 0x00040047, 0x00000009, 0x0000001e, 0x00000000, 0x00040047, 0x0000000c,
	0x0000001e, 0x00000000, 0x00020013, 0x00000002, 0x00030021, 0x00000003, 0x00000002, 0x00030016,
	0x00000006, 0x00000020, 0x00040017, 0x00000007, 0x00000006, 0x00000004, 0x00040020, 0x00000008,
	0x00000003, 0x00000007, 0x0004003b, 0x00000008, 0x00000009, 0x00000003, 0x00040017, 0x0000000a,
	0x00000006, 0x00000003, 0x00040020, 0x0000000b, 0x00000001, 0x0000000a, 0x0004003b, 0x0000000b,
	0x0000000c, 0x00000001, 0x0004002b, 0x00000006, 0x0000000e, 0x3f800000, 0x00050036, 0x00000002,
	0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x0004003d, 0x0000000a, 0x0000000d,
	0x0000000c, 0x00050051, 0x00000006, 0x0000000f, 0x0000000d, 0x00000000, 0x00050051, 0x00000006,
	0x00000010, 0x0000000d, 0x00000001, 0x00050051, 0x00000006, 0x00000011, 0x0000000d, 0x00000002,
	0x00070050, 0x00000007, 0x00000012, 0x0000000f, 0x00000010, 0x00000011, 0x0000000e, 0x0003003e,
	0x00000009, 0x00000012, 0x000100fd, 0x00010038
};
static const uint16_t indxData[] = {
	0, 1, 2,
	0 // padding (better way of doing this?)
};

namespace ver
{
	class Triangle : public Drawable
	{
	public:
		static ver::dv::VertexBuffer MakeVertices(ver::dv::VertexLayout layout)
		{
			ver::dv::VertexBuffer x{ std::move(layout),3 };
			x[0].SetAttributeByIndex(0, DirectX::XMFLOAT2{ -0.8f, -0.8f });
			x[0].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 0.0f, 1.0f });

			x[1].SetAttributeByIndex(0, DirectX::XMFLOAT2{ 0.8f, -0.8f });
			x[1].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f });

			x[2].SetAttributeByIndex(0, DirectX::XMFLOAT2{ -0.0f, 0.8f });
			x[2].SetAttributeByIndex(1, DirectX::XMFLOAT3{ 1.0f, 0.0f, 0.0f });

			return x;
		};
	public:
		Triangle(const Graphics& gfx)
			:uRotBuf(gfx, { wgpu::ShaderStage::Vertex, &rotDeg, sizeof(float) ,0})
		{
			{
				ver::Shader rvs(gfx, triangle_vs);
				ver::Shader rps(gfx, triangle_ps);

				constexpr ver::dv::VertexLayout vl
				{ {
					ver::VType::Position2D,
					ver::VType::Float3Color
				} };


				auto a = Triangle::MakeVertices(vl);
				vBuffer.emplace(gfx, a.data());
				iBuffer.emplace(gfx, indxData, 4, wgpu::IndexFormat::Uint16);


				// bind group layout (used by both the pipeline layout and uniform bind group, released at the end of this function)
				wgpu::BindGroupLayoutEntry bglEntry[1] = { uRotBuf.GetLayout() };
				wgpu::BindGroupLayoutDescriptor bglDesc = {};
				bglDesc.entryCount = 1;
				bglDesc.entries = bglEntry;
				wgpu::BindGroupLayout bindGroupLayout = gfx.device.CreateBindGroupLayout(&bglDesc);

				wgpu::BindGroupEntry bgEntry[1] = { uRotBuf.GetEntryDesc()};

				wgpu::BindGroupDescriptor bgDesc = {};
				bgDesc.layout = bindGroupLayout;
				bgDesc.entryCount = 1;
				bgDesc.entries = bgEntry;

				bindGroup = gfx.device.CreateBindGroup(&bgDesc);

				// pipeline layout (used by the render pipeline, released after its creation)
				wgpu::PipelineLayoutDescriptor layoutDesc = {};
				layoutDesc.bindGroupLayoutCount = 1;
				layoutDesc.bindGroupLayouts = &bindGroupLayout;
				wgpu::PipelineLayout pipelineLayout = gfx.device.CreatePipelineLayout(&layoutDesc);

				// begin pipeline set-up
				wgpu::RenderPipelineDescriptor desc = {};

				desc.layout = pipelineLayout;
				desc.vertexStage = rvs.GetStageDescriptor();
				desc.fragmentStage = &rps.GetStageDescriptor();

				wgpu::VertexBufferLayoutDescriptor vertDesc = {};
				vertDesc.arrayStride = vl.Size();
				vertDesc.attributeCount = vl.GetElementCount();
				vertDesc.attributes = vl.GetDescs().data();
				wgpu::VertexStateDescriptor vertState = {};
				vertState.vertexBufferCount = 1;
				vertState.vertexBuffers = &vertDesc;

				desc.vertexState = &vertState;
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

				pipeline = gfx.device.CreateRenderPipeline(&desc);
			}
		}
	public:
		void Step(const Graphics& gfx)override
		{
			rotDeg += 0.5f;
			uRotBuf.Update(gfx, &rotDeg, sizeof(rotDeg));
		}
	private:
		ConstantBuffer uRotBuf;
		float rotDeg = 0.0f;
	};

}

