#include "Item.h"
#include "raylib.h"
/*
Item paramater list:
1.   (name,  texture,  type, factor, id)
2.   (name,  texture,  type, factor, id, scalable)
*/

Item healthPotion("Health Potion(small)", LoadTexture("Assests/Items/Sprites/Small Health Potion.png"), 1, 10, 0);
Item run("Health Potion(small)", LoadTexture("Assests/UI/Running Icon.png"), 1, 10, 0);

Item items[] = {healthPotion, run};
