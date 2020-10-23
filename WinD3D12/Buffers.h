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

			GetQueue(gfx).WriteBuffer(buffer, 0, data, size);
		}
	public:
		operator wgpu::Buffer()
		{
			return buffer;
		}
		operator const wgpu::Buffer()const
		{
			return buffer;
		}
	private:
		wgpu::Buffer buffer;
	};

	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(const Graphics& gfx, const void* data, size_t count, wgpu::IndexFormat format)
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
		size_t count;
		wgpu::IndexFormat format;
	};
	class VertexBuffer : public Bindable
	{
	public:
		VertexBuffer(const Graphics& gfx, std::span<const uint8_t> xbuffer, std::string_view tag)
		{
			auto size = xbuffer.size();
			wgpu::BufferDescriptor descriptor;
			descriptor.size = size;
			descriptor.usage = wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst;
			descriptor.label = tag.data(); //TODO: get real purpose
			buffer = GetDevice(gfx).CreateBuffer(&descriptor);

			GetQueue(gfx).WriteBuffer(buffer, 0, xbuffer.data(), size);
		}
	public:
		wgpu::Buffer Get()const noexcept
		{
			return buffer;
		}
	private:
		wgpu::Buffer buffer;
	};
}