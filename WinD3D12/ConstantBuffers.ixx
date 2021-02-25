module;
#include "DawnAdapter.h"
export module ConstantBuffers;
export import Buffers;
export import ConstantBinding;

export namespace ver
{
	class ConstantBuffer : public ConstantBinding<ConstantBuffer, Buffer>
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
		wgpu::BindGroupLayoutEntry GetLayout()const noexcept
		{
			return
			{
				.binding = slot,
				.visibility = type,
				.type = wgpu::BindingType::UniformBuffer
			};
		}
		wgpu::BindGroupEntry GetEntryDesc()const noexcept
		{
			return
			{
				.binding = slot,
				.buffer = *this,
				.offset = 0,
				.size = size
			};
		}
	private:
		uint32_t size;
		uint32_t slot;
		wgpu::ShaderStage type;
	};


	template<typename T>
	class PixelConstantBuffer : public ConstantBinding<PixelConstantBuffer<T>, Buffer>
	{
	public:
		PixelConstantBuffer(const Graphics& gfx, const T& constants, uint32_t slot = 0)
			:ConstantBinding<PixelConstantBuffer<T>, Buffer>(gfx, &constants, sizeof(T), wgpu::BufferUsage::Uniform),
			slot(slot)
		{

		}
		PixelConstantBuffer(const Graphics& gfx, uint32_t slot = 0)
			:ConstantBinding<PixelConstantBuffer<T>, Buffer>(gfx, sizeof(T), wgpu::BufferUsage::Uniform),
			slot(slot)
		{

		}
	public:
		wgpu::BindGroupLayoutEntry GetLayout()const noexcept
		{
			return
			{
				.binding = slot,
				.visibility = wgpu::ShaderStage::Fragment,
				.type = wgpu::BindingType::UniformBuffer
			};
		}
		wgpu::BindGroupEntry GetEntryDesc()const noexcept
		{
			return
			{
				.binding = slot,
				.buffer = *this,
				.offset = 0,
				.size = sizeof(T)
			};
		}
		void Update(const Graphics& gfx, const T& data)
		{
			Bindable::GetQueue(gfx).WriteBuffer(*this, 0, &data, sizeof(T));
		}
	private:
		uint32_t slot;
	};
}
