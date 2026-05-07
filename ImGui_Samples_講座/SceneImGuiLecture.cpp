#include "SceneImGuiLecture.h"

#include <cstring>

#include "ImGuiDemoPage.h"
#include "ImGuiDemoPages.h"
#include "imgui.h"

SceneImGuiLecture::SceneImGuiLecture()
	: m_pages(CreateImGuiDemoPages())
{
}

void SceneImGuiLecture::Update()
{
}

void SceneImGuiLecture::Draw()
{
	DrawDockSpace();
	DrawSelector();
	DrawPages();
}

void SceneImGuiLecture::DrawDockSpace()
{
	ImGuiIO& io = ImGui::GetIO();
	if ((io.ConfigFlags & ImGuiConfigFlags_DockingEnable) == 0)
	{
		return;
	}

	ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
}

void SceneImGuiLecture::DrawSelector()
{
	const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowViewport(mainViewport->ID);
	ImGui::SetNextWindowPos(
		ImVec2(mainViewport->WorkPos.x + 20.0f, mainViewport->WorkPos.y + 20.0f),
		ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(360.0f, 520.0f), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin(
		"講座セレクター",
		nullptr,
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::End();
		return;
	}

	ImGui::TextUnformatted("PPTX 1枚 = ImGui 1ウィンドウ");
	ImGui::TextUnformatted("チェックボックスで各スライドの表示を切り替えます。");
	ImGui::SeparatorText("レイアウト");
	ImGui::BulletText("タイトルバーを別ウィンドウへドラッグすると、タブとしてドッキングできます。");
	ImGui::BulletText("ドッキングしたタブを外へ引っ張ると、別のネイティブウィンドウにできます。");
	ImGui::BulletText("このサンプルでは Docking と Multi-Viewport の両方を有効化しています。");

	if (ImGui::Button("全部表示"))
	{
		for (std::unique_ptr<ImGuiDemoPage>& page : m_pages)
		{
			page->SetOpen(true);
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("全部非表示"))
	{
		for (std::unique_ptr<ImGuiDemoPage>& page : m_pages)
		{
			page->SetOpen(false);
		}
	}

	ImGui::Separator();

	const char* currentCategory = nullptr;
	for (std::unique_ptr<ImGuiDemoPage>& page : m_pages)
	{
		if (currentCategory == nullptr || strcmp(currentCategory, page->GetCategory()) != 0)
		{
			currentCategory = page->GetCategory();
			ImGui::SeparatorText(currentCategory);
		}

		bool isOpen = page->IsOpen();
		if (ImGui::Checkbox(page->GetTitle(), &isOpen))
		{
			page->SetOpen(isOpen);
		}
	}

	ImGui::End();
}

void SceneImGuiLecture::DrawPages()
{
	for (std::unique_ptr<ImGuiDemoPage>& page : m_pages)
	{
		page->DrawWindow();
	}
}
