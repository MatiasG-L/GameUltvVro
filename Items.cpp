#include "Item.h"

/*
Item paramater list:
1.   (name,  texture,  type, factor)
2.   (name,  texture,  type, factor, scalable)
*/

Item healthPotion("Health Potion(small)", LoadTexture("Assests/Items/Sprites/Small Health Potion.png"), 1, 10);

void useItem(Item* item){};