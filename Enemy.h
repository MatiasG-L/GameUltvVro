#include "raylib.h"
#pragma once
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
        float physicalAtk;
        float specialAtk;
        float defence;
        float specialDefence;
        float speed;
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
                return energyDamageOut();
                break;
            case 1:
                return physicalDamageOut();
                break;
        }
    }
    float physicalDamageOut(){
        float temp = stats.physicalAtk + ((stats.physicalAtk * (level/100)) * 2) * (stamina / maxStamina) * (float)GetRandomValue(0.6,1.4);
        std::cout << "Enemy Raw Damage Out: " << temp << "\n";
        return temp;
    }
    
    float energyDamageOut(){
        float temp = stats.specialAtk + ((stats.specialAtk * (level/100)) * 2) * (energy / maxEnergy) * (float)GetRandomValue(0.6,1.4);
        std::cout << "Enemy Raw Damage Out: " << temp << "\n";
        return temp;
    }
    
    float damageCalc(int type, float incoming){
        float randomNum = GetRandomValue(0,100); 
       std::cout << "\n";
        if(randomNum <= 8){
            std::cout << "PLAYER CRIT! @ " << randomNum << "\n";
            std::cout << "Damage taken enemy: " <<  incoming *1.7 << "\n";
            return incoming *1.7;
        }else{
            switch(type){
                case 0:
                    std::cout << "Damage taken enemy: " << incoming - ((stats.specialDefence/100) * (incoming * 0.75f)) << "\n";
                    return incoming - ((stats.specialDefence/100) * (incoming * 0.75f));
                case 1:
                    std::cout << "Damage taken enemy: " << incoming - (((stats.defence)/100) * (incoming * 0.75f)) << "\n";
                    return incoming - (((stats.defence)/100) * (incoming * 0.75f));
                default:
                    return -1;
            }
        }
    }
    
    
    
};