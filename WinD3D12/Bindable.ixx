module;
#include "DawnAdapter.h"
#include <concepts>
export module Bindable;
export import Graphics;

export namespace ver
{
	class Bindable
	{
	protected:
		constexpr static const wgpu::Device& GetDevice(const Graphics& gfx)noexcept
		{
			return gfx.device;
		}
		constexpr static const wgpu::Queue& GetQueue(const Graphics& gfx)noexcept
		{
			return gfx.renderQueue;
		}
	};

	template<typename T>
	concept is_bindable = requires {std::derived_from<T, Bindable>; };
}