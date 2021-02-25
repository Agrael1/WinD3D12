module;
#include <cstdint>
module BindGroup;


ver::BindGroup::BindGroup(const Graphics& gfx, wgpu::BindGroup& write_to) noexcept
	:group(write_to), gfx(gfx)
{

}
ver::BindGroup::BindGroup(const Graphics& gfx, wgpu::BindGroup& write_to, const wgpu::BindGroupLayout& predefined) noexcept
	:group(write_to), gfx(gfx), bgl(predefined)
{

}

ver::BindGroup::~BindGroup()
{
	if (!group)
	{
		group = MakeBindGroup();
	}
}

wgpu::BindGroup ver::BindGroup::MakeBindGroup() const noexcept
{
	wgpu::BindGroupDescriptor bgDesc = {};
	bgDesc.layout = CookLayout();
	bgDesc.entryCount = static_cast<uint32_t>(next);
	bgDesc.entries = bindings.data();

	return GetDevice(gfx).CreateBindGroup(&bgDesc);
}

wgpu::BindGroupLayout& ver::BindGroup::CookLayout() const noexcept
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
