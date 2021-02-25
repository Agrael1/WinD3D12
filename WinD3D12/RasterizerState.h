#pragma once
import Bindable;

namespace ver
{
	class RasterizerState : public Bindable
	{
	public:
		RasterizerState(const Graphics& gfx, bool twosided);
	public:
		const wgpu::RasterizationStateDescriptor& Get()const noexcept;
	private:
		wgpu::RasterizationStateDescriptor raster;
	};
}
