#include "raylib.h"

int main(){

    //Window Properties
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth ,windowHeight, "Runner");

    //acceleration due to gravity (pixels/frame)/frame
    const int gravity{1};

    //player properties
    const int width{50};
    const int height{100};

    int posY{windowHeight - height};
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //perform ground check
        if(posY >= windowHeight-height){
            //rectangle on the ground
            velocity=0;

        }else{
            //apply gravity when in air
            velocity+=gravity;
        }

        if(IsKeyPressed(KEY_SPACE)){
            velocity-=10;
        }

        //update position
        posY+=velocity;

        DrawRectangle(windowWidth/2,posY, width, height, BLUE);
        
        //stop drawing
        EndDrawing();
    }
    CloseWindow();
}