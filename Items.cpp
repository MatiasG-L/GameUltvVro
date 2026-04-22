#include "Item.h"
#include "raylib.h"
/*
Item paramater list:
1.   (name,  texture,  type, factor, id, description)
2.   (name,  texture,  type, factor, id, description, scalable)
*/

Item healthPotion("Health Potion(small)", LoadTexture("Assests/Items/Sprites/Small Health Potion.png"), 1, 10, 0, "Small potion that restores +10 to your current health. ");

Item items[] = {healthPotion};
