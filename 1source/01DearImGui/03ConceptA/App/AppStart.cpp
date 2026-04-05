#include "App.hpp"

void App::Start()
{
    ImGuiIO& io = ImGui::GetIO();

    /*
    m_font_default = io.Fonts->AddFontDefault();
    IM_ASSERT(m_font_default != nullptr);
    /**/

    m_font_inconsolata_14 = io.Fonts->AddFontFromFileTTF("./App/Resources/Inconsolata-Medium.ttf", 14.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
    IM_ASSERT(m_font_inconsolata_14 != nullptr);

    m_font_inconsolata_18 = io.Fonts->AddFontFromFileTTF("./App/Resources/Inconsolata-Medium.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
    IM_ASSERT(m_font_inconsolata_18 != nullptr);    
}
