#include "Textures.h"
#include <vector>
Textures rock("Rock", LoadTexture("Assests/Objects/Rock.png"));
Textures Mei("Mei Mei", LoadTexture("Assests/Objects/mei.png"));
Textures Cuctus("Cuctus", LoadTexture("Assests/Objects/cuctus.png"));

std::vector<Textures> TextureList = {rock, Mei, Cuctus};