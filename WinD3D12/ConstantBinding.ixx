module;
#include <concepts>
#include "DawnAdapter.h"
export module ConstantBinding;
import Bindable;

export namespace ver
{
	template<typename T, typename From = Bindable> requires is_bindable<From>
		class ConstantBinding : public From
		{
		public:
			template<typename ...Args>
			ConstantBinding(Args&&... args) :From(std::forward<Args>(args)...) {}
		public:
			wgpu::BindGroupLayoutEntry GetLayout()const noexcept
			{
				return static_cast<const T*>(this)->GetLayout();
			}
			wgpu::BindGroupEntry GetEntryDesc()const noexcept
			{
				return static_cast<const T*>(this)->GetEntryDesc();
			}
		};
}