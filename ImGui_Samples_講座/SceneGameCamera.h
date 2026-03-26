#pragma once

#include <DirectXMath.h>

class SceneGameCamera
{
public:
	SceneGameCamera();

	void Update();
	DirectX::XMFLOAT4X4 GetViewMatrix() const;
	DirectX::XMFLOAT4X4 GetProjectionMatrix(float aspectRatio) const;

	bool GetAutoRotate() const;
	void SetAutoRotate(bool enabled);

	float GetAngle() const;
	void SetAngle(float angle);

	float GetRotationSpeed() const;
	void SetRotationSpeed(float speed);

	float GetRadius() const;
	void SetRadius(float radius);

	float GetHeight() const;
	void SetHeight(float height);

	float GetFovDegrees() const;
	void SetFovDegrees(float fovDegrees);

	float GetNearClip() const;
	void SetNearClip(float nearClip);

	float GetFarClip() const;
	void SetFarClip(float farClip);

	DirectX::XMFLOAT3 GetTarget() const;
	void SetTarget(DirectX::XMFLOAT3 target);

private:
	void NormalizeAngle();

	bool m_autoRotate;
	float m_angle;
	float m_rotationSpeed;
	float m_radius;
	float m_height;
	float m_fovDegrees;
	float m_nearClip;
	float m_farClip;
	DirectX::XMFLOAT3 m_target;
};
