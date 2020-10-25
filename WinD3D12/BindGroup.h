#pragma once
#include "ConstantBuffers.h"

namespace ver
{
	class BindGroup : public Bindable
	{
	public:
		BindGroup(const Graphics& gfx, wgpu::BindGroup& write_to)noexcept
			:group(write_to), gfx(gfx)
		{

		}
		~BindGroup()
		{
			if (!group)
			{
				group = MakeBindGroup();
			}
		}
	public:
		void BindResource(const ConstantBinding& resource)
		{
			bindings[next] = resource.GetEntryDesc();
			bindingLayouts[next++] = resource.GetLayout();
		}
		wgpu::BindGroup MakeBindGroup()const noexcept
		{
			if (!bgl) CookLayout();
			wgpu::BindGroupDescriptor bgDesc = {};
			bgDesc.layout = bgl;
			bgDesc.entryCount = static_cast<uint32_t>(next);
			bgDesc.entries = bindings.data();

			return GetDevice(gfx).CreateBindGroup(&bgDesc);
		}
		wgpu::BindGroupLayout& CookLayout()const noexcept
		{
			if (!bgl)
			{
				wgpu::BindGroupLayoutDescriptor bglDesc = {};
				bglDesc.entryCount = static_cast<uint32_t>(next);
				bglDesc.entries = bindingLayouts.data();
				return bgl = GetDevice(gfx).CreateBindGroupLayout(&bglDesc);
			}
			return bgl;
		}
	private:
		const Graphics& gfx;
		wgpu::BindGroup& group;
		size_t next = 0;
		std::array<wgpu::BindGroupLayoutEntry, 8> bindingLayouts;
		std::array<wgpu::BindGroupEntry, 8> bindings;
		mutable wgpu::BindGroupLayout bgl;
	};
}
