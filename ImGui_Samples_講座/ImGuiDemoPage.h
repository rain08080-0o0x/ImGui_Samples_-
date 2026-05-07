#pragma once

#include <string>

class ImGuiDemoPage
{
public:
	ImGuiDemoPage(const char* title, const char* category, bool isOpen);
	virtual ~ImGuiDemoPage() = default;

	const char* GetTitle() const;
	const char* GetCategory() const;
	bool IsOpen() const;
	void SetOpen(bool isOpen);
	void DrawWindow();

protected:
	void DrawIntro(const char* summary, const char* apiList) const;
	void DrawCodeBlock(const char* label, const char* code) const;
	virtual void DrawContents() = 0;

private:
	std::string m_title;
	std::string m_category;
	bool m_isOpen;
};
