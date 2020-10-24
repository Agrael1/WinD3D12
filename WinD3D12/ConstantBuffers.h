#pragma once
#include "Buffers.h"

namespace ver
{
	class ConstantBinding : public Buffer
	{
	public:
		using Buffer::Buffer;
		using Buffer::operator const wgpu::Buffer&;
		using Buffer::operator wgpu::Buffer&;
	public:
		virtual wgpu::BindGroupLayoutEntry GetLayout()const noexcept = 0;
		virtual wgpu::BindGroupEntry GetEntryDesc()const noexcept = 0;
	};

	class ConstantBuffer : public ConstantBinding
	{
	public:
		struct Desc
		{
			wgpu::ShaderStage type;
			const void* data;
			uint32_t size_bytes;
			uint32_t slot = 0;
		};
	public:
		ConstantBuffer(const Graphics& gfx, const Desc& desc)
			:ConstantBinding(gfx, desc.data, desc.size_bytes, wgpu::BufferUsage::Uniform),
			slot(desc.slot), type(desc.type), size(desc.size_bytes)
		{

		}
	public:
		wgpu::BindGroupLayoutEntry GetLayout()const noexcept override
		{
			return
			{
				.binding = slot,
				.visibility = type,
				.type = wgpu::BindingType::UniformBuffer
			};
		}
		wgpu::BindGroupEntry GetEntryDesc()const noexcept override
		{
			return
			{
				.binding = slot,
				.buffer = *this,
				.offset = 0,
				.size = size
			};
		}
		void Update(const Graphics& gfx, const void* data, uint32_t rsize)
		{
			GetQueue(gfx).WriteBuffer(*this, 0, data, rsize);
		}
	private:
		uint32_t size;
		uint32_t slot;
		wgpu::ShaderStage type;
	};
}
