#include "raylib.hpp"

#define	WIN_WIDTH	640
#define	WIN_HEIGHT	400

int main()
{
    // Initialize window and graphics
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "sick window");

    while (IsWindowReady())
    {
        // Check user input
        if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose())
        {
            goto l_exit;
        }

        // Clear the screen to a solid color
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    // Clean up and exit
    l_exit:        
        CloseWindow();
        return 0;
}
