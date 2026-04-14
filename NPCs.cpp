#include "raylib.h"
#include "NPC.h"


NPC Basic(100, 100, {0, 0}, "DudeMan", 'S');

NPC npcBlueprints[] = {Basic};

NPC getNpc(int indx){
    try{
        npcBlueprints[indx].ListNumber = indx;
    return npcBlueprints[indx];
    }catch(...){
        std::cout << "invalid index! default to basic NPC";
        return Basic;
    }
    
}