#include "raylib.h"

int main(){

    //Window Properties
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth ,windowHeight, "Runner");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //stop drawing
        EndDrawing();
    }
    CloseWindow();
}