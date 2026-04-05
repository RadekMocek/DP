#include "App.hpp"

void App::Start()
{
    // Load Fonts
    ImGuiIO& io = ImGui::GetIO();
    
    //io.Fonts->AddFontDefaultVector();
    io.Fonts->AddFontDefaultBitmap();

    font_inconsolata_medium = io.Fonts->AddFontFromFileTTF("./Resource/Inconsolata-Medium.ttf");

    // Our state
    show_demo_window = true;
    show_hello_window = false;
    show_another_window = false;
    show_testing_window = true;
}
