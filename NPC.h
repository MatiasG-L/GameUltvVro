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
    Wall *collider;
    
    
    Npc(float width, float height, Vector2 position, std::string name, std::string line, char state){
        this->width = width;
        this->height = height;
        this->position = position;
        this->name = name;
        this->line = line;
        this->state = state;
        
        collider = new Wall(height, width, &position, false, BLACK);
    }
};

class NpcEnemy : Npc{
    Enemy *enemy = new Enemy(150, 300, {1100, 100}, "EnemyNig", 100, 5, 100, 100,{5,5,100,0.1,5});

};
