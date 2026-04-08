#include "raylib.h"
class Textures{
    public:
    Texture2D texture;
    std::string name;
    Vector2D position;
    Vector2D Size;
    bool isAnimated;
    int frameCounter = 0; 
    int frameSpeed = 4; //(fps)
    int frameCount = 3;
    int currentFrame = 0;
    float aWidth;
    Rectangle animRec = {0,0,0,0};
    
    typedef struct Animation{
        int frameSpeed;
        int frameCount;
        float width;
        float height;
        std::string name;
        bool loop;
        Texture2D spriteSheet;
    }Animation;
    
    
    
    
    void animation(){
        frameCounter++;

        if (frameCounter >= (60/currentAnimation.frameSpeed))
        {
            frameCounter = 0;
            currentFrame++;

            if (currentFrame > currentAnimation.frameCount-1){
                currentFrame = 0;
                if(!currentAnimation.loop) changeAnimation("Idle");
            }

            animRec.x = (float)currentFrame*(float)currentAnimation.width/currentAnimation.frameCount;
            animRec.y = 0;
        }

    }
};