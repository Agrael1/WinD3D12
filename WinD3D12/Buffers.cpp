#include "Buffers.h"

ver::Buffer::Buffer(const Graphics& gfx, const void* data, size_t size, wgpu::BufferUsage usage)
{
	wgpu::BufferDescriptor descriptor;
	descriptor.size = size;
	descriptor.usage = usage | wgpu::BufferUsage::CopyDst;
	buffer = GetDevice(gfx).CreateBuffer(&descriptor);

	Update(gfx, data, size);
}

ver::Buffer::Buffer(const Graphics& gfx, size_t size, wgpu::BufferUsage usage)
{
	wgpu::BufferDescriptor descriptor;
	descriptor.size = size;
	descriptor.usage = usage | wgpu::BufferUsage::CopyDst;
	buffer = GetDevice(gfx).CreateBuffer(&descriptor);
}

void ver::Buffer::Update(const Graphics& gfx, const void* data, size_t size)
{
	GetQueue(gfx).WriteBuffer(buffer, 0, data, size);
}

ver::IndexBuffer::IndexBuffer(const Graphics& gfx, const void* data, uint32_t count, wgpu::IndexFormat format)
	:Buffer(gfx, data, count* size_t(format) * 2, wgpu::BufferUsage::Index),
	format(format), count(count)
{

}

ver::VertexBuffer::VertexBuffer(const Graphics& gfx, std::span<const uint8_t> xbuffer)
	:Buffer(gfx, xbuffer.data(), xbuffer.size(), wgpu::BufferUsage::Vertex)
{
}
