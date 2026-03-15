#include "raylib.h" 
#include "Item.h"
#include <iostream>
class Player{
    public:
    Texture2D textureBack;
    Texture2D textureWorld;
    float width = 50;
    Item* inventory[30];
    Item* Equipt[4];
    float height = 100;
    Vector2 position;
    std::string name;
    float health = 100;
    float maxHealth = 100;
    int rank;
    float stamina = 100;
    float maxStamina = 100;
    int exp;
    int expRankUp;
    int blockT = 0;
    bool block = false;
    Vector2 Velocity = {0,0};
    int frameCounter = 0; 
    int frameSpeed = 4; //(fps)
    int frameCount = 3;
    int currentFrame = 0;
    float aWidth;
    Rectangle animRec = {0,0,0,0};
    //std::string currentAnimation = "NULL";
    
    typedef struct{
        float physicalAtk;
        float specialAtk;
        float defence;
        float specialDefence;
        float speed;
        float stamina;
        float health;
    }Stats;

    Stats stats;
    
    typedef struct{
        float attack;
        float defence;
        float shieldMax;
        float shieldHealth;
        float battery;
        float maxBattery;
    }Suit;
    
    Suit suit;
    
    typedef struct Animation{
        int frameSpeed;
        int frameCount;
        float width;
        float height;
        std::string name;
        bool loop;
        Texture2D spriteSheet;
    }Animation;
    
    Animation idle;
    Animation AttackP;
    Animation AttackS;
    
    Animation currentAnimation;
    
    Player(int width, int height, Vector2 position, std::string name, int rank, int expRankUp, Stats stats, Suit suit){
        this->width = width;
        this->height = height;
        this->position = position;
        this->name =  name;
        this->rank = rank;
        this->expRankUp = expRankUp;
        this->stats = stats;
        this->suit = suit;
    }
    
    float specialDamageOut(){
        float temp = (stats.specialAtk * (1 + suit.attack/2) * (float)rank/(stats.specialAtk + suit.attack)) * ((suit.battery/suit.maxBattery) + 0.5) * (float)GetRandomValue(1,1.8);
        std::cout << "Player Raw Damage Out: " << temp << "\n";
        return temp;
    }
    
    float physicalDamageOut(){
        float temp = (stats.physicalAtk * (1 + suit.attack/2) * (float)rank/(stats.physicalAtk + suit.attack)) * ((stamina/maxStamina) + 0.5) * (float)GetRandomValue(1,1.8);
        std::cout << "Player Raw Damage Out: " << temp << "\n";
        return temp;
    }
    
    float damageCalc(int type, float incoming){
        
        float randomNum = GetRandomValue(0,100); 
        std::cout << "\n";

        if(randomNum <= 8){
             std::cout << "ENEMY CRIT! @ " << randomNum << "\n";
             std::cout << "\n";
             std::cout << "Player damage taken: " << incoming *1.7 << "\n";
            return incoming *2.67;
        }else{
            switch(type){
                case 0:
                    if(blockT == 0 && block) incoming /= 4;
                    else if(blockT == 1 && block) incoming -= incoming/4;
                    std::cout << "Player damage taken: " << incoming - ((((stats.specialDefence + suit.defence)/2)/100) * (incoming * 0.75f)) << "\n";
                    
                    return incoming - ((((stats.specialDefence + suit.defence)/2)/100) * (incoming * 0.75f));
                case 1:
                    if(blockT == 1 && block) incoming /= 4;
                    else if(blockT == 0 && block) incoming -= incoming/4;
                    std::cout << "Player damage taken: " << incoming - ((((stats.defence + suit.defence)/2)/100) * (incoming * 0.75f)) << "\n";
                    
                    return incoming - ((((stats.defence + suit.defence)/2)/100) * (incoming * 0.75f));
                default:
                    return -1;
            }
        }
    }
    
    void changeAnimation(std::string name){
        if(name == "Idle"){
            currentAnimation = idle;
            textureBack = idle.spriteSheet;
        }else if(name == "Physical"){
            currentAnimation = AttackP;
            textureBack = AttackP.spriteSheet;
        }else if(name == "Special"){
            currentAnimation = AttackS;
            textureBack = AttackS.spriteSheet;
        }
    }
    
    void animation(){
        frameCounter++;

        if (frameCounter >= (60/currentAnimation.frameSpeed))
        {
            frameCounter = 0;
            currentFrame++;

            if (currentFrame > currentAnimation.frameCount-1){
                currentFrame = 0;
                if(!currentAnimation.loop) changeAnimation("Idle");
            }

            animRec.x = (float)currentFrame*(float)currentAnimation.width/currentAnimation.frameCount;
            animRec.y = 0;
        }

    }
    
    
    Vector2 center(){
        return {position.x + width/2, position.y + height/2};
    }

    
};