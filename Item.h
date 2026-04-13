#include "raylib.h"
#pragma once
class Item{
    public:
        std::string name;
        Texture2D texture;
        int type;
        int factor;
        bool scalable = false;
        int id;
        Item(std::string name, Texture2D texture, int type, int factor, int id){
            this->name = name;
            this->texture = texture;
            this->type = type;
            this->factor = factor;
            this->id = id;
        }
        Item(std::string name, Texture2D texture, int type, int factor, int id, bool scalable){
            this->name = name;
            this->texture = texture;
            this->type = type;
            this->factor = factor;
            this->id = id;
            this->scalable = scalable;
        }
};