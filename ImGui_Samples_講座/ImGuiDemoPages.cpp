#include "ImGuiDemoPages.h"

#include <memory>
#include <vector>

#include "ImGuiDemoPage.h"
#include "imgui.h"

namespace
{
	class Slide01WindowBasicsPage : public ImGuiDemoPage
	{
	public:
		Slide01WindowBasicsPage()
			: ImGuiDemoPage("スライド 01 - ウィンドウの基本", "基本", true)
			, m_sampleWindowOpen(true)
		{
		}

	protected:
		void DrawContents() override
		{
			DrawIntro(
				"ImGui のウィンドウは Begin/End で囲って作ります。このページ自体も Begin/End で表示されています。",
				"ImGui::Begin\nImGui::End\nImGui::SetNextWindowSize\nImGui::BeginChild");

			ImGui::SeparatorText("動作サンプル");
			ImGui::Checkbox("ネストしたサンプルウィンドウを開く", &m_sampleWindowOpen);
			if (m_sampleWindowOpen)
			{
				ImGui::SetNextWindowSize(ImVec2(280.0f, 140.0f), ImGuiCond_FirstUseEver);
				if (ImGui::Begin("ネストしたウィンドウ例", &m_sampleWindowOpen))
				{
					ImGui::TextUnformatted("これは別の ImGui ウィンドウです。");
					ImGui::BeginChild("ChildRegion", ImVec2(0.0f, 60.0f), true);
					ImGui::TextWrapped("BeginChild/EndChild を使うと、ウィンドウ内に別の描画領域を作れます。");
					ImGui::EndChild();
				}
				ImGui::End();
			}

			DrawCodeBlock("コード例", R"CODE(
ImGui::SetNextWindowSize(ImVec2(420, 0), ImGuiCond_FirstUseEver);
if (ImGui::Begin("スライド 01 - ウィンドウの基本", &isOpen))
{
    ImGui::TextUnformatted("ここにウィンドウの内容を書きます。");
}
ImGui::End();
)CODE");
		}

	private:
		bool m_sampleWindowOpen;
	};

	class Slide02TextPage : public ImGuiDemoPage
	{
	public:
		Slide02TextPage()
			: ImGuiDemoPage("スライド 02 - 文字表示 API", "基本", true)
		{
		}

	protected:
		void DrawContents() override
		{
			DrawIntro(
				"文字を出す API は Dear ImGui の最初の入口です。まずは表示系から触ると流れを追いやすいです。",
				"ImGui::TextUnformatted, ImGui::BulletText, ImGui::TextColored, ImGui::SeparatorText");

			ImGui::SeparatorText("動作サンプル");
			ImGui::TextUnformatted("通常のテキスト");
			ImGui::BulletText("箇条書きテキスト");
			ImGui::TextColored(ImVec4(0.25f, 0.85f, 0.45f, 1.0f), "色付きテキスト");
			ImGui::SeparatorText("折り返しテキスト");
			ImGui::TextWrapped("TextWrapped は説明文のような長い文章をウィンドウ幅に合わせて折り返すときに便利です。");

			DrawCodeBlock("コード例", R"CODE(
ImGui::TextUnformatted("通常のテキスト");
ImGui::BulletText("箇条書きテキスト");
ImGui::TextColored(ImVec4(0.25f, 0.85f, 0.45f, 1.0f), "色付きテキスト");
)CODE");
		}
	};

	class Slide03ButtonPage : public ImGuiDemoPage
	{
	public:
		Slide03ButtonPage()
			: ImGuiDemoPage("スライド 03 - ボタン API", "ウィジェット", true)
			, m_counter(0)
			, m_smallCounter(0)
			, m_arrowCounter(0)
		{
		}

