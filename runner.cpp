#include "raylib.h"

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main(){

    //Window Properties
    int windowDimensions[2];
    windowDimensions[0]=512;
    windowDimensions[1]=380;

    //Initializing a window
    InitWindow(windowDimensions[0] ,windowDimensions[1], "Runner");

    //acceleration due to gravity (pixels/frame)/frame
    const int gravity{1'000};

    //obstacle variables
    
    Texture2D obstacle = LoadTexture("textures/12_nebula_spritesheet.png");

    const int numberOfObstacles = 3;

    AnimData obsAray[numberOfObstacles]{};

    for(int i=0;i<numberOfObstacles;i++){
        obsAray[i].rec.x=0.0;
        obsAray[i].rec.y=0.0;
        obsAray[i].rec.width=obstacle.width/8;
        obsAray[i].rec.height=obstacle.height/8;
        obsAray[i].pos.y=windowDimensions[1] - obstacle.height/8;
        obsAray[i].frame=0;
        obsAray[i].runningTime=0.0;
        obsAray[i].updateTime=1.0/16.0;
    }

    obsAray[0].pos.x=windowDimensions[0];
    obsAray[1].pos.x=windowDimensions[0]+300;
    obsAray[2].pos.x=windowDimensions[0]+600;

    //nebula x velocity (pixels/second)
    int obsVel{-200};

    //player properties
    Texture2D runner = LoadTexture("textures/scarfy.png");
    AnimData runnerData{
        {0.0,0.0,runner.width/6,runner.height}, //Rectangle Rec
        {windowDimensions[0]/2-runnerData.rec.width/2,windowDimensions[1]-runnerData.rec.height}, //Rectangle Pos
        0, //int frame
        1.0/12.0, //float updateTime
        0.0 //float runningTime
    };

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
        if(runnerData.pos.y >= windowDimensions[1]-runnerData.rec.height){
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

        //update runner position
        runnerData.pos.y+=velocity*dT;

        for (int i = 0; i < numberOfObstacles; i++)
        {
            //update obstacle position
            obsAray[i].pos.x+=obsVel*dT;

            //update nebula animation frame
            obsAray[i].runningTime += dT;
            if(obsAray[i].runningTime >= obsAray[i].updateTime){
                obsAray[i].runningTime = 0.0;
                //update animation frame
                obsAray[i].rec.x = obsAray[i].frame * obsAray[i].rec.width;
                obsAray[i].frame++;
                if(obsAray[i].frame>8){
                    obsAray[i].frame=0;
                }
            }
        }
        

        //update runner's animation frame
        if(!isInAir){
            //update running time
            runnerData.runningTime+=dT;
            if(runnerData.runningTime >= runnerData.updateTime){
                runnerData.frame=0;
                //update animation frame
                runnerData.rec.x = runnerData.frame * runnerData.rec.width;
                runnerData.frame++;
                if(runnerData.frame>5){
                    runnerData.frame=0;
                }
            }
        }

        //draw obstacle
        DrawTextureRec(obstacle, obsAray[0].rec, obsAray[0].pos, WHITE);

        //draw second obstacle
        DrawTextureRec(obstacle, obsAray[1].rec, obsAray[1].pos, RED);

        //draw third obstacle
        DrawTextureRec(obstacle, obsAray[2].rec, obsAray[2].pos, PURPLE);

        //draw runner
        DrawTextureRec(runner, runnerData.rec, runnerData.pos, WHITE);
        
        //stop drawing
        EndDrawing();
    }
    UnloadTexture(runner);
    UnloadTexture(obstacle);
    CloseWindow();
}