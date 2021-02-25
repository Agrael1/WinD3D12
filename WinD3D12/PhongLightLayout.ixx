module;
#include "DawnAdapter.h"
export module PhongLightLayout;
import Bindable;

export namespace ver
{
	class PhongLightLayout : public Bindable
	{
	public:
		static wgpu::BindGroupLayout& Get(const Graphics& gfx);
	private:
		static PhongLightLayout& _Get(const Graphics& gfx);
	private:
		wgpu::BindGroupLayout bgl;
		static PhongLightLayout lbg;
	};
}