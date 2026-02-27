#include "App.hpp"

enum Choice
{
    Akat, Bliskavice, Cilovnici
};

// ReSharper disable once CppMemberFunctionMayBeConst
void App::Update()
{
    const auto io = ImGui::GetIO();

    // State
    static bool show_popup_window = false;
    static bool show_demo_window = false;
    static bool show_issue_window = false;

    // Main menu bar
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Menu")) {
        if (ImGui::MenuItem("Pop-up", nullptr, show_popup_window)) {
            show_popup_window = !show_popup_window;
        }
        if (ImGui::MenuItem("Demo window", nullptr, show_demo_window)) {
            show_demo_window = !show_demo_window;
        }
        if (ImGui::MenuItem("Issue demonstration (#9249)", nullptr, show_issue_window)) {
            show_issue_window = !show_issue_window;
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

    if (show_issue_window) {
        ImGui::Begin("Issue demonstration (#9249)");
        constexpr auto INPUT_HEIGHT = 8;
        static ImGuiInputTextFlags flags_issue = ImGuiInputTextFlags_None;
        ImGui::CheckboxFlags("ImGuiInputTextFlags_ReadOnly", &flags_issue, ImGuiInputTextFlags_ReadOnly);
        ImGui::CheckboxFlags("ImGuiInputTextFlags_NoHorizontalScroll", &flags_issue,
                             ImGuiInputTextFlags_NoHorizontalScroll);
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

    ImGui::Begin("Test");
    static int e = Akat;
    ImGui::RadioButton("radio a", &e, Akat);
    ImGui::SameLine();
    ImGui::RadioButton("radio b", &e, Bliskavice);
    ImGui::SameLine();
    ImGui::RadioButton("radio c", &e, Cilovnici);
    ImGui::Text(e == Akat ? "a" : e == Bliskavice ? "b" : "c");
    ImGui::End();
}
