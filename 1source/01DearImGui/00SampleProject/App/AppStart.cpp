#include "App.hpp"

void App::Start()
{
    constexpr bool do_forever_blurry_showcase = false;

    // Load Fonts
    ImGuiIO& io = ImGui::GetIO();
    
    if (do_forever_blurry_showcase) {
        io.Fonts->AddFontDefaultVector();
        m_font_proggyforever = io.Fonts->AddFontFromFileTTF("./Resource/ProggyForever-Regular.ttf");
    }
    else {
        m_font_inconsolata = io.Fonts->AddFontFromFileTTF("./Resource/Inconsolata-Medium.ttf");
    }

    // Our state
    m_show_demo_window = true;
    m_show_hello_window = true;
    m_show_another_window = true;
    m_show_testing_window = do_forever_blurry_showcase;
}
