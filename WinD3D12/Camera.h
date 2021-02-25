#pragma once
import DirectXMath;

class Camera
{
public:
	Camera()noexcept;
public:
	DirectX::XMMATRIX GetViewMatrix()const noexcept;
	void SpawnControlWindow()noexcept;
	void Reset()noexcept;
	void Rotate(float dx, float dy)noexcept;
	void Translate(DirectX::XMFLOAT3 translation)noexcept;
private:
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 rot;
	static constexpr const float travelSpeed = 12.0f;
	static constexpr const float rotationSpeed = 0.004f;
};