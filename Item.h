#include "raylib.h"
#include <string>
#pragma once
class Item{
    public:
        std::string name;
        Texture2D texture;
        int type;
        int factor;
        bool scalable = false;
        int id;
        std::string description;
        Item(std::string name, Texture2D texture, int type, int factor, int id, std::string description){
            this->name = name;
            this->texture = texture;
            this->type = type;
            this->factor = factor;
            this->id = id;
            this->description = TextBreakup(25 ,description);
        }
        Item(std::string name, Texture2D texture, int type, int factor, int id, std::string description, bool scalable){
            this->name = name;
            this->texture = texture;
            this->type = type;
            this->factor = factor;
            this->id = id;
            this->scalable = scalable;
            this->description = TextBreakup(25 ,description);
        }
        
        std::string TextBreakup(int dist, std::string breaker){
            
            std::string result = "";
            REDO:
            int counter = 0;
            for(int i = 0; i < breaker.length(); i++){
                ++counter;
                if(counter == dist){
                    
                    while(breaker[counter] != ' ' && breaker[counter] != '.'){
                        counter++;
                    }
                    result += breaker.substr(0, counter);
                    result += "\n";
                    breaker = breaker.substr(counter);
                    counter = 0;
                    goto REDO;
                }
            }
            
            return result;
        }
};