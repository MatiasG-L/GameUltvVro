#include "raylib.h"
#include "Item.h"
class Slot{
    public:
        Texture2D texture;
        float width;
        float height;
        Vector2 position;
        Item* item;
        int thickness;
        
        Slot(float width, float height, Vector2 position, int thickness){
            this->width = width;
            this->height = height;
            this->position = position;
            this->thickness = thickness;
            item = NULL;
        }
        Slot(float width, float height, Vector2 position, int thickness, Item* item){
            this->width = width;
            this->height = height;
            this->position = position;
            this->thickness = thickness;
            this->item = item;
        }
    
};