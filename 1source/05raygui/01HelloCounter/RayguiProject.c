#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main()
{
    InitWindow(640, 480, "raygui - Hello counter");
    SetTargetFPS(60);

    int counter = 1;
    char buf[1];

    bool show_popup_window = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        //----------------------------------------------------------------------------------

        GuiStatusBar((Rectangle) { 0, 0, (float)GetScreenWidth(), 21 }, "");

        GuiCheckBox((Rectangle) { 5, 3, 15, 15 }, "Pop-up", & show_popup_window);

        if (counter == 1) GuiSetState(STATE_DISABLED);
        if (GuiButton((Rectangle) { 24, 45, 50, 30 }, "-")) {
            counter--;
        }
        GuiSetState(STATE_NORMAL);

        sprintf(buf, "%d", counter);
        GuiLabel((Rectangle) { 79, 45, 10, 30 }, buf);

        if (counter == 5) GuiSetState(STATE_DISABLED);
        if (GuiButton((Rectangle) { 94, 45, 50, 30 }, "+")) {
            counter++;
        }
        GuiSetState(STATE_NORMAL);

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
