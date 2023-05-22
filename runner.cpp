#include "raylib.h"

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight){
    return data.pos.y>=windowHeight-data.rec.height;
}

AnimData animateSprite(AnimData data, float dT,int maxFrame){
    data.runningTime+=dT;
    if(data.runningTime >= data.updateTime){
        data.runningTime=0.0;
        //update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame>maxFrame){
            data.frame=0;
        }
    }
    return data;
}

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

    const int numberOfObstacles = 6;
    int x = 0;

    AnimData obsAray[numberOfObstacles]{};
 
    for(int i=0;i<numberOfObstacles;i++){
        obsAray[i].rec.x=0.0;
        obsAray[i].rec.y=0.0;
        obsAray[i].rec.width=obstacle.width/8;
        obsAray[i].rec.height=obstacle.height/8;
        obsAray[i].pos.x=windowDimensions[0]+x;
        obsAray[i].pos.y=windowDimensions[1] - obstacle.height/8;
        obsAray[i].frame=0;
        obsAray[i].runningTime=0.0;
        obsAray[i].updateTime=1.0/16.0;
        x+=300;
    }

    float finishLine{obsAray[numberOfObstacles-1].pos.x};

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

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};

    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};

    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};

    bool collision{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        //delta time(time since last frame)
        float dT{GetFrameTime()}; 

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        bgX-=20*dT;
        if(bgX<=-background.width*2){
            bgX=0.0;
        }

        mgX-=40*dT;
        if(mgX<=-midground.width*2){
            mgX=0.0;
        }

        fgX-=80*dT;
        if(fgX<=-foreground.width*2){
            fgX=0.0;
        }

        //draw the background
        Vector2 bg1Pos{bgX,0.0};
        DrawTextureEx(background,bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX+background.width*2,0.0};
        DrawTextureEx(background,bg2Pos, 0.0, 2.0, WHITE);
        
        //draw the midground
        Vector2 mg1Pos{mgX,0.0};
        DrawTextureEx(midground,mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX+midground.width*2,0.0};
        DrawTextureEx(midground,mg2Pos, 0.0, 2.0, WHITE);

        //draw the midground
        Vector2 fg1Pos{fgX,0.0};
        DrawTextureEx(foreground,fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX+foreground.width*2,0.0};
        DrawTextureEx(foreground,fg2Pos, 0.0, 2.0, WHITE);

        //perform ground check
        if(isOnGround(runnerData,windowDimensions[1])){
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

        //update runner's animation frame
        if(!isInAir){
            runnerData=animateSprite(runnerData,dT,5);
        }
   
        for(AnimData obstacle : obsAray)
        {
            float pad{50};
            Rectangle obsRec{
                obstacle.pos.x+20,
                obstacle.pos.y+20,
                obstacle.rec.width-2*pad,
                obstacle.rec.height-2*pad
            };
            Rectangle runnerRec{
                runnerData.pos.x,
                runnerData.pos.y,
                runnerData.rec.width,
                runnerData.rec.height
            };
            if(CheckCollisionRecs(obsRec,runnerRec)){
                collision=true;
            }
        }
        

        for (int i = 0; i < numberOfObstacles; i++)
        {
            //update obstacle position
            obsAray[i].pos.x+=obsVel*dT;

            obsAray[i]=animateSprite(obsAray[i],dT,7);

        }

        finishLine+=obsVel*dT;

        if (collision)
        {
            //lose game
            DrawText("Game Over!", windowDimensions[0]/4, windowDimensions[1]/2, 40, RED);
        }else if(runnerData.pos.x >=finishLine){
            //win the game
            DrawText("You win!", windowDimensions[0]/4, windowDimensions[1]/2, 40, RED);
        }else{

            for (int i = 0; i < numberOfObstacles; i++)
            {
                //draw obstacle
                DrawTextureRec(obstacle, obsAray[i].rec, obsAray[i].pos, WHITE);
            }
            
            //draw runner
            DrawTextureRec(runner, runnerData.rec, runnerData.pos, WHITE);
        
            
        }

        //stop drawing
        EndDrawing();
    }
    UnloadTexture(runner);
    UnloadTexture(obstacle);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}