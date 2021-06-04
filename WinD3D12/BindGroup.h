#pragma once
#include "ConstantBuffers.h"
#include "ConstantBinding.h"

namespace ver
{
	class BindGroup : public Bindable
	{
	public:
		BindGroup()noexcept = default;
		BindGroup(const wgpu::BindGroupLayout& predefined)noexcept
			:bgl(predefined)
		{}
	public:
		template<typename T, typename R>
		void BindResource(const ConstantBinding<T,R>& resource)
		{
			if (!bgl) bindingLayouts[next] = resource.GetLayout();
			bindings[next++] = resource.GetEntryDesc();
		}
		wgpu::BindGroup MakeBindGroup(const Graphics& gfx)const noexcept
		{
			wgpu::BindGroupDescriptor bgDesc = {};
			bgDesc.layout = CookLayout(gfx);
			bgDesc.entryCount = static_cast<uint32_t>(next);
			bgDesc.entries = bindings.data();

			return GetDevice(gfx).CreateBindGroup(&bgDesc);
		}
		wgpu::BindGroupLayout& CookLayout(const Graphics& gfx)const noexcept
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
		size_t next = 0;
		std::array<wgpu::BindGroupLayoutEntry, 8> bindingLayouts;
		std::array<wgpu::BindGroupEntry, 8> bindings;
		mutable wgpu::BindGroupLayout bgl;
	};
}
