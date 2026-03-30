#include "raylib.h"

class Wall{
    public:
    float height;
    float width;
    Vector2 position;
    Vector2 *positionNPC = NULL;
    bool moveable = false;
    Color sqrColor;
    int index;
    
    Wall(float height, float width, Vector2 position, Color sqrColor){
        this->height = height;
        this->width = width;
        this->sqrColor = sqrColor;
        this->position = position;
        Vector2 *positionNPC = NULL;
    }
    Wall(float height, float width, Vector2 position, bool moveable, Color sqrColor){
        this->height = height;
        this->width = width;
        this->moveable = moveable;
        this->sqrColor = sqrColor;
        this->position = position;
        Vector2 *positionNPC = NULL;
    }
    
    Wall(float height, float width, Vector2 *positionNPC, bool moveable, Color sqrColor){
        this->height = height;
        this->width = width;
        this->moveable = moveable;
        this->sqrColor = sqrColor;
        this->positionNPC = positionNPC;
    }
    
};

class EnemyWall : Wall{
    
};