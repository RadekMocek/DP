#include <format>

#include "App.hpp"

void App::Update()
{
    ImGuiIO& io = ImGui::GetIO();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (m_show_demo_window) {
        ImGui::ShowDemoWindow(&m_show_demo_window);
    }

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    if (m_show_hello_window) {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &m_show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &m_show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&m_clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (m_show_another_window) {
        ImGui::Begin("Another Window", &m_show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        
        ImGui::Text("Hello from another window!");
        
        /*
        ImGui::Text("ÏöË¯û˝·ÌÈÛ˙˘ÔùÚ Ãä»ÿé›¡Õ…”⁄Ÿœç“");
        
        static char str0[128] = "ÏöË¯û˝·ÌÈÛ˙˘ÔùÚ Ãä»ÿé›¡Õ…”⁄Ÿœç“";
        ImGui::InputText("input text", str0, IM_COUNTOF(str0));
        //*/

        if (ImGui::Button("Close Me"))
            m_show_another_window = false;
        ImGui::End();
    }

    // 4. Testing misc stuff...
    if (m_show_testing_window) {
        const auto header = std::format("Dear ImGui verze {} ({})", IMGUI_VERSION, IMGUI_VERSION_NUM);
        constexpr ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

        constexpr auto text = "Dear ImGui Aa Bb Cc Dd Ee";

        ImGui::Begin("Blurry forever", nullptr, flags);

        ImGui::PushFont(nullptr, 28.0f);
        ImGui::Text("%s (added via AddFontDefaultVector)", text);
        ImGui::PopFont();

        /*
        ImGui::PushFont(m_font_proggyclean, 28.0f);
        ImGui::Text("%s", text);
        ImGui::PopFont();
        //*/

        ImGui::PushFont(m_font_proggyforever, 28.0f);
        ImGui::Text("%s (added via AddFontFromFileTTF)", text);
        ImGui::PopFont();

        /*
        ImGui::PushFont(m_font_inconsolata, 28.0f);
        ImGui::Text("%s", text);
        ImGui::PopFont();        
        //*/

        ImGui::End();
    }
}
