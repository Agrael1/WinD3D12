#include "Camera.h"
#include <algorithm>

namespace dx = DirectX;

template<typename T>
T wrap_angle(T theta)
{
	T x = (T)fmod(theta + (T)dx::XM_PI, (T)dx::XM_2PI);
	if (x < 0)
		x += (T)dx::XM_2PI;
	return x - (T)dx::XM_PI;
}

Camera::Camera() noexcept
{
	Reset();
}

DirectX::XMMATRIX Camera::GetViewMatrix() const noexcept
{
	using namespace dx;
	const dx::XMVECTOR forwardBaseVector = dx::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	// apply the camera rotations to a base vector
	const auto lookVector = dx::XMVector3Transform(forwardBaseVector,
		dx::XMMatrixRotationRollPitchYawFromVector(dx::XMLoadFloat2(&orbit))*
		dx::XMMatrixRotationRollPitchYawFromVector(dx::XMLoadFloat2(&rot))
	);
	// generate camera transform (applied to all objects to arrange them relative
	// to camera position/orientation in world) from cam position and direction
	// camera "top" always faces towards +Y (cannot do a barrel roll)
	const auto camPosition = dx::XMVector3Transform(dx::XMLoadFloat3(&pos), 
		dx::XMMatrixRotationRollPitchYawFromVector(dx::XMLoadFloat2(&orbit)));
	const auto camTarget = camPosition + lookVector;
	return XMMatrixLookAtLH(camPosition, camTarget, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
}
void Camera::Reset() noexcept
{
	pos = { 0, 0, -5.0f };
	rot = orbit = { 0, 0 };
}
void Camera::Orbit(float dphi, float dtheta) noexcept
{
	orbit.y = wrap_angle(orbit.y + dphi * rotationSpeed);
	orbit.x = std::clamp(orbit.x + dtheta * rotationSpeed, 0.995f * -dx::XM_PIDIV2, 0.995f * dx::XM_PIDIV2);
}
void Camera::Rotate(float dx, float dy) noexcept
{
	rot.y = wrap_angle(rot.y + dx * rotationSpeed);
	rot.x = std::clamp(rot.x + dy * rotationSpeed, 0.995f * -dx::XM_PIDIV2, 0.995f * dx::XM_PIDIV2);
}
void Camera::Translate(DirectX::XMFLOAT3 translation) noexcept
{
	using namespace dx;
	dx::XMStoreFloat3(&pos, dx::XMLoadFloat3(&pos) + dx::XMVector3Transform(
		dx::XMLoadFloat3(&translation),
		dx::XMMatrixRotationRollPitchYawFromVector(dx::XMLoadFloat2(&rot)) *
		dx::XMMatrixScaling(travelSpeed, travelSpeed, travelSpeed)
	));
}

