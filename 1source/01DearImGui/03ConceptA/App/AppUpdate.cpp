#include "App.hpp"

void App::Update()
{
    // Implicit font: inconsolata_14

    static bool show_demo_window = false;
    static bool is_about_popup_queued = false;

    // Main menu bar
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Debug")) {
        if (ImGui::MenuItem("Dear ImGui demo window", nullptr, show_demo_window)) {
            show_demo_window = !show_demo_window;
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help")) {
        if (ImGui::MenuItem("About...")) {
            is_about_popup_queued = true;
        }
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();    

    // Main "fullscreen" window
    ModuleMain();

    // Show the big demo window
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    // Show about modal
    if (is_about_popup_queued) {
        is_about_popup_queued = false;
        ImGui::OpenPopup("About...##modal");
    }
    // Always center this window when appearing
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal("About...##modal", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {        
        ImGui::TextLinkOpenURL("https://github.com/RadekMocek/DP", "https://github.com/RadekMocek/DP");
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        if (ImGui::Button("Close", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }        
        ImGui::EndPopup();
    }    
}