	protected:
		void DrawContents() override
		{
			DrawIntro(
				"ボタン系ウィジェットは、押した瞬間に処理を発火させるための基本部品です。",
				"ImGui::Button, ImGui::SmallButton, ImGui::ArrowButton, ImGui::SameLine");

			ImGui::SeparatorText("動作サンプル");
			if (ImGui::Button("カウントアップ"))
			{
				++m_counter;
			}
			ImGui::SameLine();
			ImGui::Text("通常=%d", m_counter);

			if (ImGui::SmallButton("小"))
			{
				++m_smallCounter;
			}
			ImGui::SameLine();
			ImGui::Text("小ボタン=%d", m_smallCounter);

			if (ImGui::ArrowButton("右矢印", ImGuiDir_Right))
			{
				++m_arrowCounter;
			}
			ImGui::SameLine();
			ImGui::Text("矢印=%d", m_arrowCounter);

			DrawCodeBlock("コード例", R"CODE(
if (ImGui::Button("カウントアップ"))
{
    ++counter;
}

if (ImGui::SmallButton("小"))
{
    ++smallCounter;
}
)CODE");
		}

	private:
		int m_counter;
		int m_smallCounter;
		int m_arrowCounter;
	};

	class Slide04SelectionPage : public ImGuiDemoPage
	{
	public:
		Slide04SelectionPage()
			: ImGuiDemoPage("スライド 04 - チェックボックスとラジオ", "ウィジェット", false)
			, m_showGrid(true)
			, m_debugMode(false)
			, m_layoutMode(0)
		{
		}

	protected:
		void DrawContents() override
		{
			DrawIntro(
				"選択系ウィジェットは、機能の ON/OFF やモード切り替えを見せるときに向いています。",
				"ImGui::Checkbox, ImGui::RadioButton");

			ImGui::SeparatorText("動作サンプル");
			ImGui::Checkbox("グリッドを表示", &m_showGrid);
			ImGui::Checkbox("デバッグモード", &m_debugMode);
			ImGui::RadioButton("簡易", &m_layoutMode, 0);
			ImGui::SameLine();
			ImGui::RadioButton("詳細", &m_layoutMode, 1);
			ImGui::SameLine();
			ImGui::RadioButton("コンパクト", &m_layoutMode, 2);
			ImGui::Text("現在のモード: %d", m_layoutMode);

			DrawCodeBlock("コード例", R"CODE(
ImGui::Checkbox("グリッドを表示", &showGrid);
ImGui::RadioButton("簡易", &mode, 0);
ImGui::RadioButton("詳細", &mode, 1);
)CODE");
		}

	private:
		bool m_showGrid;
		bool m_debugMode;
		int m_layoutMode;
	};

	class Slide05InputPage : public ImGuiDemoPage
	{
	public:
		Slide05InputPage()
			: ImGuiDemoPage("スライド 05 - 入力 API", "ウィジェット", false)
			, m_sampleInt(3)
			, m_sampleFloat(1.5f)
		{
			m_textBuffer[0] = 'I';
			m_textBuffer[1] = 'm';
			m_textBuffer[2] = 'G';
			m_textBuffer[3] = 'u';
			m_textBuffer[4] = 'i';
			m_textBuffer[5] = '\0';
		}

	protected:
		void DrawContents() override
		{
			DrawIntro(
				"入力系ウィジェットは、文字・整数・小数などをその場で編集させるために使います。",
				"ImGui::InputText, ImGui::InputInt, ImGui::InputFloat");

			ImGui::SeparatorText("動作サンプル");
			ImGui::InputText("文字列", m_textBuffer, sizeof(m_textBuffer));
			ImGui::InputInt("整数", &m_sampleInt);
			ImGui::InputFloat("小数", &m_sampleFloat, 0.1f, 1.0f, "%.2f");

			DrawCodeBlock("コード例", R"CODE(
char text[64] = "ImGui";
int sampleInt = 3;
float sampleFloat = 1.5f;

ImGui::InputText("文字列", text, sizeof(text));
ImGui::InputInt("整数", &sampleInt);
ImGui::InputFloat("小数", &sampleFloat);
)CODE");
		}

	private:
		char m_textBuffer[64];
		int m_sampleInt;
		float m_sampleFloat;
	};

