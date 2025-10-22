#include "App.hpp"

void App::Update()
{
    static int counter = 1;

    ImGui::Begin("Hello Counter");

    ImGui::BeginDisabled(counter == 1);
    if (ImGui::Button("-")) {
        counter--;
    }
    ImGui::EndDisabled();

    ImGui::SameLine();

    ImGui::Text("%d", counter);

    ImGui::SameLine();

    ImGui::BeginDisabled(counter == 5);
    if (ImGui::Button("+")) {
        counter++;
    }
    ImGui::EndDisabled();

    if (counter == 3) {
        ImGui::Text("Hello!");
    }

    ImGui::End();
}
