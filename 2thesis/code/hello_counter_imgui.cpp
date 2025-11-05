void App::update() {
    static int counter = 1;

    ImGui::Begin("Hello Counter");

    ImGui::BeginDisabled(counter == 1);
    if (ImGui::Button("-")) {
        counter--;
    }
    ImGui::EndDisabled();

    ImGui::Text("%d", counter);

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