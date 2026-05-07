#include "ImGuiDemoPage.h"

#include "imgui.h"

ImGuiDemoPage::ImGuiDemoPage(const char* title, const char* category, bool isOpen)
	: m_title(title)
	, m_category(category)
	, m_isOpen(isOpen)
{
}

const char* ImGuiDemoPage::GetTitle() const
{
	return m_title.c_str();
}

const char* ImGuiDemoPage::GetCategory() const
{
	return m_category.c_str();
}

bool ImGuiDemoPage::IsOpen() const
{
	return m_isOpen;
}

void ImGuiDemoPage::SetOpen(bool isOpen)
{
	m_isOpen = isOpen;
}

void ImGuiDemoPage::DrawWindow()
{
	if (!m_isOpen)
	{
		return;
	}

	ImGui::SetNextWindowSize(ImVec2(460.0f, 0.0f), ImGuiCond_FirstUseEver);
	if (ImGui::Begin(m_title.c_str(), &m_isOpen))
	{
		DrawContents();
	}
	ImGui::End();
}

void ImGuiDemoPage::DrawIntro(const char* summary, const char* apiList) const
{
	ImGui::TextWrapped("%s", summary);
	ImGui::SeparatorText("使用API");
	ImGui::TextWrapped("%s", apiList);
}

void ImGuiDemoPage::DrawCodeBlock(const char* label, const char* code) const
{
	ImGui::SeparatorText(label);
	ImGui::BeginChild(label, ImVec2(0.0f, 120.0f), true);
	ImGui::TextUnformatted(code);
	ImGui::EndChild();
}
