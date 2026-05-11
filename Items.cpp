#include "Item.h"
#include "raylib.h"

#pragma once
/*
Item paramater list:
1.   (function, name,  texture,  type, factor, id, description)
2.   (function, name,  texture,  type, factor, id, description, scalable)
*/

Item healthPotion(NULL ,"Health Potion(small)", LoadTexture("Assests/Items/Sprites/Small Health Potion.png"), 1, 10, 0, "Small potion that restores +10 to your current health. ");

Item items[] = {healthPotion};
