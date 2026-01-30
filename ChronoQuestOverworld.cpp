/**************************************************************************************************************
*
*   COOL LITTLE GAME IN C++, USING: RAYLIB 5.0
*
**************************************************************************************************************/



     //---------------------------------------------------------------------------//
    //  NOTE:                                                                    //            
   //     when subtracting from an objects position on the y axis; it will      //
  //      appear to be moving up and vise versa meaning that, up is a          // 
 //       lower value or negative, while down is a positive or higher number  // 
//---------------------------------------------------------------------------//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <queue>
#include <fstream>
#include <sstream>

#include "Wall.h"
#include "raylib.h"
#include "Player.h"
#include "NPC.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
Player player(100, 100, {200, 400}, "Player", 3, 50, {100,100,10,10,10,10,10}, {10,10,10,10,100,100});
std::vector<Wall> walls;
std::vector<Npc> npcs; 
Vector2 playerSpawn;
template <typename T> void coll(float distance, char axis, std::vector<T> *toCheck);
void savelevel (std::vector<Wall> Objcts, Player);
void loadlevel (std::string map);
Vector2 mousePositionWorld;

bool editor = false;
int main(void){
    

    /*
    Wall one(100, 100, {4500, 100}, BLUE);
    walls.push_back(one);
    Wall two(300, 100, {-300, 250}, BLUE);
    walls.push_back(two);
    Wall three(100, 300, {450, -300}, BLUE);
    walls.push_back(three);
    Wall four(300, 300, {0, -150},true, GREEN);
    walls.push_back(four);
    Wall five(100, 100, {200, 200}, true, GREEN);
    walls.push_back(five);
    Wall six(100, 100, {300, 0}, true, GREEN);
    walls.push_back(six);
    Wall sv(100,100, {0,300}, true, GREEN);
    walls.push_back(sv);
    */
    bool dragging = false;
    bool resizing = false;
    int index = -1;

    // Initialization
    //--------------------------------------------------------------------------------------
    //creating variables to set the screen dimentions to
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    
    
    
    InitWindow(screenWidth, screenHeight, " |ChronoQuest: Fractures In Time| "); //initilisation of the window 

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    
        
    //initializes camera values
    Camera2D camera = { 0 };
    camera.offset = {screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    camera.target = {800,450};
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    
    loadlevel("Map.txt");
    
    while (!WindowShouldClose()){    // Detect window close button or ESC key
    
        mousePositionWorld = GetScreenToWorld2D({GetMouseX(), GetMouseY()}, camera);
        
        camera.target = lerpV(camera.target, {player.position.x + player.width / 2, player.position.y + player.height / 2}, 0.2);
       
        
        if (IsKeyPressed(KEY_R)){
            editor = !editor;
        }
       
        
         if (IsKeyDown(KEY_W)){
            coll<Npc>(-10, 'y', &npcs);
            coll<Wall>(-10, 'y', &walls);
          }
        else if (IsKeyDown(KEY_A)){
            coll<Npc>(-10, 'x', &npcs);
            coll<Wall>(-10, 'x', &walls);
            
          }
        else if (IsKeyDown(KEY_S)){
            coll<Npc>(10, 'y', &npcs);
            coll<Wall>(10, 'y', &walls);
            
          }
        else if (IsKeyDown(KEY_D)){
            coll<Npc>(10, 'x', &npcs);
            coll<Wall>(10, 'x', &walls);
            
          }
        else if (IsKeyDown(KEY_UP)){
            coll<Npc>(-10, 'y', &npcs);
            coll<Wall>(-10, 'y', &walls);
            
          }
        else if (IsKeyDown(KEY_LEFT)){
            coll<Npc>(-10, 'x', &npcs);
            coll<Wall>(-10, 'x', &walls);
            
          }
        else if (IsKeyDown(KEY_DOWN)){
            coll<Npc>(10, 'y', &npcs);
            coll<Wall>(10, 'y', &walls);
            
          }
        else if (IsKeyDown(KEY_RIGHT)){
            coll<Npc>(10, 'x', &npcs);
            coll<Wall>(10, 'x', &walls);
            
        }else{
            coll<Npc>(0, 'x', &npcs);
            coll<Npc>(0, 'y', &npcs);
            coll<Wall>(0, 'x', &walls);
            coll<Wall>(0, 'y', &walls);
        }
      if (IsKeyPressed(KEY_SPACE)){
          savelevel(walls, player);
      }
        
        
        
     
        // Draw, where the scene actually gets rendered and drawn out
        BeginDrawing();
            
            
            
            //anything drawn inside of the BeginMode2D() and EndMode2D() are going to be drawn onto the world and wont move with the camera but anything drawn after EndMode2D() is drawn onto the screen and moves with the camera useful for UI
                BeginMode2D(camera);
                
                  
                ClearBackground(WHITE);
                //draws the player
                DrawRectangle(player.position.x,player.position.y,player.width,player.height,ORANGE);
                
                
                
                
                for(int i = 0; i < walls.size(); i++){
                    if(editor) DrawRectangleLines(walls[i].position.x,walls[i].position.y,walls[i].width, walls[i].height,walls[i].sqrColor);
                    else DrawRectangle(walls[i].position.x,walls[i].position.y,walls[i].width, walls[i].height,walls[i].sqrColor);
                }
                
                if (editor){
                    for (int i = 0; i < walls.size(); i++){
                        DrawRectangleRec({walls.at(i).position.x + walls.at(i).width, walls.at(i).position.y + walls.at(i).height, 20, 20}, BLUE);
                        if (CheckCollisionPointRec(mousePositionWorld, {walls.at(i).position.x + walls.at(i).width, walls.at(i).position.y + walls.at(i).height,20,20}) && IsMouseButtonPressed(0)){
                            resizing = true;
                            index = i;                            
                        }
                        if (CheckCollisionPointRec(mousePositionWorld, {walls.at(i).position.x, walls.at(i).position.y, walls.at(i).width, walls.at(i).height}) && IsMouseButtonPressed(0)){
                            dragging = true;
                            index = i;                            
                        }
                    }
                        
                    if (resizing){
                        walls[index].width += GetMouseDelta().x;
                        walls[index].height += GetMouseDelta().y;
                    }
                    
                    if (dragging){
                        walls[index].position.x += GetMouseDelta().x;
                        walls[index].position.y += GetMouseDelta().y;
                    }
                    
                    if(IsMouseButtonReleased(0)){
                        resizing = false;
                        dragging = false;
                        index = -1;
                    }
                
                }
        

                
                EndMode2D();
                //UI elements past this point
                DrawFPS(0,0);
           
        //ends the drawing phase of the program     
        EndDrawing();
        //----------------------------------------------------------------------------------
    } 
     
     

    // De-Initialization
    //--------------------------------------------------------------------------------------
      // Texture unloading
      

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
//function for collision handleling that takes paramaters for the distance desired to move and the axis on which to move
template<typename T> void coll(float distance, char axis, std::vector<T> *toCheck){
    //boolean to keep trabk of whether a collision was detected in th function
    bool collision = false;
    //collision on x axis
    if (axis == 'x'){
        //loops through a vector of Wall objects to check for collision
        for(int i = 0; i < toCheck->size(); i++){
            //uses raylibs built in collision detection functino given two Rec objects as paramaters 
            if (CheckCollisionRecs({player.position.x + distance, player.position.y, player.width, player.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y, toCheck->at(i).width, toCheck->at(i).height})){
                
                
                //determines if the players starting position is on the left of the objected collided with
                if(player.position.x < toCheck->at(i).position.x + toCheck->at(i).width / 2){
                    if(toCheck->at(i).moveable){
                    
                    
                    //if the wall is movable then the player pushes it along to the left
                        toCheck->at(i).position.x += (player.position.x + player.width) - toCheck->at(i).position.x + 10;
                        
                    }else{
                    //sets the players position to the edge of the object hit (left)
                        player.position.x = toCheck->at(i).position.x - player.width;
                        collision = true;
                    }
                    //sets the players position to the edge of the object hit (left)
                    
                    
                    
                }else{
                    if(toCheck->at(i).moveable){
                        //if the wall is movable then the player pushes it along to the right
                        toCheck->at(i).position.x -= (toCheck->at(i).position.x + toCheck->at(i).width) - player.position.x + 10;
                        
                        
                    }else{
                        //sets the players position to the edge of the object hit (right) 
                        player.position.x = toCheck->at(i).position.x + toCheck->at(i).width;
                        collision = true;
                    }
                    //sets the players position to the edge of the object hit () right
                    
                    
                }
            }
        }
     //collision on y axis
    }else if (axis == 'y'){
        //loops through a vector of Wall objects to check for collision
        for(int i = 0; i < toCheck->size(); i++){
            //uses raylibs built in collision detection function given two Rec objects as paramaters 
            if (CheckCollisionRecs({player.position.x, player.position.y + distance, player.width, player.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width, toCheck->at(i).height})){
                //determines if the players starting position is above of the objected collided with
                if (player.position.y < toCheck->at(i).position.y + toCheck->at(i).height / 2){
                    //checks if the wall is moveable and pushes it
                    if (toCheck->at(i).moveable){
                        toCheck->at(i).position.y += (player.position.y + player.height) - toCheck->at(i).position.y + 10;

                        
                    }else{
                        player.position.y = toCheck->at(i).position.y - player.height;
                        collision = true;
                    }
                    //sets the players position to the edge of the object hit (above)
                    

                }else{
                    if (toCheck->at(i).moveable){
                        toCheck->at(i).position.y -= (toCheck->at(i).position.y + toCheck->at(i).height) - player.position.y + 10;
                        
                    }else{
                        player.position.y = toCheck->at(i).position.y + toCheck->at(i).height;
                        collision = true;
                    }
                    //sets the players position to the edge of the object hit (below)
                }
            }   
        }
    
    
    }
    
    // code where wall collision is preformed agianst other walls (pushable walls)
    for (int i = 0; i < toCheck->size(); i++){
        for (int j = 0; j < toCheck->size(); j++){
            //only checks collision if the wall at i is a movable wall and, its not the same as wall at j and, if wall at i is closer to the player than wall at j
            if (toCheck->at(i).moveable && j != i && abs(Distance(toCheck->at(i).position, player.position)) < abs(Distance(toCheck->at(j).position, player.position))){
                //splits collision between the x and y axis respectivly 
               if (axis == 'x'){
                   //checks for a collision between wall at i and wall at j using raylibs built in CheckCollisionRecs() function
                   if (CheckCollisionRecs({toCheck->at(i).position.x, toCheck->at(i).position.y, toCheck->at(i).width, toCheck->at(i).height},{toCheck->at(j).position.x, toCheck->at(j).position.y, toCheck->at(j).width, toCheck->at(j).height})){
                       //splits the way collision is handled depending if the wall is on the left or right of its collision respectivly
                       if (toCheck->at(i).position.x + (toCheck->at(i).width / 2) < toCheck->at(j).position.x + (toCheck->at(j).width / 2)){
                           toCheck->at(i).position.x = toCheck->at(j).position.x - toCheck->at(i).width;
                           if (CheckCollisionRecs({player.position.x, player.position.y, player.width, player.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                           //player.position.x = toCheck->at(i).position.x - player.width;
                            player.position.x = toCheck->at(i).position.x - player.width;
                            collision = true;
                           }
                       //splits the way collision is handled depending if the wall is on the left or right of its collision respectivly
                       }else{
                           toCheck->at(i).position.x = toCheck->at(j).position.x + toCheck->at(i).width;
                           if (CheckCollisionRecs({player.position.x, player.position.y, player.width, player.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                           //player.position.x = toCheck->at(i).position.x + toCheck->at(i).width;
                            player.position.x = toCheck->at(i).position.x + player.width ;
                            collision = true;
                           }
                       }
                   }
                //splits collision between the x and y axis respectivly 
               }else if (axis == 'y'){
                   //checks for a collision between wall at i and wall at j using raylibs built in CheckCollisionRecs() function
                   if (CheckCollisionRecs({toCheck->at(i).position.x, toCheck->at(i).position.y, toCheck->at(i).width, toCheck->at(i).height},{toCheck->at(j).position.x,    toCheck->at(j).position.y, toCheck->at(j).width, toCheck->at(j).height})){
                       //splits the way collision is handled depending if the wall is above or below of its collision respectivly
                       if (toCheck->at(i).position.y - (toCheck->at(i).height / 2) < toCheck->at(j).position.y - (toCheck->at(j).height / 2)){
                           toCheck->at(i).position.y = toCheck->at(j).position.y - toCheck->at(i).height;
                           if (CheckCollisionRecs({player.position.x, player.position.y, player.width, player.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                                player.position.y = toCheck->at(i).position.y - player.height;
                                collision = true;
                           }
                       //splits the way collision is handled depending if the wall is above or below of its collision respectivly
                       }else{
                           toCheck->at(i).position.y = toCheck->at(j).position.y + toCheck->at(i).height;
                           if (CheckCollisionRecs({player.position.x, player.position.y, player.width, player.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                                player.position.y = toCheck->at(i).position.y + player.height;
                                collision = true;
                           }
                       }
                   }
               }
            }
        }
    }
    
    
    
    //if no collisin was detected then the player is free to move the desired distance
    if (!collision){
        if (axis == 'x'){
        player.position.x += distance;
        }else if (axis == 'y'){
            player.position.y += distance;
        }
    }
    
    
   

}
    void savelevel(std::vector<Wall> Objcts, Player){
        std::ostringstream mapName;
        std::ifstream mapFind;
        mapName << "Map.txt";

        mapFind.open(mapName.str(), std::ifstream::in);
        if (!mapFind.is_open()){
            std::cout << "file not open";
        }
        std::cout << mapName.str();
        mapFind.close();
        std::ofstream mapFile(mapName.str());
        std::ostringstream pushFile;
        pushFile << "OBJECTS\n";
        for(Wall obj : walls){
            pushFile << obj.position.x;
            pushFile << ", ";
            pushFile << obj.position.y;
            pushFile << ", ";
            pushFile << obj.width;
            pushFile << ", ";
            pushFile << obj.height;
            pushFile << ", ";
            if(obj.moveable == true){
                obj.moveable = 1;
            }
            pushFile << obj.moveable;
            pushFile << "; \n";
        }
            pushFile << "PLAYER\n";
            pushFile << player.position.x;
            pushFile << ", ";
            pushFile << player.position.y;
            pushFile << ", ";
            pushFile << player.width;
            pushFile << ", ";
            pushFile << player.height;
            pushFile << ", ";
            pushFile << playerSpawn.x;
            pushFile << ", ";
            pushFile << playerSpawn.y;
            pushFile << "; \n";
        std::string add = pushFile.str();
        mapFile << add;
        mapFile.close();
    }
    void loadlevel(std::string Map){
        std::ifstream mapFile(Map);
        std::string mapContents;
        
        
        if(mapFile){
            std::string mapLine;
            while (getline( mapFile, mapLine)){
                mapContents += mapLine + "\n";
            }
            mapFile.close();
        }
        
        mapContents = mapContents.substr(7);
        int counter = 0;
        bool stop = false;
        bool objs = false;
        
        std::vector<Wall> obj;
        
        int arrayPos = 0;
        int dataList[5];
        while(!objs){

            try{
                while(mapContents.at(counter) != ',' && mapContents.at(counter) != ';'){
                    if (mapContents.at(counter) == 'X') objs = true;
                    else if (mapContents.at(counter) == ';') stop = true;
                    else{
                      counter++;
                      std::cout << counter << ", ";                      
                    } 
                }
                if(objs)break;
                std::cout << mapContents.substr(0,counter) << "\n";
                
                dataList[arrayPos] = std::stoi(mapContents.substr(0,counter));
                if(arrayPos < 4)arrayPos++;
                else{
                    arrayPos = 0;
                    Wall obj1(dataList[3],  dataList[2], {dataList[0], dataList[1]}, dataList[4], BLACK);
                    obj.push_back(obj1);
                  
                }
                
                mapContents = mapContents.substr(counter + 2);
                
                counter = 0;
                std::cout << "\n";
                walls = obj;
               
                
            }catch(...){
              walls = obj;
              objs = true;
            }
        }
        
        
    }
    
    
    