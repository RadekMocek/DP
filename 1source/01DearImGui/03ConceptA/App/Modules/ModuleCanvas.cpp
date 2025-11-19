#include <cmath>
#include <format>
#include <iomanip>
#include <map>
#include <sstream>

#include "../App.hpp"
#include "../Misc/Helper.hpp"

void App::ModuleCanvas()
{
    static ImGuiIO& io = ImGui::GetIO(); // For getting the mouse position

    // Create a parent for our canvas (with zero padding)
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    // Half of the main window is occupied by the text editor, so this will take up the rest on the x axis
    ImGui::BeginChild("CanvasParent", ImVec2(0, ImGui::GetContentRegionAvail().y - m_fps_info_size.y), ImGuiChildFlags_Borders, ImGuiWindowFlags_None);
    ImGui::PopStyleVar();

    // "node index" in this context means the row number in the text editor, where the particular node is defined (starting from 0)

    static std::map<unsigned int, ImVec4> areas; // Key=node index; Value=aabr(axis aligned bounding rectangle :))
    // LMB
    static bool is_moving_node = false;
    static unsigned int moving_node_index = 0;
    static ImVec2 moving_node_size;
    // RMB
    static bool right_clicked_on_node = false;
    static unsigned int right_clicked_node_index = 0;

    static ImVec2 scrolling(0.0f, 0.0f); // Scrolling means moving the canvas in this context

    // Options
    const float border_offset = 18.0f; // Padding of rectangle border around text in canvas
    static bool is_grid_enabled = true;
    const auto color_grid_line = IM_COL32(200, 200, 200, 40);
    const auto color_node = IM_COL32(0, 0, 0, 255);
    const auto color_ghost = IM_COL32(0, 0, 196, 196);

    // Using InvisibleButton() as a convenience:
    // 1) it will advance the layout cursor
    // 2) allows us to use IsItemHovered()/IsItemActive()
    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos(); // ImDrawList API uses screen coordinates!
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail(); // Resize canvas to what's available
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

    ImDrawList* draw_list = ImGui::GetWindowDrawList(); // Enables us to draw primitives
    
    //draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255)); // Border
    //draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255)); // Background color

    // This will catch our interactions
    ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
    const bool is_hovered = ImGui::IsItemHovered(); // Hovered (hot item)
    const bool is_active = ImGui::IsItemActive(); // Held
    const ImVec2 origin(canvas_p0.x + scrolling.x, canvas_p0.y + scrolling.y); // Lock scrolled origin
    const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);

    // LMB
    if (is_hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        //IMGUI_DEBUG_LOG("%f %f\n", mouse_pos_in_canvas.x, mouse_pos_in_canvas.y);
        // Check every node if cursor is inside its aabr
        for (auto const& [key, value] : areas) {
            //IMGUI_DEBUG_LOG("%f %f | %f %f\n", value.x, value.z, value.y, value.w);
            if (InRangeInclFloat(value.x, mouse_pos_in_canvas.x, value.z) && InRangeInclFloat(value.y, mouse_pos_in_canvas.y, value.w)) {
                //IMGUI_DEBUG_LOG("Clicked on node!\n");
                is_moving_node = true;
                moving_node_index = key; // Remember node index (of the moving node) so we can change the coor values in the text editor after LMB release
                moving_node_size = ImVec2(value.z - value.x, value.w - value.y); // Remember node size so we can show "the ghost node" with proper size
                break;
            }
        }
    }

    // LMB release
    if (is_moving_node && !ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        //IMGUI_DEBUG_LOG("Released LMB!\n");
        is_moving_node = false;
        // Put new position to the text editor
        // Custom syntax in diagram source will be replaced later by TOML or similiar, so no need for tip-top code here right now
        std::ostringstream oss;
        std::stringstream ss(m_source);
        std::string part;
        unsigned int line_n = 0;
        while (getline(ss, part)) {
            if (line_n == moving_node_index) {
                std::string label;
                int x, y;
                std::istringstream iss(part);
                iss >> std::quoted(label) >> x >> y;
                oss << std::format("\"{}\" {} {}\n", label, round(mouse_pos_in_canvas.x), round(mouse_pos_in_canvas.y));
            }
            else {
                oss << part << '\n';
            }
            line_n++;
        }
        m_source = oss.str();
    }

    // RMB drag to move the canvas ("scrolling")
    // Pan (we use a zero mouse threshold when there's no context menu)
    // You may decide to make that threshold dynamic based on whether the mouse is hovering something etc.
    const float mouse_threshold_for_pan = -1.0f;
    if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan)) {
        scrolling.x += io.MouseDelta.x;
        scrolling.y += io.MouseDelta.y;
    }

    // RMB: Context menu (under default mouse threshold)
    ImVec2 drag_delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
    if (!is_moving_node && drag_delta.x == 0.0f && drag_delta.y == 0.0f) {

        ImGui::OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);
        
        if (ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
            //IMGUI_DEBUG_LOG("RMB");
            // Check all aabr if we right cliked on any node
            for (auto const& [key, val] : areas) {
                if (InRangeInclFloat(val.x, mouse_pos_in_canvas.x, val.z) && InRangeInclFloat(val.y, mouse_pos_in_canvas.y, val.w)) {
                    right_clicked_on_node = true;
                    right_clicked_node_index = key;
                    break;
                }
            }
        }
    }
    if (ImGui::BeginPopup("context")) {      
        if (ImGui::MenuItem("Delete", nullptr, false, right_clicked_on_node)) {
            // Remove the line with that node from the text editor
            std::ostringstream oss;
            std::stringstream ss(m_source);
            std::string part;
            unsigned int line_n = 0;
            while (getline(ss, part)) {
                if (line_n != right_clicked_node_index) {
                    oss << part << '\n';
                }
                line_n++;
            }
            m_source = oss.str();
        }
        ImGui::EndPopup();
    }
    else {
        right_clicked_on_node = false; // Reset to false when context menu dissappears
    }

    // aabrs get refreshed every frame, could be optimized
    areas.clear();

    // Draw grid + all lines in the canvas
    draw_list->PushClipRect(canvas_p0, canvas_p1, true);
    if (is_grid_enabled) {
        const float GRID_STEP = 100.0f;
        for (float x = fmodf(scrolling.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
            draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), color_grid_line);
        for (float y = fmodf(scrolling.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
            draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), color_grid_line);
    }
    
    // Scan each line of the text editor and draw nodes to canvas
    std::stringstream ss(m_source);
    std::string part;
    unsigned int line_n = 0; // node index
    while (getline(ss, part)) {
        std::string label;
        int node_x, node_y;
        std::istringstream iss(part);
        iss >> std::quoted(label) >> node_x >> node_y; // eg: "Hello" 10 20
        
        if (label.empty()) {
            line_n++;
            continue;
        }

        // Draw text
        auto label_c_str = label.c_str();
        auto label_origin = ImVec2(origin.x + node_x, origin.y + node_y);
        draw_list->AddText(label_origin, color_node, label_c_str);

        // Draw rectangle and store its aabr
        auto label_size = ImGui::CalcTextSize(label_c_str);        
        auto upper_left = ImVec2PlusC(label_origin, -border_offset);
        auto lower_right = ImVec2PlusC(ImVec2Plus(label_origin, label_size), border_offset);
        draw_list->AddRect(upper_left, lower_right, color_node);
        ImVec4 aabr(upper_left.x - origin.x, upper_left.y - origin.y, lower_right.x - origin.x, lower_right.y - origin.y);
        areas.insert_or_assign(line_n, aabr);

        line_n++;
    }

    // Draw ghost at cursor pos if moving node
    if (is_moving_node) {
        auto position = ImVec2PlusC(io.MousePos, -border_offset);
        draw_list->AddRect(position, ImVec2Plus(position, moving_node_size), color_ghost);
    }

    draw_list->PopClipRect();

    ImGui::EndChild();
}