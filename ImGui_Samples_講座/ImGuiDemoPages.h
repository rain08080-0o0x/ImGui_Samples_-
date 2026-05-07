#pragma once

#include <memory>
#include <vector>

class ImGuiDemoPage;

std::vector<std::unique_ptr<ImGuiDemoPage>> CreateImGuiDemoPages();
