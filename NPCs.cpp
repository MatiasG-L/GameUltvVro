#include "raylib.h"
#include "NPC.h"


NPC BasicFella(100, 100, {0, 0}, "DudeMan", 'S');

NPC NPCBlueprints[] = {BasicFella};

NPC getNPC(int indx){
    try{
        NPCBlueprints[indx].ListNumber = indx;
    return NPCBlueprints[indx];
    }catch(...){
        std::cout << "invalid index! default to basic NPC";
        return BasicFella;
    }
    
}