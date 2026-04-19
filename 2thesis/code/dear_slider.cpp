constexpr auto SLIDER_WIDTH = 200;
ImGui::SetCursorPosX(ImGui::GetCursorPosX()
                     + ImGui::GetContentRegionAvail().x
                     - SLIDER_WIDTH);
ImGui::PushItemWidth(SLIDER_WIDTH);
ImGui::SliderInt( ... );
ImGui::PopItemWidth();