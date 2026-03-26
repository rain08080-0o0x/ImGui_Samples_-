#pragma once

#include <DirectXMath.h>

#include "Scene.h"
#include "SceneGameCamera.h"

struct SceneObjectTransform
{
	DirectX::XMFLOAT3 position{ 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 rotation{ 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 scale{ 1.0f, 1.0f, 1.0f };
};

class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame() override = default;

	void Update() override;
	void Draw() override;

	const SceneObjectTransform& GetGroundTransform() const;
	void SetGroundTransform(const SceneObjectTransform& transform);

	const SceneObjectTransform& GetBoxTransform() const;
	void SetBoxTransform(const SceneObjectTransform& transform);

	const SceneObjectTransform& GetCylinderTransform() const;
	void SetCylinderTransform(const SceneObjectTransform& transform);

	const SceneGameCamera& GetCamera() const;
	SceneGameCamera& GetCamera();

private:
	void SetupRenderState() const;
	void ApplyCamera() const;
	void DrawSceneObjects() const;
	void DrawEditor();
	float GetAspectRatio() const;

	SceneObjectTransform m_groundTransform;
	SceneObjectTransform m_boxTransform;
	SceneObjectTransform m_cylinderTransform;
	SceneGameCamera m_camera;
};
