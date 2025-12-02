#include "App.hpp"

void App::Update()
{
    // State
    static int counter = 1;
    static bool show_popup_window = false;

    // Const
    constexpr ImVec2 button_size(35, 0);

    // Main menu bar
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Pop-up", nullptr, show_popup_window))
        {
            show_popup_window = !show_popup_window;
        }
        if (ImGui::MenuItem("Exit", "Alt+F4"))
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    // Fullscreen window setup
    constexpr ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    static bool show_main_window = true;

    // Fullscreen window begin
    ImGui::Begin("Hello Counter", &show_main_window, flags);

    ImGui::BeginDisabled(counter == 1);
    if (ImGui::Button("-", button_size))
    {
        counter--;
    }
    ImGui::EndDisabled();

    ImGui::SameLine();

    ImGui::Text("%d", counter);

    ImGui::SameLine();

    ImGui::BeginDisabled(counter == 5);
    if (ImGui::Button("+", button_size))
    {
        counter++;
    }
    ImGui::EndDisabled();

    if (counter == 3)
    {
        ImGui::Text("Hello!");
    }

    ImGui::End();

    // Pop-up window
    if (show_popup_window)
    {
        ImGui::Begin("Pop-up window");

        ImGui::Text("Not much you can do here...");

        if (ImGui::Button("Close"))
        {
            show_popup_window = false;
        }

        ImGui::End();
    }
}
