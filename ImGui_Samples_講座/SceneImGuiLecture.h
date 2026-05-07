#pragma once

#include <memory>
#include <vector>

#include "Scene.h"

class ImGuiDemoPage;

class SceneImGuiLecture : public Scene
{
public:
	SceneImGuiLecture();
	~SceneImGuiLecture() override = default;

	void Update() override;
	void Draw() override;

private:
	void DrawDockSpace();
	void DrawSelector();
	void DrawPages();

	std::vector<std::unique_ptr<ImGuiDemoPage>> m_pages;
};
