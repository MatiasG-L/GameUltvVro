#include "raylib.h"

class Wall{
    public:
    int height;
    int width;
    Vector2 position;
    bool moveable = false;
    Color sqrColor;
    Wall(int height, int width, Vector2 position, Color sqrColor){
        this->height = height;
        this->width = width;
        this->sqrColor = sqrColor;
        this->position = position;
    }
    Wall(int height, int width, Vector2 position, bool moveable, Color sqrColor){
        this->height = height;
        this->width = width;
        this->moveable = moveable;
        this->sqrColor = sqrColor;
        this->position = position;
    }
};