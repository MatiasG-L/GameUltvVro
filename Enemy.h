#include "raylib.h"
#include <iostream>
class Enemy{
    public:
    Texture2D spriteFront;
    Texture2D spriteWorld;
    int width;
    int height;
    Vector2 position;
    std::string name;
    float health;
    float maxHealth;
    float stamina; 
    float maxStamina;
    float energy;
    float maxEnergy;
    int guard;
    int level;
    typedef struct{
        int physicalAtk;
        int specialAtk;
        int defence;
        int specialDefence;
        int speed;
    }Stats;
    
    Stats stats;
    
    Enemy(int width, int height, Vector2 position, std::string name, float maxHealth, int level, float maxStamina, float maxEnergy, Stats stats){
        this->width = width;
        this->height = height;
        this->position = position;
        this->name = name;
        this->maxHealth = maxHealth;
        this->level = level;
        this->stats = stats;
        this->maxStamina = maxStamina;
        this->maxEnergy = maxEnergy;
        health = maxHealth;
        stamina = maxStamina;
        energy = maxEnergy;
    } 
    
    
    float returnDamage(int type){
        switch(type){
            case 0: 
                return stats.specialAtk + ((stats.specialAtk * (level/100)) * 2) * (energy / maxEnergy);
                break;
            case 1:
                return stats.physicalAtk + ((stats.physicalAtk * (level/100)) * 2) * (stamina / maxStamina);
                break;
        }
    }
    float physicalDamageOut(){
        return stats.physicalAtk + ((stats.physicalAtk * (level/100)) * 2) * (stamina / maxStamina);
    }
    
    float energyDamageOut(){
        return stats.specialAtk + ((stats.specialAtk * (level/100)) * 2) * (energy / maxEnergy);
    }
    
    float damageCalc(int type, float incoming){
        float randomNum = GetRandomValue(0,100); 
        std::cout << "\n" << randomNum << "\n";
        if(randomNum <=8){
            std::cout << "CRIT! @ " << randomNum << "\n";
            return incoming *1.7;
        }else{
            switch(type){
                case 0:
                    return incoming - ((stats.specialDefence/100) * (incoming * 0.75f));
                case 1:
                    return incoming - (((stats.defence)/100) * (incoming * 0.75f));
                default:
                    return -1;
            }
        }
    }
    
    
    
};