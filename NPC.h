#include "raylib.h"
#include "Enemy.h"

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
    
    Npc(float width, float height, Vector2 position, std::string name, char state){
        this->width = width;
        this->height = height;
        this->position = position;
        this->name = name;
        this->state = state;
        
    }
};