	class Slide06SliderPage : public ImGuiDemoPage
	{
	public:
		Slide06SliderPage()
			: ImGuiDemoPage("スライド 06 - スライダーとドラッグ", "ウィジェット", false)
			, m_alpha(0.5f)
			, m_quality(2)
		{
			m_position[0] = 0.0f;
			m_position[1] = 1.0f;
			m_position[2] = 2.0f;
		}

	protected:
		void DrawContents() override
		{
			DrawIntro(
				"スライダーやドラッグ操作は、数値を感覚的に調整させたい場面で使います。",
				"ImGui::SliderFloat, ImGui::SliderInt, ImGui::DragFloat3");

			ImGui::SeparatorText("動作サンプル");
			ImGui::SliderFloat("透明度", &m_alpha, 0.0f, 1.0f, "%.2f");
			ImGui::SliderInt("品質", &m_quality, 0, 5);
			ImGui::DragFloat3("位置", m_position, 0.05f);

			DrawCodeBlock("コード例", R"CODE(
ImGui::SliderFloat("透明度", &alpha, 0.0f, 1.0f);
ImGui::SliderInt("品質", &quality, 0, 5);
ImGui::DragFloat3("位置", position, 0.05f);
)CODE");
		}

	private:
		float m_alpha;
		int m_quality;
		float m_position[3];
	};

	class Slide07ChoicePage : public ImGuiDemoPage
	{
	public:
		Slide07ChoicePage()
			: ImGuiDemoPage("スライド 07 - コンボとリスト", "ウィジェット", false)
			, m_comboIndex(0)
			, m_listIndex(1)
		{
		}

	protected:
		void DrawContents() override
		{
			static const char* kOptions[] = {
				"ウィンドウ",
				"テキスト",
				"ボタン",
				"入力",
				"テーブル"
			};

			DrawIntro(
				"候補から 1 つ選ばせたいときは、コンボボックスやリストボックスが使いやすいです。",
				"ImGui::Combo, ImGui::ListBox");

			ImGui::SeparatorText("動作サンプル");
			ImGui::Combo("コンボ", &m_comboIndex, kOptions, 5);
			ImGui::ListBox("リスト", &m_listIndex, kOptions, 5, 4);
			ImGui::Text("コンボ=%s", kOptions[m_comboIndex]);
			ImGui::Text("リスト=%s", kOptions[m_listIndex]);

			DrawCodeBlock("コード例", R"CODE(
static const char* options[] = { "A", "B", "C" };
ImGui::Combo("コンボ", &comboIndex, options, 3);
ImGui::ListBox("リスト", &listIndex, options, 3, 3);
)CODE");
		}

	private:
		int m_comboIndex;
		int m_listIndex;
	};

	class Slide08TreePage : public ImGuiDemoPage
	{
	public:
		Slide08TreePage()
			: ImGuiDemoPage("スライド 08 - ツリーとヘッダー", "レイアウト", false)
			, m_selectedNode(0)
		{
		}

	protected:
		void DrawContents() override
		{
			DrawIntro(
				"ツリー系ウィジェットは、階層構造や折りたたみ表示を教えるときに便利です。",
				"ImGui::CollapsingHeader, ImGui::TreeNode, ImGui::Selectable");

			ImGui::SeparatorText("動作サンプル");
			if (ImGui::CollapsingHeader("シーンノード", ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (ImGui::TreeNode("プレイヤー"))
				{
					if (ImGui::Selectable("座標", m_selectedNode == 0))
					{
						m_selectedNode = 0;
					}
					if (ImGui::Selectable("ステータス", m_selectedNode == 1))
					{
						m_selectedNode = 1;
					}
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("敵"))
				{
					if (ImGui::Selectable("AI", m_selectedNode == 2))
					{
						m_selectedNode = 2;
					}
					if (ImGui::Selectable("ドロップ表", m_selectedNode == 3))
					{
						m_selectedNode = 3;
					}
					ImGui::TreePop();
				}
			}
			ImGui::Text("選択中ノード: %d", m_selectedNode);

			DrawCodeBlock("コード例", R"CODE(
if (ImGui::CollapsingHeader("シーンノード"))
{
    if (ImGui::TreeNode("プレイヤー"))
    {
        ImGui::Selectable("座標", selected == 0);
        ImGui::TreePop();
    }
}
)CODE");
		}

	private:
		int m_selectedNode;
	};

