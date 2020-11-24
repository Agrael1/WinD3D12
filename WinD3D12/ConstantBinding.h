#pragma once
#include "Bindable.h"

namespace ver
{

	template<typename T>
	class XConstantBinding : public Bindable
	{
	public:
		wgpu::BindGroupLayoutEntry GetLayout()const noexcept
		{
			return static_cast<const T*>(this)->GetLayout();
		}
		wgpu::BindGroupEntry GetEntryDesc()const noexcept
		{
			return static_cast<const T*>(this)->GetEntryDesc();
		}
	protected:
		uint32_t slot;
	};
}
