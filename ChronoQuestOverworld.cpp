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
#include <cstdlib>

#include "Wall.h"
#include "raylib.h"
#include "Player.h"
#include "NPC.h"
#include "Enemy.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
Player player(100, 100, {200, 400}, "Player", 3, 50, {100,100,10,10,10,10,10}, {10,10,10,10,100,100});
std::vector<Wall> walls;
std::vector<Npc> npcs; 
std::vector<Enemy> enemies;
Vector2 playerSpawn;
template <typename T> void coll(float distance, char axis, std::vector<T> *toCheck);
void savelevel (std::vector<Wall> Objcts, Player);
void updWalls ();
void loadlevel (std::string map);
Vector2 mousePositionWorld;

bool placeMenu = false;

bool editor = false;
bool place = false;
int main(void){
    
    
     typedef struct{
        Vector2 position;
        Vector2 size;
        int type;
        Texture2D* extd;
        std::string wallname;
    }Placer;
    
    std::vector<Placer> builder;
    
    Placer moveableWall{{0,150}, {150,150}, 1, NULL, "push"};
    Placer nonMoveableWall{{0,150}, {150,150}, 2, NULL, "nonpush"};
    Placer NPCenemy{{0,150}, {150, 150}, 3, NULL, "enemy"};
    
    builder.push_back(moveableWall);
    builder.push_back(nonMoveableWall);
    builder.push_back(NPCenemy);
 
    bool dragging = false;
    bool resizing = false;
    int index = -1;
    int indexc = -1;

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
    
    while (!WindowShouldClose()){   
        
        for (int i = 0; i < walls.size(); i++){
            if (walls.at(i).positionNPC != NULL){
                walls.at(i).position = *walls.at(i).positionNPC;
            }
        }

    // Detect window close button or ESC key
        for (int i = 0; i < walls.size(); i++){
            if(walls.at(i).positionNPC != NULL){
                walls.at(i).position = *walls.at(i).positionNPC;
            }
        }
        mousePositionWorld = GetScreenToWorld2D({GetMouseX(), GetMouseY()}, camera);
        
        
        for(int i = 0; i < npcs.size(); i++){
            walls.at(*npcs.at(i).wallp).positionNPC = &npcs.at(i).position;
        }
        
        
        if(!editor){
            camera.target = lerpV(camera.target, {player.position.x + player.width / 2, player.position.y + player.height / 2}, 0.2);
        }else if(IsMouseButtonDown(2)){
            camera.target = vectorAddition(camera.target, {-GetMouseDelta().x / camera.zoom, -GetMouseDelta().y / camera.zoom});
        }
        
       
        
        if (IsKeyPressed(KEY_R)){
            editor = !editor;
        }
       
       
        
        if(!editor){
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
            
        camera.zoom = 1.0f;    
        }else{
            camera.zoom += GetMouseWheelMove()* 0.05;
        }
        if (IsKeyPressed(KEY_SPACE)){
              savelevel(walls, player);
        }
        if (IsKeyPressed(KEY_F)){
            std::system("cls");
            for (int i = 0 ; i < walls.size(); i++){
                std::cout << "\n" << npcs.size() << "\n" << std::to_string(walls.at(i).index).c_str() << "\n" ;
            }
        }
     
        // Draw, where the scene actually gets rendered and drawn out
        BeginDrawing();
            
            
            
            //anything drawn inside of the BeginMode2D() and EndMode2D() are going to be drawn onto the world and wont move with the camera but anything drawn after EndMode2D() is drawn onto the screen and moves with the camera useful for UI
                BeginMode2D(camera);
                
                  
                ClearBackground(WHITE);
                //draws the player
                DrawRectangle(player.position.x,player.position.y,player.width,player.height,ORANGE);
                
                
                
                
                for(int i = 0; i < walls.size(); i++){
                    if(editor){
                        if(walls.at(i).moveable && walls.at(i).positionNPC == NULL){
                            DrawRectangleLines(walls[i].position.x,walls[i].position.y,walls[i].width, walls[i].height, GREEN);
                            DrawText(std::to_string(walls.at(i).index).c_str(), walls[i].position.x, walls[i].position.y, 20 , BLACK );
                        }else if (!walls.at(i).moveable && walls.at(i).positionNPC == NULL){
                            DrawRectangleLines(walls[i].position.x,walls[i].position.y,walls[i].width, walls[i].height, BLUE);
                            DrawText(std::to_string(walls.at(i).index).c_str(), walls[i].position.x, walls[i].position.y, 20 , BLACK );
                        }else if (walls.at(i).positionNPC != NULL){
                            DrawRectangleLines(walls[i].position.x,walls[i].position.y,walls[i].width, walls[i].height, RED);
                            //DrawTextEx(GetFontDefault(), std::to_string(walls.at(i).index).c_str(), {0,0}, 2, 20, BLACK );
                            //DrawText("Busss", 10, 10, 2, BLACK);
                        }
                        
                    } 
                    else{
                        if(walls.at(i).moveable && walls.at(i).positionNPC == NULL){
                            DrawRectangle(walls[i].position.x,walls[i].position.y,walls[i].width, walls[i].height, GREEN);
                        }else if (!walls.at(i).moveable && walls.at(i).positionNPC == NULL){
                            DrawRectangle(walls[i].position.x,walls[i].position.y,walls[i].width, walls[i].height, BLUE);
                        }else if (walls.at(i).positionNPC != NULL){
                            DrawRectangle(walls[i].position.x,walls[i].position.y,walls[i].width, walls[i].height, RED);
                        }
                        
                    }
                }
                
                if (editor){
                    for (int i = 0; i < walls.size(); i++){
                        DrawRectangleRec({walls.at(i).position.x + walls.at(i).width, walls.at(i).position.y + walls.at(i).height, (20 / camera.zoom), (20 / camera.zoom)}, BLUE);
                        if (CheckCollisionPointRec(mousePositionWorld, {walls.at(i).position.x + walls.at(i).width, walls.at(i).position.y + walls.at(i).height,(20 / camera.zoom), (20 / camera.zoom)}) && IsMouseButtonPressed(0)){
                            resizing = true;
                            index = i;                            
                        }
                        if (CheckCollisionPointRec(mousePositionWorld, {walls.at(i).position.x, walls.at(i).position.y, walls.at(i).width, walls.at(i).height}) && IsMouseButtonPressed(0)){
                            dragging = true;
                            index = i;                            
                        }
                    }
                        
                    if (resizing){
                        walls[index].width += GetMouseDelta().x / camera.zoom;
                        walls[index].height += GetMouseDelta().y / camera.zoom;
                    }
                    
                    if (dragging){
                        if (walls[index].positionNPC == NULL){
                            walls[index].position.x += GetMouseDelta().x / camera.zoom;
                            walls[index].position.y += GetMouseDelta().y / camera.zoom;
                        }else{
                            walls[index].positionNPC->x += GetMouseDelta().x / camera.zoom;
                            walls[index].positionNPC->y += GetMouseDelta().y / camera.zoom ;
                        }
                        
                    }
                    
                    if(IsMouseButtonReleased(0)){
                        resizing = false;
                        dragging = false;
                        index = -1;
                    }

                     if (place){
                        SetMouseCursor(3);
                        if (IsMouseButtonPressed(0)){
                                if (builder.at(indexc).type == 1){
                                    Wall wallp(100,100, vectorAddition(mousePositionWorld, {-50,-50}), true, BLACK);
                                    walls.push_back(wallp);
                                    place = false;
                                    placeMenu = false;
                                    updWalls();
                                }else if (builder.at(indexc).type == 2){
                                    Wall wallp(100,100, vectorAddition(mousePositionWorld, {-50,-50}), BLACK);
                                    walls.push_back(wallp);
                                    place = false;
                                    placeMenu = false;
                                    updWalls();
                                }else if (builder.at(indexc).type == 3){
                                    Npc enemy( 100, 100, vectorAddition(mousePositionWorld, {-50,-50}), "bussy", 'N');
                                    npcs.push_back(enemy);
                                    Wall temp(enemy.height, enemy.width, &enemy.position, false, RED);
                                    enemy.collider = &temp;
                                    enemy.collider->index = walls.size();
                                    walls.push_back(*enemy.collider);
                                    enemy.wallp = &enemy.collider->index;
                                    place = false;
                                    placeMenu = false;
                                    updWalls();
                                }
                        }
                    }
                    for (int i = 0; i < walls.size(); i++){
                        if (CheckCollisionPointRec(mousePositionWorld, {walls.at(i).position.x, walls.at(i).position.y, walls.at(i).width, walls.at(i).height}) && IsMouseButtonPressed(1)){
                            
                            for (int j = 0 ; j < npcs.size(); i++){
                                
                                if (walls.at(i).index == *npcs.at(j).wallp){
                                    npcs.erase(npcs.begin() + j);
                                }
                                
                            }
                            walls.erase(walls.begin() + i);
                            updWalls();
                        }
                    }

                }
                if (!place){
                        SetMouseCursor(1);
                    }
        

                
                EndMode2D();
                //UI elements past this point

                if (editor){
                    if (placeMenu && !place){
                        DrawRectangle(100, 100 , 1400, 750, GRAY);
                        for(int i = 0; i < builder.size(); i++){
                            builder.at(i).position.x = (builder.at(i).size.x + 50) * (i + 1);
                            DrawRectangleLines(builder.at(i).position.x, builder.at(i).position.y, builder.at(i).size.x, builder.at(i).size.y, BLACK);
                            DrawText(builder.at(i).wallname.c_str(), builder.at(i).position.x, builder.at(i).position.y, 20 , RED );
                            if (CheckCollisionPointRec({GetMouseX(), GetMouseY()}, {builder.at(i).position.x, builder.at(i).position.y, builder.at(i).size.x, builder.at(i).size.y})){
                                builder.at(i).size.x = 160;
                                builder.at(i).size.y = 160;
                            }else{
                                builder.at(i).size.x = 150;
                                builder.at(i).size.y = 150;
                            }
                            if (IsMouseButtonPressed(0) && CheckCollisionPointRec({GetMouseX(), GetMouseY()}, {builder.at(i).position.x, builder.at(i).position.y, builder.at(i).size.x, builder.at(i).size.y})){
                                place = true;
                                indexc = i;
                            }
                        }

                    }
                    if (IsKeyPressed(KEY_EQUAL)){
                        placeMenu = !placeMenu;
                        
                    }
                }

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
    Vector2 temp = player.position;
    //collision on x axis
    if (axis == 'x'){
        //loops through a vector of Wall objects to check for collision
        for(int i = 0; i < toCheck->size(); i++){
            
            //uses raylibs built in collision detection functino given two Rec objects as paramaters 
            if (CheckCollisionRecs({player.position.x + distance, player.position.y, player.width, player.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y, toCheck->at(i).width, toCheck->at(i).height})){
                
                
                //determines if the players starting position is on the left of the objected collided with
                if(player.position.x + player.width / 2 < toCheck->at(i).position.x + toCheck->at(i).width / 2){
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
                if (player.position.y + player.height / 2 < toCheck->at(i).position.y + toCheck->at(i).height / 2){
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
            if (toCheck->at(i).moveable && j != i && abs(Distance(vectorAddition(toCheck->at(i).position, {toCheck->at(i).width/2, toCheck->at(i).height/2}), player.center())) < abs(Distance(vectorAddition(toCheck->at(j).position, {toCheck->at(j).width/2, toCheck->at(j).height/2}), player.center()))){
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
                           toCheck->at(i).position.x = toCheck->at(j).position.x + toCheck->at(j).width;
                           if (CheckCollisionRecs({player.position.x, player.position.y, player.width, player.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                           //player.position.x = toCheck->at(i).position.x + toCheck->at(i).width;
                            player.position.x = toCheck->at(i).position.x + toCheck->at(i).width;
                            collision = true;
                           }
                       }
                   }
                //splits collision between the x and y axis respectivly 
               }else if (axis == 'y'){
                   //checks for a collision between wall at i and wall at j using raylibs built in CheckCollisionRecs() function
                   if (CheckCollisionRecs({toCheck->at(i).position.x, toCheck->at(i).position.y, toCheck->at(i).width, toCheck->at(i).height},{toCheck->at(j).position.x,    toCheck->at(j).position.y, toCheck->at(j).width, toCheck->at(j).height})){
                       //splits the way collision is handled depending if the wall is above or below of its collision respectivly
                       if (toCheck->at(i).position.y + (toCheck->at(i).height / 2) < toCheck->at(j).position.y + (toCheck->at(j).height / 2)){
                           toCheck->at(i).position.y = toCheck->at(j).position.y - toCheck->at(i).height;
                           if (CheckCollisionRecs({player.position.x, player.position.y, player.width, player.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                                player.position.y = toCheck->at(i).position.y - player.height;
                                collision = true;
                           }
                           
                           
                       //splits the way collision is handled depending if the wall is above or below of its collision respectivly
                       }else{
                           toCheck->at(i).position.y = toCheck->at(j).position.y + toCheck->at(j).height;
                           if (CheckCollisionRecs({player.position.x, player.position.y, player.width, player.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                                player.position.y = toCheck->at(i).position.y + toCheck->at(i).height;
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
            /*pushFile << ", ";
            pushFile << playerSpawn.x;
            pushFile << ", ";
            pushFile << playerSpawn.y;*/
            pushFile << "; \n";
            
            for(int i = 0; i < npcs.size(); i++){
                    pushFile << "ENEMY\n";
                    pushFile << npcs.at(i).position.x;
                    pushFile << ", ";
                    pushFile << npcs.at(i).position.y;
                    pushFile << ", ";
                    pushFile << npcs.at(i).collider->index;
                    pushFile << "; \n";
            }
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
        Vector2 vroPos;
        std::vector<Wall> obj;
        std::vector<Npc> npcTemp;
        int arrayPos = 0;
        int dataList[5];
        while(!objs){

            try{
                while(mapContents.at(counter) != ',' && mapContents.at(counter) != ';'){
                    if (mapContents.at(counter) == ';') stop = true;
                    else{
                      counter++;                     
                    } 
                }
                
                dataList[arrayPos] = std::stoi(mapContents.substr(0,counter));
                if(arrayPos < 4)arrayPos++;
                else{
                    arrayPos = 0;
                    Wall obj1(dataList[3],  dataList[2], {dataList[0], dataList[1]}, dataList[4], BLACK);
                    obj.push_back(obj1);
                  
                }
                
                mapContents = mapContents.substr(counter + 2);
                
                counter = 0;
                walls = obj;
               
                
            }catch(...){
              walls = obj;
              objs = true;
            }
        }

        mapContents = mapContents.substr(8);
        counter = 0;
        while(mapContents.at(counter) != ',' && mapContents.at(counter) != ';'){
            if (mapContents.at(counter) == ';') break;
            else{
                counter++;                 
            } 
        }
        dataList[0] = std::stoi(mapContents.substr(0,counter));
        mapContents = mapContents.substr(counter + 2);
        counter = 0;
        while(mapContents.at(counter) != ',' && mapContents.at(counter) != ';'){
            if (mapContents.at(counter) == ';') break;
            else{
                counter++;                
            } 
        }
        dataList[1] = std::stoi(mapContents.substr(0,counter));
        
        player.position = {dataList[0], dataList[1]};
        mapContents = mapContents.substr(counter + 2);

        counter = 0;
        mapContents = mapContents.substr(6);
        while(!objs){

            try{
                while(mapContents.at(counter) != ',' && mapContents.at(counter) != ';'){
                    if (mapContents.at(counter) == ';') stop = true;
                    else{
                      counter++;                     
                    } 
                }
                
                dataList[arrayPos] = std::stoi(mapContents.substr(0,counter));
                if(arrayPos < 3)arrayPos++;
                else{
                    arrayPos = 0;
                    Npc enemy1(100, 100, {dataList[0], dataList[1]}, "EnemyFella", 'n');
                    npcTemp.push_back(enemy1);
                    enemy1.wallp = &walls.at(dataList[2]).index;
                    enemy1.collider = &walls.at(*enemy1.wallp);
                    walls.at(*enemy1.wallp).positionNPC = &enemy1.position;
           
                  
                }
                
                mapContents = mapContents.substr(counter + 2);
                
               npcs = npcTemp;
                
            }catch(...){
              objs = true;
              npcs = npcTemp;
            }
        }
        for(int i = 0; i < npcs.size(); i++){
            std::cout << "\n" <<npcs.at(i).wallp << "\n";
        }
    }
    
    void updWalls(){
        for(int i = 0; i < walls.size(); i++){
            walls.at(i).index = i;
            
        }
    }