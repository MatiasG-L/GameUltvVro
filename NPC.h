#include "raylib.h"
#pragma once

class Npc{
    public:
    float width;
    float height;
    Vector2 position;
    std::string name;
    Texture2D sprite;
    std::string line;
    bool moveable;
    char state;
    int ListNumber;
    
    Npc(float width, float height, Vector2 position, std::string name, char state){
        this->width = width;
        this->height = height;
        this->position = position;
        this->name = name;
        this->state = state;
        
    }
};
