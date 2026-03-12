#include "raylib.h"
#pragma once
class Item{
    public:
        std::string name;
        Texture2D texture;
        int type;
        int factor;
        bool scalable = false;
        Item(std::string name, Texture2D texture, int type, int factor){
            this->name = name;
            this->texture = texture;
            this->type = type;
            this->factor = factor;
        }
        Item(std::string name, Texture2D texture, int type, int factor, bool scalable){
            this->name = name;
            this->texture = texture;
            this->type = type;
            this->factor = factor;
            this->scalable = scalable;
        }
};