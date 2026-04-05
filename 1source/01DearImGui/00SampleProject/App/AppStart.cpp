#include "App.hpp"

void App::Start()
{
    // Load Fonts
    ImGuiIO& io = ImGui::GetIO();
    
    //io.Fonts->AddFontDefaultVector();
    //io.Fonts->AddFontDefaultBitmap();

    //m_font_proggyclean = io.Fonts->AddFontFromFileTTF("./Resource/ProggyClean.ttf");
    //m_font_proggyforever = io.Fonts->AddFontFromFileTTF("./Resource/ProggyForever-Regular.ttf");
    m_font_inconsolata = io.Fonts->AddFontFromFileTTF("./Resource/Inconsolata-Medium.ttf");

    // Our state
    m_show_demo_window = true;
    m_show_hello_window = true;
    m_show_another_window = true;
    m_show_testing_window = false;
}
