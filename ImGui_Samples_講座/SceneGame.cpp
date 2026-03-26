#include "SceneGame.h"

#include "Defines.h"
#include "DirectX.h"
#include "Geometory.h"
#include "Texture.h"
#include "imgui.h"

namespace
{
	DirectX::XMFLOAT4X4 ToFloat4x4(const DirectX::XMMATRIX& matrix)
	{
		DirectX::XMFLOAT4X4 value{};
		DirectX::XMStoreFloat4x4(&value, matrix);
		return value;
	}

	DirectX::XMFLOAT4X4 MakeWorldMatrix(const SceneObjectTransform& transform)
	{
		const DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(
			transform.scale.x,
			transform.scale.y,
			transform.scale.z);
		const DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(
			DirectX::XMConvertToRadians(transform.rotation.x),
			DirectX::XMConvertToRadians(transform.rotation.y),
			DirectX::XMConvertToRadians(transform.rotation.z));
		const DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(
			transform.position.x,
			transform.position.y,
			transform.position.z);
		return ToFloat4x4(DirectX::XMMatrixTranspose(scale * rotation * translation));
	}

	void AddGrid(float halfSize, float step)
	{
		const DirectX::XMFLOAT4 gridColor(0.35f, 0.40f, 0.48f, 1.0f);
		for (float position = -halfSize; position <= halfSize; position += step)
		{
			Geometory::AddLine(
				DirectX::XMFLOAT3(position, 0.0f, -halfSize),
				DirectX::XMFLOAT3(position, 0.0f, halfSize),
				gridColor);
			Geometory::AddLine(
				DirectX::XMFLOAT3(-halfSize, 0.0f, position),
				DirectX::XMFLOAT3(halfSize, 0.0f, position),
				gridColor);
		}

		Geometory::AddLine(
			DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT3(2.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT4(1.0f, 0.2f, 0.2f, 1.0f));
		Geometory::AddLine(
			DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT3(0.0f, 2.0f, 0.0f),
			DirectX::XMFLOAT4(0.2f, 1.0f, 0.2f, 1.0f));
		Geometory::AddLine(
			DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT3(0.0f, 0.0f, 2.0f),
			DirectX::XMFLOAT4(0.2f, 0.5f, 1.0f, 1.0f));
	}

	bool EditTransformGui(const char* label, SceneObjectTransform* transform)
	{
		bool changed = false;

		if (ImGui::TreeNode(label))
		{
			ImGui::PushID(label);
			changed |= ImGui::DragFloat3("Position", &transform->position.x, 0.05f);
			changed |= ImGui::DragFloat3("Rotation", &transform->rotation.x, 1.0f);
			changed |= ImGui::DragFloat3("Scale", &transform->scale.x, 0.05f, 0.01f, 100.0f);
			ImGui::PopID();
			ImGui::TreePop();
		}

		return changed;
	}
}

SceneGame::SceneGame()
{
	m_groundTransform.position = DirectX::XMFLOAT3(0.0f, -0.6f, 0.0f);
	m_groundTransform.scale = DirectX::XMFLOAT3(5.0f, 0.15f, 5.0f);

	m_boxTransform.position = DirectX::XMFLOAT3(0.0f, 0.85f, 0.0f);
	m_boxTransform.rotation = DirectX::XMFLOAT3(20.0f, 0.0f, 0.0f);

	m_cylinderTransform.position = DirectX::XMFLOAT3(-1.7f, 0.2f, 0.0f);
	m_cylinderTransform.scale = DirectX::XMFLOAT3(0.35f, 0.9f, 0.35f);

	SetupRenderState();
}

const SceneObjectTransform& SceneGame::GetGroundTransform() const
{
	return m_groundTransform;
}

void SceneGame::SetGroundTransform(const SceneObjectTransform& transform)
{
	m_groundTransform = transform;
}

const SceneObjectTransform& SceneGame::GetBoxTransform() const
{
	return m_boxTransform;
}

void SceneGame::SetBoxTransform(const SceneObjectTransform& transform)
{
	m_boxTransform = transform;
}

const SceneObjectTransform& SceneGame::GetCylinderTransform() const
{
	return m_cylinderTransform;
}

void SceneGame::SetCylinderTransform(const SceneObjectTransform& transform)
{
	m_cylinderTransform = transform;
}

const SceneGameCamera& SceneGame::GetCamera() const
{
	return m_camera;
}

SceneGameCamera& SceneGame::GetCamera()
{
	return m_camera;
}

void SceneGame::Update()
{
	m_camera.Update();
}

void SceneGame::Draw()
{
	SetupRenderState();
	ApplyCamera();
	DrawSceneObjects();
	// ImGui•`‰æ
	
	//DrawEditor();
}

void SceneGame::SetupRenderState() const
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);
	SetDepthTest(true);
}

