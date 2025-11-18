#include "App.hpp"

void App::Update()
{
    // Implicit font: inconsolata_14

    static bool show_demo_window = false;

    // Show the big demo window
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    // Main menu bar
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Debug")) {
        if (ImGui::MenuItem("Dear ImGui demo window", nullptr, show_demo_window)) {
            show_demo_window = !show_demo_window;
        }
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();    

    // Main "fullscreen" window
    ModuleMain();
}
