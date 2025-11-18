#include "../Misc/imgui_stdlib.h"

#include "../App.hpp"

void App::ModuleTextEditor()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
    
    static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
    ImGui::InputTextMultiline("##source", &m_source, ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, ImGui::GetContentRegionAvail().y - m_fps_info_size.y), flags);
    
    ImGui::PopStyleVar();
}