void SceneGame::ApplyCamera() const
{
	Geometory::SetView(m_camera.GetViewMatrix());
	Geometory::SetProjection(m_camera.GetProjectionMatrix(GetAspectRatio()));
}

void SceneGame::DrawSceneObjects() const
{
	Geometory::SetWorld(MakeWorldMatrix(m_groundTransform));
	Geometory::DrawBox();

	Geometory::SetWorld(MakeWorldMatrix(m_boxTransform));
	Geometory::DrawBox();

	Geometory::SetWorld(MakeWorldMatrix(m_cylinderTransform));
	Geometory::DrawCylinder();

	AddGrid(DEBUG_GRID_NUM * DEBUG_GRID_MARGIN, DEBUG_GRID_MARGIN);
	Geometory::DrawLines();
}

void SceneGame::DrawEditor()
{
	if (!ImGui::Begin("SceneGame Editor"))
	{
		ImGui::End();
		return;
	}

	ImGui::TextUnformatted("Edit camera and transforms.");

	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool autoRotate = m_camera.GetAutoRotate();
		if (ImGui::Checkbox("Auto Rotate", &autoRotate))
		{
			m_camera.SetAutoRotate(autoRotate);
		}

		float angle = m_camera.GetAngle();
		if (ImGui::SliderAngle("Angle", &angle))
		{
			m_camera.SetAngle(angle);
		}

		float rotationSpeed = m_camera.GetRotationSpeed();
		if (ImGui::DragFloat("Rotate Speed", &rotationSpeed, 0.0005f, 0.0f, 0.2f, "%.4f"))
		{
			m_camera.SetRotationSpeed(rotationSpeed);
		}

		float radius = m_camera.GetRadius();
		if (ImGui::DragFloat("Radius", &radius, 0.05f, 0.1f, 50.0f))
		{
			m_camera.SetRadius(radius);
		}

		float height = m_camera.GetHeight();
		if (ImGui::DragFloat("Height", &height, 0.05f, -50.0f, 50.0f))
		{
			m_camera.SetHeight(height);
		}

		DirectX::XMFLOAT3 target = m_camera.GetTarget();
		if (ImGui::DragFloat3("Target", &target.x, 0.05f))
		{
			m_camera.SetTarget(target);
		}

		float fovDegrees = m_camera.GetFovDegrees();
		if (ImGui::SliderFloat("FOV", &fovDegrees, 10.0f, 170.0f, "%.1f deg"))
		{
			m_camera.SetFovDegrees(fovDegrees);
		}
	}

	if (ImGui::CollapsingHeader("Objects", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::TextUnformatted("Rotation values are degrees.");

		SceneObjectTransform ground = GetGroundTransform();
		if (EditTransformGui("Ground", &ground))
		{
			SetGroundTransform(ground);
		}

		SceneObjectTransform box = GetBoxTransform();
		if (EditTransformGui("Box", &box))
		{
			SetBoxTransform(box);
		}

		SceneObjectTransform cylinder = GetCylinderTransform();
		if (EditTransformGui("Cylinder", &cylinder))
		{
			SetCylinderTransform(cylinder);
		}
	}

	ImGui::End();
}

float SceneGame::GetAspectRatio() const
{
	const RenderTarget* pRTV = GetDefaultRTV();
	if (!pRTV || pRTV->GetHeight() == 0)
	{
		return 1.0f;
	}

	return static_cast<float>(pRTV->GetWidth()) / static_cast<float>(pRTV->GetHeight());
}
