#pragma once
#include "ConstantBuffers.h"
#include "DynamicConstant.h"

namespace ver
{
	template<wgpu::ShaderStage stage>
	class ConstantBufferEx : public ConstantBuffer
	{
	public:
		ConstantBufferEx(const Graphics& gfx, dc::Buffer&& xbuf, uint32_t slot)
			:
			ConstantBuffer(gfx, Desc{
			.type = stage, 
			.data = nullptr,
			.size_bytes = (uint32_t)xbuf.GetSizeInBytes(),
			.slot = slot
				}),
			buf(std::move(xbuf))
		{
			Update(gfx, buf.GetData().data(), (uint32_t)buf.GetSizeInBytes());
		}
	public:
		ConstantBufferEx Clone(const Graphics& gfx)const noexcept
		{
			dc::Buffer x = GetBuffer();
			return ConstantBufferEx{ gfx, std::move(x), slot };
		}
		const dc::Buffer& GetBuffer() const noexcept
		{
			return buf;
		}
		//void SetBuffer(const DC::Buffer& buf_in)
		//{
		//	buf.CopyFrom(buf_in);
		//	dirty = true;
		//}
		//void Bind(const Graphics& gfx) noexcept override
		//{
		//	if (dirty)
		//	{
		//		T::Update(gfx, buf);
		//		dirty = false;
		//	}
		//	T::Bind(gfx);
		//}
		//void Accept(TechniqueProbe& probe) override
		//{
		//	if (probe.VisitBuffer(buf))
		//	{
		//		dirty = true;
		//	}
		//}
	private:
		bool dirty = false;
		dc::Buffer buf;
	};

	using PixelConstantBufferEx = ConstantBufferEx<wgpu::ShaderStage::Fragment>;
	using VertexConstantBufferEx = ConstantBufferEx<wgpu::ShaderStage::Vertex>;
}