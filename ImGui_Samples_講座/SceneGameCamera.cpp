#include "SceneGameCamera.h"

#include <cmath>

namespace
{
	DirectX::XMFLOAT4X4 ToFloat4x4(const DirectX::XMMATRIX& matrix)
	{
		DirectX::XMFLOAT4X4 value{};
		DirectX::XMStoreFloat4x4(&value, matrix);
		return value;
	}
}

SceneGameCamera::SceneGameCamera()
	: m_autoRotate(true)
	, m_angle(0.0f)
	, m_rotationSpeed(0.01f)
	, m_radius(6.0f)
	, m_height(3.2f)
	, m_fovDegrees(60.0f)
	, m_nearClip(0.1f)
	, m_farClip(100.0f)
	, m_target(0.0f, 0.6f, 0.0f)
{
}

void SceneGameCamera::Update()
{
	if (!m_autoRotate)
	{
		return;
	}

	m_angle += m_rotationSpeed;
	NormalizeAngle();
}

DirectX::XMFLOAT4X4 SceneGameCamera::GetViewMatrix() const
{
	const DirectX::XMVECTOR eye = DirectX::XMVectorSet(
		std::sin(m_angle) * m_radius,
		m_height,
		std::cos(m_angle) * m_radius,
		0.0f);
	const DirectX::XMVECTOR target = DirectX::XMLoadFloat3(&m_target);
	const DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	return ToFloat4x4(DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(eye, target, up)));
}

DirectX::XMFLOAT4X4 SceneGameCamera::GetProjectionMatrix(float aspectRatio) const
{
	if (aspectRatio <= 0.0f)
	{
		aspectRatio = 1.0f;
	}

	return ToFloat4x4(DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(m_fovDegrees),
			aspectRatio,
			m_nearClip,
			m_farClip)));
}

bool SceneGameCamera::GetAutoRotate() const
{
	return m_autoRotate;
}

void SceneGameCamera::SetAutoRotate(bool enabled)
{
	m_autoRotate = enabled;
}

float SceneGameCamera::GetAngle() const
{
	return m_angle;
}

void SceneGameCamera::SetAngle(float angle)
{
	m_angle = angle;
	NormalizeAngle();
}

float SceneGameCamera::GetRotationSpeed() const
{
	return m_rotationSpeed;
}

void SceneGameCamera::SetRotationSpeed(float speed)
{
	if (speed < 0.0f)
	{
		speed = 0.0f;
	}
	m_rotationSpeed = speed;
}

float SceneGameCamera::GetRadius() const
{
	return m_radius;
}

void SceneGameCamera::SetRadius(float radius)
{
	if (radius < 0.1f)
	{
		radius = 0.1f;
	}
	m_radius = radius;
}

float SceneGameCamera::GetHeight() const
{
	return m_height;
}

void SceneGameCamera::SetHeight(float height)
{
	m_height = height;
}

float SceneGameCamera::GetFovDegrees() const
{
	return m_fovDegrees;
}

void SceneGameCamera::SetFovDegrees(float fovDegrees)
{
	if (fovDegrees < 10.0f)
	{
		fovDegrees = 10.0f;
	}
	if (fovDegrees > 170.0f)
	{
		fovDegrees = 170.0f;
	}
	m_fovDegrees = fovDegrees;
}

float SceneGameCamera::GetNearClip() const
{
	return m_nearClip;
}

void SceneGameCamera::SetNearClip(float nearClip)
{
	if (nearClip < 0.01f)
	{
		nearClip = 0.01f;
	}
	m_nearClip = nearClip;
	if (m_farClip <= m_nearClip)
	{
		m_farClip = m_nearClip + 0.01f;
	}
}

float SceneGameCamera::GetFarClip() const
{
	return m_farClip;
}

void SceneGameCamera::SetFarClip(float farClip)
{
	if (farClip <= m_nearClip)
	{
		farClip = m_nearClip + 0.01f;
	}
	m_farClip = farClip;
}

DirectX::XMFLOAT3 SceneGameCamera::GetTarget() const
{
	return m_target;
}

void SceneGameCamera::SetTarget(DirectX::XMFLOAT3 target)
{
	m_target = target;
}

void SceneGameCamera::NormalizeAngle()
{
	while (m_angle >= DirectX::XM_2PI)
	{
		m_angle -= DirectX::XM_2PI;
	}

	while (m_angle < 0.0f)
	{
		m_angle += DirectX::XM_2PI;
	}
}
