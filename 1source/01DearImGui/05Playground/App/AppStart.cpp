#include "App.hpp"

void App::Start()
{
    ImGuiIO& io = ImGui::GetIO();

    ImFont* font = io.Fonts->AddFontFromFileTTF("./App/Resources/Inconsolata-Medium.ttf", 26.0f);

    IM_ASSERT(font != nullptr);


}
