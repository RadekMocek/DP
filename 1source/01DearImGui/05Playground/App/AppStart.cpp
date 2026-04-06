#include "App.hpp"

void App::Start()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.FontSizeBase = 26.0f;

    ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontDefaultVector();
    //io.Fonts->AddFontDefaultBitmap();
    ImFont* font = io.Fonts->AddFontFromFileTTF("./App/Resources/Inconsolata-Medium.ttf");

    IM_ASSERT(font != nullptr);
}
