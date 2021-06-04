#include "pch.h"
#include "Mesh.h"
#include "Material.h"

using namespace ver;

ver::Mesh::Mesh(Graphics& gfx, const Material& mat, const aiMesh& mesh, float scale)
	:cbuf(gfx), pixbuf(mat.MakePixelBuffer(gfx))
{
	vBuffer.emplace(mat.MakeVertexBindable(gfx, mesh, scale));
	iBuffer.emplace(mat.MakeIndexBindable(gfx, mesh));

	auto b = mat.GetBinds();
	auto p = mat.GetPipeline();
	b.BindResource(cbuf);
	b.BindResource(pixbuf);
	p.SetBindGroup(b.CookLayout(gfx));
	bindGroup = b.MakeBindGroup(gfx);
	pipeline = p.CookPipeline(gfx);
}

concurrency::task<std::shared_ptr<Mesh>> 
ver::Mesh::MakeAsync(Graphics& gfx, const Material& mat, const aiMesh& mesh, float scale)
{
	return concurrency::create_task(
		[&gfx, mat, mesh]() {
			return std::make_shared<Mesh>(gfx, mat, mesh);
		});
}

DirectX::XMMATRIX ver::Mesh::GetTransformXM() const noexcept
{
	return DirectX::XMLoadFloat4x4(&transform);
}

void ver::Mesh::Step(const Graphics& gfx, float dt, DirectX::FXMMATRIX accumulatedTranform)
{
	DirectX::XMStoreFloat4x4(&transform, accumulatedTranform);
	cbuf.Update(gfx, accumulatedTranform);
}

