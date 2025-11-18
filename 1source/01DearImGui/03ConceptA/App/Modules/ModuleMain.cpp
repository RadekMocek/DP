#include <format>

#include <imgui_internal.h>

#include "../App.hpp"

void App::ModuleMain()
{
    ImGui::PushFont(font_inconsolata_18);

    // Framerate info
    static ImGuiIO& io = ImGui::GetIO();
    std::string fps_info = std::format("Application average {} FPS", round(io.Framerate));
    m_fps_info_size = ImGui::CalcTextSize(fps_info.c_str());
    m_fps_info_size.y += 4;

    // Fullscreen window setup
    const ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::Begin("Main", nullptr, flags);

    // Two main columns
    ModuleTextEditor();
    ImGui::SameLine();
    ModuleCanvas();

    ImGui::SetCursorPosX(/*ImGui::GetCursorPosX() + */ImMax(0.0f, ImGui::GetContentRegionAvail().x - m_fps_info_size.x));
    ImGui::Text(fps_info.c_str());

    ImGui::End();

    ImGui::PopFont();
}
