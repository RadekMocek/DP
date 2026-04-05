#include "App.hpp"

void App::Start()
{
    const ImGuiIO& io = ImGui::GetIO();

    ImFont* font = io.Fonts->AddFontFromFileTTF("./Resource/Inconsolata-Medium.ttf", 26.0f);

    IM_ASSERT(font != nullptr);
}
