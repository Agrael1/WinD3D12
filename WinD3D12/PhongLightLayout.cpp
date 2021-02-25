module;
#include "DawnAdapter.h"
module PhongLightLayout;

ver::PhongLightLayout ver::PhongLightLayout::lbg;

wgpu::BindGroupLayout& ver::PhongLightLayout::Get(const Graphics& gfx)
{
	return _Get(gfx).bgl;
}

ver::PhongLightLayout& ver::PhongLightLayout::_Get(const Graphics& gfx)
{
	if (!lbg.bgl)
	{
		wgpu::BindGroupLayoutEntry lay
		{
			.binding = 1,
			.visibility = wgpu::ShaderStage::Fragment,
			.type = wgpu::BindingType::UniformBuffer,
			.hasDynamicOffset = false
		};
		wgpu::BindGroupLayoutDescriptor bglDesc = {};
		bglDesc.entryCount = 1;
		bglDesc.entries = &lay;
		lbg.bgl = GetDevice(gfx).CreateBindGroupLayout(&bglDesc);
	}
	return lbg;
}
