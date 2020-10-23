#pragma once
#include "Buffers.h"

namespace ver
{
	class ConstantBuffer : public Buffer
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
			:Buffer(gfx, desc.data, desc.size_bytes, wgpu::BufferUsage::Uniform),
			slot(desc.slot), type(desc.type)
		{

		}
	public:
		constexpr wgpu::BindGroupLayoutEntry GetDesc()const noexcept
		{
			return
			{
				.binding = slot,
				.visibility = type,
				.type = wgpu::BindingType::UniformBuffer
			};
		}
		void Update(const Graphics& gfx, const void* data, uint32_t size)
		{
			GetQueue(gfx).WriteBuffer(*this, 0, data, size);
		}
	private:
		uint32_t slot;
		wgpu::ShaderStage type;
	};
}
