#include "pch.h"
#include "Node.h"
#include "Mesh.h"

using namespace ver;
namespace dx = DirectX;

Node::Node(int id, std::string_view name, std::vector<Mesh*> meshPtrs, const DirectX::XMMATRIX& transform_in)
	:id(id),
	meshPtrs(std::move(meshPtrs)),
	name(name)
{
	dx::XMStoreFloat4x4(&transform, transform_in);
	dx::XMStoreFloat4x4(&appliedTransform, dx::XMMatrixIdentity());
}

void Node::Step(const Graphics& gfx, float dt, DirectX::FXMMATRIX accumulatedTransform) const
{
	const auto built =
		dx::XMLoadFloat4x4(&appliedTransform) *
		dx::XMLoadFloat4x4(&transform) *
		accumulatedTransform;
	for (const auto pm : meshPtrs)
		pm->Step(gfx, dt, built);
	for (const auto& pc : childPtrs)
		pc->Step(gfx, dt, built);
}

void Node::AddChild(std::unique_ptr<Node> pChild)noexcept
{
	assert(pChild);
	childPtrs.push_back(std::move(pChild));
}
void Node::SetAppliedTransform(DirectX::FXMMATRIX rtransform) noexcept
{
	dx::XMStoreFloat4x4(&appliedTransform, rtransform);
}
const DirectX::XMFLOAT4X4& Node::GetAppliedTransform() const noexcept
{
	return appliedTransform;
}
int Node::GetId() const noexcept
{
	return id;
}