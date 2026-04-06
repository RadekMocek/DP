#include "App.hpp"

enum Choice
{
    Akat, Bliskavice, Cilovnici
};

// ReSharper disable once CppMemberFunctionMayBeConst
void App::Update()
{
    const auto Dummy = [] {
        ImGui::Dummy({0.0f, 8.0f});
    };

    const auto io = ImGui::GetIO();

    // State
    static bool show_popup_window = false;
    static bool show_demo_window = true;
    static bool show_inputtextmultiline_window = true;
    static bool show_radio_window = false;

    // Main menu bar
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Menu")) {
        if (ImGui::MenuItem("Pop-up", nullptr, show_popup_window)) {
            show_popup_window = !show_popup_window;
        }
        if (ImGui::MenuItem("Demo window", nullptr, show_demo_window)) {
            show_demo_window = !show_demo_window;
        }
        if (ImGui::MenuItem("InputTextMultiline test", nullptr, show_inputtextmultiline_window)) {
            show_inputtextmultiline_window = !show_inputtextmultiline_window;
        }
        if (ImGui::MenuItem("Radio button test", nullptr, show_radio_window)) {
            show_radio_window = !show_radio_window;
        }
        if (ImGui::MenuItem("Exit", "Alt+F4")) {
            glfwSetWindowShouldClose(m_window, GLFW_TRUE);
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
        ImGui::PushFont(nullptr, 18.0f);
        ImGui::ShowDemoWindow();
        ImGui::PopFont();
    }

    if (show_inputtextmultiline_window) {
        ImGui::Begin("InputTextMultiline test");

        ImGui::Text("Initially for issue demonstration (#9249)\nnow to test the InputTextMultiline.");
        Dummy();
        ImGui::Separator();

        constexpr auto INPUT_HEIGHT = 8;
        static ImGuiInputTextFlags txt_flags = ImGuiInputTextFlags_None;

        ImGui::CheckboxFlags("ReadOnly", &txt_flags, ImGuiInputTextFlags_ReadOnly);
        ImGui::CheckboxFlags("NoHorizontalScroll", &txt_flags, ImGuiInputTextFlags_NoHorizontalScroll);
        ImGui::CheckboxFlags("CharsDecimal", &txt_flags, ImGuiInputTextFlags_CharsDecimal);
        ImGui::CheckboxFlags("AllowTabInput", &txt_flags, ImGuiInputTextFlags_AllowTabInput);
        ImGui::CheckboxFlags("EscapeClearsAll", &txt_flags, ImGuiInputTextFlags_EscapeClearsAll);
        ImGui::CheckboxFlags("Password", &txt_flags, ImGuiInputTextFlags_Password);
        ImGui::CheckboxFlags("AlwaysOverwrite", &txt_flags, ImGuiInputTextFlags_AlwaysOverwrite);
        ImGui::CheckboxFlags("AutoSelectAll (no work in multiline?)", &txt_flags, ImGuiInputTextFlags_AutoSelectAll);
        ImGui::CheckboxFlags("ImGuiInputTextFlags_WordWrap (Beta)", &txt_flags, ImGuiInputTextFlags_WordWrap);

        static char text[1024 * INPUT_HEIGHT] =
            "abcde ABCDE\n"
            "fghij FGHIJ fghij FGHIJ\n"
            "klmno KLMNO klmno KLMNO klmno KLMNO\n"
            "pqrst PQRST pqrst PQRST pqrst PQRST pqrst PQRST\n"
            "uvwxyz UVWXYZ uvwxyz UVWXYZ uvwxyz UVWXYZ uvwxyz UVWXYZ uvwxyz UVWXYZ\n"
            "ěščřžýáíé ĚŠČŘŽÝÁÍÉ ěščřžýáíé ĚŠČŘŽÝÁÍÉ ěščřžýáíé ĚŠČŘŽÝÁÍÉ ěščřžýáíé ĚŠČŘŽÝÁÍÉ ěščřžýáíé ĚŠČŘŽÝÁÍÉ ěščřžýáíé ĚŠČŘŽÝÁÍÉ\n"
            "☺ ☻ ♥ ♦ ♣ ♠\n"
            "😀\n"
            "0 1 2 3 4 5 6 7 8 9";

        //ImGui::Text("Default style:");
        ImGui::Separator();
        Dummy();
        ImGui::InputTextMultiline("##source1", text, IM_ARRAYSIZE(text),
                                  ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * INPUT_HEIGHT), txt_flags);

        /*
        ImGui::Text("Zero frame padding:");
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::InputTextMultiline("##source2", text, IM_ARRAYSIZE(text),
                                  ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * INPUT_HEIGHT), txt_flags);
        ImGui::PopStyleVar();
        ImGui::Text("io.MouseWheel: %.1f", io.MouseWheel);
        if (io.KeyShift) {
            ImGui::Text("io.KeyShift");
        }
        //*/
        ImGui::End();
    }

    if (show_radio_window) {
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
}
