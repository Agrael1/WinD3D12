#pragma once
#include "Bindable.h"
#include "DynamicVBuffer.h"

namespace ver
{
	class Buffer : public Bindable
	{
	public:
		Buffer(const Graphics& gfx, const void* data, size_t size, wgpu::BufferUsage usage)
		{
			wgpu::BufferDescriptor descriptor;
			descriptor.size = size;
			descriptor.usage = usage | wgpu::BufferUsage::CopyDst;
			buffer = GetDevice(gfx).CreateBuffer(&descriptor);

			Update(gfx, data, size);
		}
		Buffer(const Graphics& gfx, size_t size, wgpu::BufferUsage usage)
		{
			wgpu::BufferDescriptor descriptor;
			descriptor.size = size;
			descriptor.usage = usage | wgpu::BufferUsage::CopyDst;
			buffer = GetDevice(gfx).CreateBuffer(&descriptor);
		}
	public:
		operator wgpu::Buffer&()
		{
			return buffer;
		}
		operator const wgpu::Buffer&()const
		{
			return buffer;
		}
		void Update(const Graphics& gfx, const void* data, size_t size)
		{
			GetQueue(gfx).WriteBuffer(buffer, 0, data, size);
		}
	private:
		wgpu::Buffer buffer;
	};

	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(const Graphics& gfx, const void* data, uint32_t count, wgpu::IndexFormat format)
			:Buffer(gfx, data, count*size_t(format)*2, wgpu::BufferUsage::Index), 
			format(format), count(count)
		{

		}
	public:
		auto GetFormat()const noexcept
		{
			return format;
		}
		auto GetCount()const noexcept
		{
			return count;
		}
	private:
		uint32_t count;
		wgpu::IndexFormat format;
	};
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(const Graphics& gfx, std::span<const uint8_t> xbuffer)
			:Buffer(gfx, xbuffer.data(), xbuffer.size(), wgpu::BufferUsage::Vertex)
		{
		}
	};
}