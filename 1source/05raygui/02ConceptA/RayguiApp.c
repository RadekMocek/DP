#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main()
{
    InitWindow(640, 480, "raygui :: ConceptA");
    SetTargetFPS(60);

    float screen_width;
    float screen_height;

    bool is_text_edit_active = false;
    char buf[1024];

    bool show_about_window = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        screen_width = (float)GetScreenWidth();
        screen_height = (float)GetScreenHeight();
        //----------------------------------------------------------------------------------

        GuiStatusBar((Rectangle) { 0, 0, screen_width, 21 }, "");

        GuiCheckBox((Rectangle) { 5, 3, 15, 15 }, "About...", & show_about_window);       

        if (GuiTextBox((Rectangle) { 5, 25, screen_width / 2, screen_height - 30 }, buf, 1024, is_text_edit_active)) {
            is_text_edit_active = !is_text_edit_active;
        }

        if (show_about_window) {
            int result = GuiMessageBox((Rectangle) { screen_width / 2 - 125, screen_height / 2 - 50, 250, 100 },
                "About...", "https://github.com/RadekMocek/DP", "Close");

            if (result >= 0) show_about_window = false;
        }

        //----------------------------------------------------------------------------------
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
