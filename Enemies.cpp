#include "Enemy.h"
#include "raylib.h"

/* 
Enemy Paramaters:

    (int width, int height, Vector2 position, std::string name, float maxHealth, int level, float maxStamina, float maxEnergy, Stats stats){
    
    Stats{
        float physicalAtk;
        float specialAtk;
        float defence;
        float specialDefence;
        float speed;
    } 
    
*/

Enemy Basic(150, 300, 100, 100, {0, 0}, "Basic Enemy", 100, 5, 100, 100,{5,5,5,5,5});

Enemy enemyBlueprints[] = {Basic};

Enemy getEnemy(int indx){
    try{
        enemyBlueprints[indx].ListNumber = indx;
    return enemyBlueprints[indx];
    }catch(...){
        std::cout << "invalid index! default to basic enemy";
        return Basic;
    }
    
}