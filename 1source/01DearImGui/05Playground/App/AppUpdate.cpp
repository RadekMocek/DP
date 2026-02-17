#include "App.hpp"

void App::Update()
{
    const auto io = ImGui::GetIO();

    // State
    static bool show_popup_window = false;
    static bool show_demo_window = false;

    // Main menu bar
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Menu")) {
        if (ImGui::MenuItem("Pop-up", nullptr, show_popup_window)) {
            show_popup_window = !show_popup_window;
        }
        if (ImGui::MenuItem("Demo", nullptr, show_demo_window)) {
            show_demo_window = !show_demo_window;
        }
        if (ImGui::MenuItem("Exit", "Alt+F4")) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    // Fullscreen window setup
    constexpr ImGuiWindowFlags flags_window = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    static bool show_main_window = true;

    // Fullscreen window begin
    ImGui::Begin("Hello Counter", &show_main_window, flags_window);

    ImGui::End();

    // Pop-up window
    if (show_popup_window) {
        ImGui::Begin("Pop-up window");

        ImGui::Text("Not much you can do here...");

        if (ImGui::Button("Close")) {
            show_popup_window = false;
        }

        ImGui::End();
    }
    if (show_demo_window) {
        ImGui::ShowDemoWindow();
    }

    ImGui::Begin("Issue demonstration");

    constexpr auto INPUT_HEIGHT = 8;
    static ImGuiInputTextFlags flags_issue = ImGuiInputTextFlags_None;
    ImGui::CheckboxFlags("ImGuiInputTextFlags_ReadOnly", &flags_issue, ImGuiInputTextFlags_ReadOnly);
    ImGui::CheckboxFlags("ImGuiInputTextFlags_NoHorizontalScroll", &flags_issue, ImGuiInputTextFlags_NoHorizontalScroll);
    ImGui::CheckboxFlags("ImGuiInputTextFlags_ElideLeft", &flags_issue, ImGuiInputTextFlags_ElideLeft);

    static char text[1024 * INPUT_HEIGHT] = "abcde ABCDE\nfghij FGHIJ\nklmno KLMNO\npqrstu PQRSTU";
    ImGui::Text("Default style:");
    ImGui::InputTextMultiline("##source1", text, IM_ARRAYSIZE(text),
                              ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * INPUT_HEIGHT), flags_issue);

    ImGui::Text("Zero frame padding:");
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    ImGui::InputTextMultiline("##source2", text, IM_ARRAYSIZE(text),
                              ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * INPUT_HEIGHT), flags_issue);
    ImGui::PopStyleVar();

    ImGui::Text("io.MouseWheel: %.1f", io.MouseWheel);
    if (io.KeyShift) {
        ImGui::Text("io.KeyShift");
    }

    ImGui::End();
}
