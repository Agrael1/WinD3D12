#pragma once
#include "Buffers.h"
#include "Shaders.h"
#include "DynamicVBuffer.h"

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
static const float vertData[] = {
	-0.8f, -0.8f, 0.0f, 0.0f, 1.0f, // BL
	 0.8f, -0.8f, 0.0f, 1.0f, 0.0f, // BR
	-0.0f,  0.8f, 1.0f, 0.0f, 0.0f, // top
};
static const uint16_t indxData[] = {
	0, 1, 2,
	0 // padding (better way of doing this?)
};


namespace ver
{

class VeritasEngine
{
public:
	VeritasEngine(uint32_t width, uint32_t height, XWindow wnd)
		:gfx(width, height, wnd),
		//v(gfx, vertData,sizeof(vertData)),
		idx(gfx, indxData, sizeof(v)),
		uRotBuf(gfx,&rotDeg,sizeof(float),wgpu::BufferUsage::Uniform)
	{
		ver::Shader rvs(gfx, triangle_vs);
		ver::Shader rps(gfx, triangle_ps);

		constexpr ver::dv::VertexLayout vl
		{ {
			ver::VType::Position2D,
			ver::VType::Float3Color
		} };
		constexpr bool x = vl.Has(ver::dv::VertexLayout::ElementType::Float4Color);
		constexpr size_t y = vl.Size();
		constexpr auto z = vl.GetDescs();
		constexpr auto w = vl.ResolveByIndex(1);

		constexpr ver::dv::VertexBuffer<y * 3> a{ vl };
		constexpr auto b = a[0];
		b.Attr<ver::VType::Position2D>() = { -0.8f, -0.8f };
		b.Attr<ver::VType::Float3Color>() = { 0.0f, 0.0f, 1.0f };

		constexpr auto c = a[1];
		c.Attr<ver::VType::Position2D>() = { 0.8f, -0.8f };
		c.Attr<ver::VType::Float3Color>() = { 0.0f, 1.0f, 1.0f };

		constexpr auto d = a[2];
		d.Attr<ver::VType::Position2D>() = { -0.0f,  0.8f };
		d.Attr<ver::VType::Float3Color>() = { 1.0f, 1.0f, 1.0f };

		//*f = 5;

		v.emplace(gfx, a.data(), 20 * 3);

		// bind group layout (used by both the pipeline layout and uniform bind group, released at the end of this function)
		wgpu::BindGroupLayoutEntry bglEntry = {};
		bglEntry.binding = 0;
		bglEntry.visibility = wgpu::ShaderStage::Vertex;
		bglEntry.type = wgpu::BindingType::UniformBuffer;

		wgpu::BindGroupLayoutDescriptor bglDesc = {};
		bglDesc.entryCount = 1;
		bglDesc.entries = &bglEntry;
		wgpu::BindGroupLayout bindGroupLayout = gfx.device.CreateBindGroupLayout(&bglDesc);

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
		vertDesc.arrayStride = y;
		vertDesc.attributeCount = 2;
		vertDesc.attributes = z.data();
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

		wgpu::BindGroupEntry bgEntry = {};
		bgEntry.binding = 0;
		bgEntry.buffer = uRotBuf;
		bgEntry.offset = 0;
		bgEntry.size = sizeof(rotDeg);

		wgpu::BindGroupDescriptor bgDesc = {};
		bgDesc.layout = bindGroupLayout;
		bgDesc.entryCount = 1;
		bgDesc.entries = &bgEntry;

		bindGroup = gfx.device.CreateBindGroup(&bgDesc);
	}
public:
	void Close()
	{
		bWindowClosed = true;
	}
	void Suspend()
	{

	}
	void Visibility(bool Visible)
	{
		bVisible = Visible;
	}
	void WindowActivationChanged(CoreWindowActivationState activationState)
	{

	}
private:
	void Test()
	{
		rotDeg += 0.1f;
		gfx.renderQueue.WriteBuffer(uRotBuf, 0, &rotDeg, sizeof(rotDeg));

		wgpu::RenderPassDescriptor renderPass = {};
		renderPass.colorAttachmentCount = 1;
		renderPass.colorAttachments = &gfx.colorDesc;

		wgpu::CommandEncoder encoder = gfx.device.CreateCommandEncoder(nullptr);			// create encoder
		{
			wgpu::RenderPassEncoder pass = encoder.BeginRenderPass(&renderPass);	// create pass

			// draw the triangle (comment these five lines to simply clear the screen)
			pass.SetPipeline(pipeline);
			pass.SetBindGroup(0, bindGroup, 0, 0);
			pass.SetVertexBuffer(0, v.value(), 0, 0);
			pass.SetIndexBufferWithFormat(idx, wgpu::IndexFormat::Uint16, 0, 0);
			pass.DrawIndexed(3);
			pass.EndPass();
		}

		commands = encoder.Finish(nullptr);				// create commands
		gfx.renderQueue.Submit(1, &commands);

		gfx.Present();
	}
public:
	void Run()
	{
		if(bVisible)
			Test();
	}
private:
	Graphics gfx;
	bool bWindowClosed = false;
	bool bVisible = true;
private:
	std::optional<VertexBuffer> v;
	IndexBuffer idx;
	Buffer uRotBuf;
	wgpu::RenderPipeline pipeline;
	wgpu::BindGroup bindGroup;
	wgpu::CommandBuffer commands;
	float rotDeg = 0.0f;
};
}