#pragma once

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	void RootUpdate();
	void RootDraw();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};