	class Slide09TablePage : public ImGuiDemoPage
	{
	public:
		Slide09TablePage()
			: ImGuiDemoPage("スライド 09 - テーブル API", "レイアウト", false)
		{
		}

	protected:
		void DrawContents() override
		{
			DrawIntro(
				"テーブルは一覧表示やデータ確認、エディタ向け UI を作るときに役立ちます。",
				"ImGui::BeginTable, ImGui::TableSetupColumn, ImGui::TableHeadersRow, ImGui::TableNextRow");

			ImGui::SeparatorText("動作サンプル");
			if (ImGui::BeginTable("ApiTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
			{
				ImGui::TableSetupColumn("API");
				ImGui::TableSetupColumn("分類");
				ImGui::TableSetupColumn("用途");
				ImGui::TableHeadersRow();

				static const char* kRows[][3] = {
					{"Button", "ウィジェット", "処理を発火する"},
					{"InputText", "ウィジェット", "文字列を受け取る"},
					{"BeginTable", "レイアウト", "表形式で表示する"}
				};

				for (int row = 0; row < 3; ++row)
				{
					ImGui::TableNextRow();
					for (int col = 0; col < 3; ++col)
					{
						ImGui::TableSetColumnIndex(col);
						ImGui::TextUnformatted(kRows[row][col]);
					}
				}
				ImGui::EndTable();
			}

			DrawCodeBlock("コード例", R"CODE(
if (ImGui::BeginTable("ApiTable", 3, ImGuiTableFlags_Borders))
{
    ImGui::TableSetupColumn("API");
    ImGui::TableHeadersRow();
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::TextUnformatted("Button");
    ImGui::EndTable();
}
)CODE");
		}
	};

	class Slide10PopupPage : public ImGuiDemoPage
	{
	public:
		Slide10PopupPage()
			: ImGuiDemoPage("スライド 10 - ポップアップとモーダル", "応用", false)
			, m_confirmed(false)
		{
		}

	protected:
		void DrawContents() override
		{
			DrawIntro(
				"ポップアップやモーダルは、確認ダイアログや一時的な操作画面を見せるときに使います。",
				"ImGui::OpenPopup, ImGui::BeginPopupModal, ImGui::CloseCurrentPopup");

			ImGui::SeparatorText("動作サンプル");
			if (ImGui::Button("確認ダイアログを開く"))
			{
				ImGui::OpenPopup("確認ダイアログ");
			}
			ImGui::Text("確定状態: %s", m_confirmed ? "true" : "false");

			if (ImGui::BeginPopupModal("確認ダイアログ", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::TextWrapped("これは確認ダイアログの教材用サンプルです。");
				if (ImGui::Button("OK", ImVec2(120.0f, 0.0f)))
				{
					m_confirmed = true;
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("キャンセル", ImVec2(120.0f, 0.0f)))
				{
					m_confirmed = false;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}

			DrawCodeBlock("コード例", R"CODE(
if (ImGui::Button("確認ダイアログを開く"))
{
    ImGui::OpenPopup("確認ダイアログ");
}

if (ImGui::BeginPopupModal("確認ダイアログ"))
{
    if (ImGui::Button("OK")) { ImGui::CloseCurrentPopup(); }
    ImGui::EndPopup();
}
)CODE");
		}

	private:
		bool m_confirmed;
	};

	class Slide11StylePage : public ImGuiDemoPage
	{
	public:
		Slide11StylePage()
			: ImGuiDemoPage("スライド 11 - スタイルと色", "応用", false)
		{
			m_color[0] = 0.20f;
			m_color[1] = 0.55f;
			m_color[2] = 0.90f;
			m_rounding = 6.0f;
		}

	protected:
		void DrawContents() override
		{
			DrawIntro(
				"スタイル API を使うと、色や角丸を変えながらテーマの考え方も説明できます。",
				"ImGui::ColorEdit3, ImGui::SliderFloat, ImGui::StyleColorsDark, ImGui::StyleColorsLight");

			ImGui::SeparatorText("動作サンプル");
			ImGui::ColorEdit3("アクセントカラー", m_color);
			ImGui::SliderFloat("角丸", &m_rounding, 0.0f, 16.0f);
			ImGuiStyle& style = ImGui::GetStyle();
			style.FrameRounding = m_rounding;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(m_color[0], m_color[1], m_color[2], 1.0f));
			ImGui::Button("スタイル付きボタン", ImVec2(180.0f, 0.0f));
			ImGui::PopStyleColor();

			if (ImGui::Button("ダーク"))
			{
				ImGui::StyleColorsDark();
			}
			ImGui::SameLine();
			if (ImGui::Button("ライト"))
			{
				ImGui::StyleColorsLight();
			}
			ImGui::SameLine();
			if (ImGui::Button("クラシック"))
			{
				ImGui::StyleColorsClassic();
			}

			DrawCodeBlock("コード例", R"CODE(
ImGui::ColorEdit3("アクセントカラー", accentColor);
ImGui::SliderFloat("角丸", &rounding, 0.0f, 16.0f);
ImGuiStyle& style = ImGui::GetStyle();
style.FrameRounding = rounding;
)CODE");
		}

	private:
		float m_color[3];
		float m_rounding;
	};

	class Slide12DockingPage : public ImGuiDemoPage
	{
	public:
		Slide12DockingPage()
			: ImGuiDemoPage("スライド 12 - Docking と Viewports", "応用", false)
		{
		}

	protected:
		void DrawContents() override
		{
			ImGuiIO& io = ImGui::GetIO();
			const bool dockingEnabled = (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) != 0;
			const bool viewportsEnabled = (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0;

			DrawIntro(
				"Docking は複数ウィンドウをタブ化してまとめる機能です。Multi-Viewport はウィンドウを外へ分離して別 OS ウィンドウ化する機能です。",
				"ImGuiConfigFlags_DockingEnable, ImGuiConfigFlags_ViewportsEnable, ImGui::DockSpaceOverViewport");

			ImGui::SeparatorText("動作サンプル");
			ImGui::Text("Docking: %s", dockingEnabled ? "有効" : "無効");
			ImGui::Text("Multi-Viewport: %s", viewportsEnabled ? "有効" : "無効");
			ImGui::Spacing();
			ImGui::BulletText("このウィンドウを別のスライドへドラッグしてみてください。");
			ImGui::BulletText("青いプレビューが出た位置で離すと、タブとしてドッキングされます。");
			ImGui::BulletText("ドッキングしたタブを外へ引っ張ると、別のネイティブウィンドウになります。");

			DrawCodeBlock("コード例", R"CODE(
ImGuiIO& io = ImGui::GetIO();
io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

ImGui::NewFrame();
ImGui::DockSpaceOverViewport();
)CODE");
		}
	};
}

std::vector<std::unique_ptr<ImGuiDemoPage>> CreateImGuiDemoPages()
{
	std::vector<std::unique_ptr<ImGuiDemoPage>> pages;
	pages.emplace_back(std::make_unique<Slide01WindowBasicsPage>());
	pages.emplace_back(std::make_unique<Slide02TextPage>());
	pages.emplace_back(std::make_unique<Slide03ButtonPage>());
	pages.emplace_back(std::make_unique<Slide04SelectionPage>());
	pages.emplace_back(std::make_unique<Slide05InputPage>());
	pages.emplace_back(std::make_unique<Slide06SliderPage>());
	pages.emplace_back(std::make_unique<Slide07ChoicePage>());
	pages.emplace_back(std::make_unique<Slide08TreePage>());
	pages.emplace_back(std::make_unique<Slide09TablePage>());
	pages.emplace_back(std::make_unique<Slide10PopupPage>());
	pages.emplace_back(std::make_unique<Slide11StylePage>());
	pages.emplace_back(std::make_unique<Slide12DockingPage>());
	return pages;
}
