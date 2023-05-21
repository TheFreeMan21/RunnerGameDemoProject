#include "raylib.h"

int main(){

    //Window Properties
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth ,windowHeight, "Runner");

    //acceleration due to gravity (pixels/frame)/frame
    const int gravity{1'000};

    //player properties
    Texture2D runner = LoadTexture("textures/scarfy.png");
    Rectangle runnerRec;
    runnerRec.width = runner.width/6;
    runnerRec.height = runner.height;
    runnerRec.x = 0;
    runnerRec.y = 0;
    Vector2 runnerPos;
    runnerPos.x = windowWidth/2 - runnerRec.width/2;
    runnerPos.y = windowHeight - runnerRec.height;

    //animation frame
    int frame{};
    //amount of time before we update the animation frame
    const float updateTime{1.0/12.0};
    float runningTime{};

    //Is in air?
    bool isInAir;
    //jump velocity pixels/second
    const int jumpVel{-600};

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        //delta time(time since last frame)
        float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //perform ground check
        if(runnerPos.y >= windowHeight-runnerRec.height){
            //rectangle on the ground
            velocity=0;
            isInAir=false;

        }else{
            //apply gravity when in air
            velocity+=gravity*dT;
            isInAir=true;
        }

        //jump check
        if(IsKeyPressed(KEY_SPACE)&&!isInAir){
            velocity+=jumpVel;
        }

        //update position
        runnerPos.y+=velocity*dT;

        //update running time
        runningTime+=dT;
        if(runningTime >= updateTime){
            runningTime=0;
            //update animation frame
            runnerRec.x = frame * runnerRec.width;
            frame++;
            if(frame>5){
                frame=0;
            }
        }

        DrawTextureRec(runner, runnerRec, runnerPos, WHITE);
        
        //stop drawing
        EndDrawing();
    }
    UnloadTexture(runner);
    CloseWindow();
}