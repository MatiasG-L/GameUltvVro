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
        std::string description;
        Item(std::string name, Texture2D texture, int type, int factor, int id, std::string description){
            this->name = name;
            this->texture = texture;
            this->type = type;
            this->factor = factor;
            this->id = id;
            this->description = description;
        }
        Item(std::string name, Texture2D texture, int type, int factor, int id, std::string description, bool scalable){
            this->name = name;
            this->texture = texture;
            this->type = type;
            this->factor = factor;
            this->id = id;
            this->scalable = scalable;
            this->description = description;
        }
};