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
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth ,windowHeight, "Runner");

    //acceleration due to gravity (pixels/frame)/frame
    const int gravity{1'000};

    //obstacle variables
    
    Texture2D obstacle = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData obsData{
        {0.0, 0.0, obstacle.width/8, obstacle.height/8}, //Rectangle Rec
        {windowWidth, windowHeight - obsData.rec.height},  //Rectangle Pos
        0,  //int frame
        1.0/12.0,  //float updateTime
        0.0  //float runningTime
    };
    AnimData obs2Data{
        {0.0, 0.0, obstacle.width/8, obstacle.height/8}, //Rectangle Rec
        {windowWidth+300, windowHeight - obs2Data.rec.height}, //Rectangle Pos
        0, //int frame
        1.0/16.0, //float updateTime
        0.0 //float runningTime
    };

    //nebula x velocity (pixels/second)
    int obsVel{-200};

    //player properties
    Texture2D runner = LoadTexture("textures/scarfy.png");
    AnimData runnerData{
        {0.0,0.0,runner.width/6,runner.height}, //Rectangle Rec
        {windowWidth/2-runnerData.rec.width/2,windowHeight-runnerData.rec.height}, //Rectangle Pos
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
        if(runnerData.pos.y >= windowHeight-runnerData.rec.height){
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

        //update obstacle position
        obsData.pos.x+=obsVel*dT;

        //update the second obstacle position
        obs2Data.pos.x+=obsVel*dT;

        //update runner position
        runnerData.pos.y+=velocity*dT;

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

        //update nebula animation frame
        obsData.runningTime += dT;
        if(obsData.runningTime >= obsData.updateTime){
            obsData.runningTime = 0.0;
            //update animation frame
            obsData.rec.x = obsData.frame * obsData.rec.width;
            obsData.frame++;
            if(obsData.frame>8){
                obsData.frame=0;
            }
        }

        //update nebula animation frame
        obs2Data.runningTime += dT;
        if(obs2Data.runningTime >= obs2Data.updateTime){
            obs2Data.runningTime = 0.0;
            //update animation frame
            obs2Data.rec.x = obs2Data.frame * obs2Data.rec.width;
            obs2Data.frame++;
            if(obs2Data.frame>8){
                obs2Data.frame=0;
            }
        }

        //draw obstacle
        DrawTextureRec(obstacle, obsData.rec, obsData.pos, WHITE);

        //draw second obstacle
        DrawTextureRec(obstacle, obs2Data.rec, obs2Data.pos, RED);

        //draw runner
        DrawTextureRec(runner, runnerData.rec, runnerData.pos, WHITE);
        
        //stop drawing
        EndDrawing();
    }
    UnloadTexture(runner);
    UnloadTexture(obstacle);
    CloseWindow();
}