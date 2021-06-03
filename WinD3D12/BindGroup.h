#pragma once
#include "ConstantBuffers.h"
#include "ConstantBinding.h"

namespace ver
{
	class BindGroup : public Bindable
	{
	public:
		BindGroup(const Graphics& gfx, wgpu::BindGroup& write_to)noexcept
			:group(write_to), gfx(gfx)
		{

		}
		BindGroup(const Graphics& gfx, wgpu::BindGroup& write_to, const wgpu::BindGroupLayout& predefined)noexcept
			:group(write_to), gfx(gfx), bgl(predefined)
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
		template<typename T>
		void BindResource(const ConstantBinding<T>& resource)
		{
			if (!bgl) bindingLayouts[next] = resource.GetLayout();
			bindings[next++] = resource.GetEntryDesc();
		}
		wgpu::BindGroup MakeBindGroup()const noexcept
		{
			wgpu::BindGroupDescriptor bgDesc = {};
			bgDesc.layout = CookLayout();
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
