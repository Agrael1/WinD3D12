#pragma once
#include "Graphics.h"

namespace ver
{
	class Bindable
	{
	protected:
		static wgpu::Device GetDevice(Graphics& gfx)noexcept
		{
			return gfx.device;
		}
	};
}