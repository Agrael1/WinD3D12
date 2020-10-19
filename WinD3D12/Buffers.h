#pragma once
#include "Bindable.h"

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

			GetQueue(gfx).WriteBuffer(buffer, 0, data, size);
		}
	private:
		wgpu::Buffer buffer;
	};

	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(const Graphics& gfx, const void* data, size_t size)
			:Buffer(gfx, data, size, wgpu::BufferUsage::Index)
		{

		}
	};
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(const Graphics& gfx, const void* data, size_t size)
			:Buffer(gfx, data, size, wgpu::BufferUsage::Vertex)
		{

		}
	};
}