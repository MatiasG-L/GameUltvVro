#include "raylib.h"
#pragma once
class Textures{
    public:
    Texture2D texture;
    std::string name;
    Vector2 position;
    float angle = 0;
    Vector2 size;
    float scale = 1;
    bool isAnimated = false;
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
    Animation properties;
    
    Textures(std::string name, Texture2D texture){
            this->name = name;
            this->texture = texture;
    }
    Textures(std::string name, Texture2D texture, Animation properties){
            this->name = name;
            this->texture = texture;
            isAnimated = true;
            this->properties = properties;
    }
    
    
    void animation(){
        frameCounter++;

        if (frameCounter >= (60/properties.frameSpeed))
        {
            frameCounter = 0;
            currentFrame++;

            if (currentFrame > properties.frameCount-1){
                currentFrame = 0;
                
            }

            animRec.x = (float)currentFrame*(float)properties.width/properties.frameCount;
            animRec.y = 0;
        }

    }
};