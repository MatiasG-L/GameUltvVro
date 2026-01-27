#include "raylib.h"


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
    Npc(int width, int height, Vector2 position, std::string name, std::string line, char state){
        this->width = width;
        this->height = height;
        this->position = position;
        this->name = name;
        this->line = line;
        this->state = state;
    }
};
