#pragma once
#include "ConstantBuffers.h"

namespace ver
{
	class BindGroup : public Bindable
	{
	public:
		BindGroup(const Graphics& gfx, wgpu::BindGroup& write_to)noexcept;
		BindGroup(const Graphics& gfx, wgpu::BindGroup& write_to, const wgpu::BindGroupLayout& predefined)noexcept;
		~BindGroup();
	public:
		template<typename T, typename R>
		void BindResource(const ConstantBinding<T, R>& resource)
		{
			if (!bgl) bindingLayouts[next] = resource.GetLayout();
			bindings[next++] = resource.GetEntryDesc();
		}
		wgpu::BindGroup MakeBindGroup()const noexcept;
		wgpu::BindGroupLayout& CookLayout()const noexcept;
	private:
		const Graphics& gfx;
		wgpu::BindGroup& group;
		size_t next = 0;
		std::array<wgpu::BindGroupLayoutEntry, 8> bindingLayouts;
		std::array<wgpu::BindGroupEntry, 8> bindings;
		mutable wgpu::BindGroupLayout bgl;
	};
}
