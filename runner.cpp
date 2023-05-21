#include "raylib.h"

int main(){

    //Window Properties
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth ,windowHeight, "Runner");

    //acceleration due to gravity (pixels/frame)/frame
    const int gravity{1};

    Texture2D runner = LoadTexture("textures/scarfy.png");
    Rectangle runnerRec;
    Vector2 runnerPos;

    //player properties
    const int width{50};
    const int height{100};

    //Is in air?
    bool isInAir;
    //jump velocity
    const int jumpVel{-22};

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
            isInAir=false;

        }else{
            //apply gravity when in air
            velocity+=gravity;
            isInAir=true;
        }

        //jump check
        if(IsKeyPressed(KEY_SPACE)&&!isInAir){
            velocity+=jumpVel;
        }

        //update position
        posY+=velocity;

        DrawRectangle(windowWidth/2,posY, width, height, BLUE);
        
        //stop drawing
        EndDrawing();
    }
    CloseWindow();
}