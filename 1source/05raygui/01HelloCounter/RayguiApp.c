#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main()
{
    InitWindow(640, 480, "raygui");
    SetTargetFPS(60);

    int counter = 1;
    char buf[1];

    bool show_popup_window = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        //----------------------------------------------------------------------------------

        int status_bar_height = 21;

        //*
        GuiStatusBar((Rectangle) { 0, 0, (float)GetScreenWidth(), status_bar_height }, "");

        GuiCheckBox((Rectangle) { 5, 3, 15, 15 }, "Pop-up", & show_popup_window);
        //*/

        int padding = 16;

        int x = padding;
        int y = padding + status_bar_height;

        if (counter == 1) GuiSetState(STATE_DISABLED);
        if (GuiButton((Rectangle) { x, y, 50, 30 }, "-")) {
            counter--;
        }
        GuiSetState(STATE_NORMAL);

        sprintf(buf, "%d", counter);
        GuiLabel((Rectangle) { x + 55, y, 10, 30 }, buf);

        if (counter == 5) GuiSetState(STATE_DISABLED);
        if (GuiButton((Rectangle) { x + 70, y, 50, 30 }, "+")) {
            counter++;
        }
        GuiSetState(STATE_NORMAL);

        if (counter == 3) {
            GuiLabel((Rectangle) { x, y + 25, 50, 30 }, "Hello!");
        }

        if (show_popup_window) {
            int result = GuiMessageBox((Rectangle) { (float)GetScreenWidth() / 2 - 125, (float)GetScreenHeight() / 2 - 50, 250, 100 },
                "Pop-up window", "Not much you can do here...", "Close");

            if (result >= 0) show_popup_window = false;
        }

        //----------------------------------------------------------------------------------
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
