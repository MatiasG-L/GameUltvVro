#include "raylib.h"
#include "Enemy.h"
class Wall{
    public:
    float height;
    float width;
    Vector2 position;
    bool moveable = false;
    Color sqrColor;
    int index;
    bool isEnemy = false;
    Enemy *enemy = NULL;
    Wall(float height, float width, Vector2 position, Color sqrColor){
        this->height = height;
        this->width = width;
        this->sqrColor = sqrColor;
        this->position = position;

    }
    Wall(float height, float width, Vector2 position, bool moveable, Color sqrColor){
        this->height = height;
        this->width = width;
        this->moveable = moveable;
        this->sqrColor = sqrColor;
        this->position = position;

    }
    Wall(float height, float width, Vector2 position, bool moveable, Color sqrColor, Enemy *enemy){
        this->height = height;
        this->width = width;
        this->moveable = moveable;
        this->sqrColor = sqrColor;
        this->position = position;
        isEnemy = true;
        this->enemy = enemy;
    }
};