#include <stdio.h>
#include <raylib.h>
#include<conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "game.h"

// #define SCREEN_WIDTH 1200 //800
// #define SCREEN_HEIGHT 450 //600
// #define TILE_SIZE 30 //40
// #define MAP_WIDTH 40
// #define MAP_HEIGHT 15

 Texture pacr , pacl , pacu , pacd; // right left up down
    Texture pac2; // closed
    Texture ghost;  
    Texture followingghost;  
    Texture heart;
    Texture cherryT;
    Texture AppleT;
    Texture MushroomT;
    Texture peperT; 
    Sound ghosteat ;
    Sound ClaimStar;
    Sound GameOver;

 Color red = {220 , 76, 39,0};
int gameMap[MAP_HEIGHT][MAP_WIDTH] = {// 0 = empty // 1 = wall // 2 = star // 3 = apple // 4 = Cherry //5= mushroom //6= peper
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

 int option = 0;
 int replay = 1;
  int animcounter;
 Player pacman;
 Ghost ghosts[5];
 Ghost ghostcopy[5];
 Cherry cherry;
 Apple apple;
 Mushroom mushroom;
 Peper peper;
 int health = 0;
 int starcount = 10;
 bool gameRunning = false;
 bool recordsRunning = false;
 bool caneatghosts = false;
 int n = 1; // for peper and normal -> peper = 2 , normal = 1 , update pacman while controller
 int applerespawntime;
 int cherryrespawntime;

void loadtexture(){
    Image image = LoadImage("../images/pcmn.png");
    pacr = LoadTextureFromImage(image);
    image = LoadImage("../images/pcmnleft.png");
    pacl = LoadTextureFromImage(image);
    image = LoadImage("../images/pcmnup.png");
    pacu = LoadTextureFromImage(image);
    image = LoadImage("../images/pcmndown.png");
    pacd = LoadTextureFromImage(image);
    image = LoadImage("../images/ghost.png");
    ghost = LoadTextureFromImage(image);
    image = LoadImage("../images/heart.png");
    heart = LoadTextureFromImage(image);
    image = LoadImage("../images/cherry.png");
    cherryT = LoadTextureFromImage(image);
    image = LoadImage("../images/apple.png");
    AppleT = LoadTextureFromImage(image);
    image = LoadImage("../images/mushrooms.png");
    MushroomT= LoadTextureFromImage(image);
    image = LoadImage("../images/peper.png");
    peperT= LoadTextureFromImage(image);
    image = LoadImage ("../images/following ghost.png");
    followingghost = LoadTextureFromImage(image);
}
void loadsound(){
    ghosteat = LoadSound("../sounds/pacman_eatghost.wav");
    ClaimStar = LoadSound("../sounds/coin.mp3");
    GameOver = LoadSound("../sounds/game-over.mp3");
}
void initstar(int Map[MAP_HEIGHT][MAP_WIDTH]){
    for (int i = 0 ; i < 10 ; i ++){
        int x , y;
        do{
        y = rand() % MAP_HEIGHT ;
        x = rand () % MAP_WIDTH ;
        }while(Map[y][x] != 0);
        Map[y][x] = 2 ;
    }
    starcount = 10 ; 
}
void initapple(int Map[MAP_HEIGHT][MAP_WIDTH]){
    do{
        apple.x = rand() % MAP_WIDTH ; 
        apple.y = rand () % MAP_HEIGHT ; 
        }while(Map[apple.y][apple.x] != 0);
        Map[apple.y][apple.x] = 3 ;
        apple.active = true;
        applerespawntime = 0;
}
void initcherry(int Map[MAP_HEIGHT][MAP_WIDTH]){
    do{
            cherry.x = rand() % MAP_WIDTH ; 
            cherry.y = rand () % MAP_HEIGHT ; 
            }while(Map[cherry.y][cherry.x] != 0);
            Map[cherry.y][cherry.x] = 4 ;
            cherry.active = true;
            cherryrespawntime = 0;
}

void InitGame(int Map[MAP_HEIGHT][MAP_WIDTH]) {
    // Init Pacman
    pacman.x = 1;
    pacman.y = 1;
    pacman.dx = 0;
    pacman.dy = 0;
    pacman.score = 0;

    // Init Ghosts
    //0
        ghosts[0].x = 9 ;
        ghosts[0].y = 8;
        ghosts[0].dx = 1;
        ghosts[0].dy = 0;
        ghosts[0].active = true;
        //1
        ghosts[1].x = 31;
        ghosts[1].y = 8;
        ghosts[1].dx = 1;
        ghosts[1].dy = 0;
        ghosts[1].active = true;
        // 2
        ghosts[2].x = 18 ;
        ghosts[2].y = 5;
        ghosts[2].dx = 0;
        ghosts[2].dy = 1;
        ghosts[2].active = true;
        // 3
        ghosts[3].x = 26 ;
        ghosts[3].y = 8;
        ghosts[3].dx = 0;
        ghosts[3].dy = 1;
        ghosts[3].active = true;
        //4
        ghosts[4].x = 7;
        ghosts[4].y = 2 ; 
        ghosts[4].dx = 0;
        ghosts[4].dy = 1; 
        for(int i =0 ; i < 5 ; i++){
            ghostcopy[i] = ghosts[i];
        }
        //star 
        initstar(Map);
        // apple
        initapple(Map);
                // cherry
        initcherry(Map);
        //mushroom
        do{
        mushroom.x = rand() % MAP_WIDTH ; 
        mushroom.y = rand () % MAP_HEIGHT ; 
        }while(Map[mushroom.y][mushroom.x] != 0);
        Map[mushroom.y][mushroom.x] = 5 ;
        //peper
        do{
        peper.x = rand() % MAP_WIDTH ; 
        peper.y = rand () % MAP_HEIGHT ; 
        }while(Map[peper.y][peper.x] != 0);
        Map[peper.y][peper.x] = 6 ;

    }


void UpdatePacman(int Map[MAP_HEIGHT][MAP_WIDTH]) {
    if(health <= 0){
        gameRunning = false;
        PlaySound(GameOver);
        replay = 0;        
        return ;
    }
   for(int i = 0 ; i < n ; i++){
    int newX = pacman.x +  pacman.dx;
    int newY = pacman.y +  pacman.dy;

    if (Map[newY][newX] != 1) {
        pacman.x = newX;
        pacman.y = newY;
        if (starcount <= 0 )
        initstar(Map);

        if (Map[newY][newX] == 2) {
            pacman.score += 10;
            Map[newY][newX] = 0;
            PlaySound(ClaimStar) ;
            starcount -- ;
        } 
        else if (Map[newY][newX] == 3) {
            if(health < 3){
            health ++ ;
            apple.active = false ;
            applerespawntime = 5 * 15 ;
            Map[newY][newX] = 0;
            }
        }
        else if (Map[newY][newX] == 4){
            caneatghosts = true;
            cherry.timer = 15 * 15 * 5 ; //( 15 * FPS * ghost count) , because there is 5 time loop per frame for check ghosts 
            cherryrespawntime = 20 * 15 ;
            cherry.active = false ;
            Map[newY][newX] = 0;
        }else if (Map[newY][newX] == 5){
            health -- ;
            Map[newY][newX] = 0;
        }else if (Map[newY][newX] == 6){
            n = 2 ;
            peper.active = true;
            peper.timer = 5 * 15 * 5 ;// 5 seconds 
            Map[newY][newX] = 0;
        }
    }if (!apple.active){
        if(applerespawntime <= 0){
        initapple(Map);
        }else if (applerespawntime > 0){
        applerespawntime -- ;
        }
    }if (!cherry.active){
        if (cherryrespawntime <= 0 ){
            initcherry(Map);
        }else
        cherryrespawntime -- ;
    }
}
}

void UpdateGhosts() {
    SetTargetFPS(3);
    int rander;
    int followRange = 3; //following ghost
    for (int i = 0; i < 5; i++) {
        // check death
        if (ghosts[i].x == pacman.x && ghosts[i].y == pacman.y) {
            if (caneatghosts){
                ghosts[i] = ghostcopy[i];
            }else{
            health--;
            pacman.x = 1;
            pacman.y = 1;
            pacman.dx = 0;
            pacman .dy = 0;
            PlaySound(ghosteat);
            if (health <= 0) {
                gameRunning = false;
                PlaySound(GameOver);
                replay = 0;
                }
            }
        }
        //control ghosts directions
         if(gameMap[ghosts[i].y -1][ghosts[i].x] != 1 && gameMap[ghosts[i].y +1][ghosts[i].x] == 1 && gameMap[ghosts[i].y][ghosts[i].x + 1] != 1 && gameMap[ghosts[i].y][ghosts[i].x - 1] != 1){
            if(rand()%2 && ghosts[i].dy != 1){
                ghosts[i].dx = 0;
                ghosts[i].dy = -1;
            }else if (ghosts[i].dy == 1){
                rander = rand()%2 > 0 ? 1 : -1 ;
                ghosts[i].dx = rander * 1 ;
                ghosts[i].dy = 0 ;
            }
        }else if(gameMap[ghosts[i].y +1][ghosts[i].x] != 1 && gameMap[ghosts[i].y -1][ghosts[i].x] == 1 && gameMap[ghosts[i].y][ghosts[i].x + 1] != 1 && gameMap[ghosts[i].y][ghosts[i].x - 1] != 1){ 
            if(rand()%2 && ghosts[i].dy != -1){
                ghosts[i].dx = 0;
                ghosts[i].dy = 1;
            }else if( ghosts[i].dy == -1){
                rander = rand()%2 > 0 ? 1 : -1 ;
                ghosts[i].dx = rander * 1 ;
                ghosts[i].dy = 0 ;  
            }
        }else if(gameMap[ghosts[i].y][ghosts[i].x - 1] != 1 && gameMap[ghosts[i].y ][ghosts[i].x + 1] == 1 && gameMap[ghosts[i].y - 1][ghosts[i].x] != 1 && gameMap[ghosts[i].y + 1][ghosts[i].x] != 1){ 
            if(rand()%2 && ghosts[i].dx != 1){
                ghosts[i].dx = -1;
                ghosts[i].dy = 0;
            }else if(ghosts[i].dx == 1 ){
                rander = rand()%2 > 0 ? 1 : -1 ;
                ghosts[i].dx = 0 ;
                ghosts[i].dy = rander * 1 ;
            }
        }else if(gameMap[ghosts[i].y][ghosts[i].x + 1] != 1 && gameMap[ghosts[i].y ][ghosts[i].x - 1] == 1 && gameMap[ghosts[i].y - 1][ghosts[i].x] != 1 && gameMap[ghosts[i].y + 1][ghosts[i].x] != 1){ 
            if(rand()%2 && ghosts[i].dx != -1){
                ghosts[i].dx = 1;
                ghosts[i].dy = 0;
            }else if (ghosts[i].dx == 1){
                rander = rand()%2 > 0 ? 1 : -1 ;
                ghosts[i].dx = 0 ;
                ghosts[i].dy = rander * 1 ;
            }
        }
        // following ghost
        if (abs(ghosts[4].x - pacman.x) <= followRange && abs(ghosts[4].y - pacman.y) <= followRange) {
            DrawText(TextFormat("Pacman Detected") , ghosts[4].x*TILE_SIZE - TILE_SIZE , ghosts[4].y * TILE_SIZE + 7 , 7 ,RED);

        if (ghosts[4].x < pacman.x) { 
        ghosts[4].dx = 1; 
        ghosts[4].dy = 0;
        } else if (ghosts[4].x > pacman.x) {
        ghosts[4].dx = -1; 
        ghosts[4].dy = 0;
        } else if (ghosts[4].y < pacman.y) { 
        ghosts[4].dx = 0; 
        ghosts[4].dy = 1;
        } else if (ghosts[4].y > pacman.y) { 
        ghosts[4].dx = 0;
        ghosts[4].dy = -1;
        }
        }
       
        int newX = ghosts[i].x +  ghosts[i].dx;
        int newY = ghosts[i].y +  ghosts[i].dy;
        
        if (gameMap[newY][newX] == 1 || (newX < 5 && newY < 5) ) {

            // Try to find a new direction
            if (ghosts[i].dx != 0) {
                // Moving horizontally, try vertical directions
                if (gameMap[ghosts[i].y + 1][ghosts[i].x] != 1) {
                    ghosts[i].dx = 0;
                    ghosts[i].dy = 1;
                } else if (gameMap[ghosts[i].y - 1][ghosts[i].x] != 1) {
                    ghosts[i].dx = 0;
                    ghosts[i].dy = -1;
                } else {
                    // Reverse horizontal direction
                    ghosts[i].dx = -ghosts[i].dx;
                }
            } else if (ghosts[i].dy != 0) {
                // Moving vertically, try horizontal directions
                if (gameMap[ghosts[i].y][ghosts[i].x + 1] != 1) {
                    ghosts[i].dx = 1;
                    ghosts[i].dy = 0;
                } else if (gameMap[ghosts[i].y][ghosts[i].x - 1] != 1) {
                    ghosts[i].dx = -1;
                    ghosts[i].dy = 0;
                } else {
                    // Reverse vertical direction
                    ghosts[i].dy = -ghosts[i].dy;
                }
            }
        } else {
            ghosts[i].x = newX;
            ghosts[i].y = newY;
        }
        // for can eat ghosts
          if (caneatghosts) {
        cherry.timer--;
        if (cherry.timer <= 0) {
            caneatghosts = false;
            cherry.timer = 0 ;
        }
    }
    if (peper.active){
        peper.timer -- ;
        if(peper.timer <= 0){
            peper.active = false ;
            n = 1 ;
            peper.timer = 0 ;
        }
    }
        
    }
    SetTargetFPS(15);
}



void DrawGame(int Map[MAP_HEIGHT][MAP_WIDTH]) {
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw map
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (Map[y][x] == 1) {
                DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKBLUE);
            } else if (Map[y][x] == 2) {
                DrawCircle(x * TILE_SIZE + TILE_SIZE / 2, y * TILE_SIZE + TILE_SIZE / 2, 5, YELLOW);
            } else if (Map[y][x] == 3) {
                DrawTexture(AppleT, x * TILE_SIZE , y * TILE_SIZE, WHITE);
            } else if (Map[y][x] ==  4){
                DrawTexture(cherryT , x * TILE_SIZE , y * TILE_SIZE  , WHITE);
            } else if (Map[y][x] ==  5){
                DrawTexture(MushroomT , x * TILE_SIZE , y * TILE_SIZE  , WHITE);
            } else if (Map[y][x] ==  6){
                DrawTexture(peperT , x * TILE_SIZE , y * TILE_SIZE  , WHITE);
            }
        }
    }

    // Draw Pacman
   int anim = animcounter>5 ? 0 : 1; 
    if(anim)
    DrawCircle(pacman.x * TILE_SIZE + TILE_SIZE / 2, pacman.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE / 2 , RED);
    if(!anim){
   if(pacman.dx > 0)
    DrawTexture(pacr , pacman.x * TILE_SIZE + TILE_SIZE / 2 - 20 , pacman.y * TILE_SIZE + TILE_SIZE / 2 - 20 , WHITE);
    else if(pacman.dx < 0)
    DrawTexture(pacl , pacman.x * TILE_SIZE + TILE_SIZE / 2 - 20 , pacman.y * TILE_SIZE + TILE_SIZE / 2 - 20 , WHITE);
    else if(pacman.dy < 0)
    DrawTexture(pacu , pacman.x * TILE_SIZE + TILE_SIZE / 2 - 20 , pacman.y * TILE_SIZE + TILE_SIZE / 2 - 20 , WHITE);
    else if(pacman.dy > 0)
    DrawTexture(pacd , pacman.x * TILE_SIZE + TILE_SIZE / 2 - 20 , pacman.y * TILE_SIZE + TILE_SIZE / 2 - 20 , WHITE);
    }
    // Draw Ghosts
    for (int i = 0; i < 4; i++) {
         DrawTexture(ghost , ghosts[i].x* TILE_SIZE + TILE_SIZE / 2 - 20 , ghosts[i].y* TILE_SIZE + TILE_SIZE / 2 - 20 , WHITE);
         
    }
    //following ghost
        DrawTexture(followingghost , ghosts[4].x *TILE_SIZE+ TILE_SIZE/2 - 20 , ghosts[4].y * TILE_SIZE + TILE_SIZE /2 - 20 , WHITE);
    // Draw Score
    DrawText(TextFormat("Score: %d", pacman.score), 10, 10, 20, WHITE);
    // Draw health
    for(int i =0 ; i < health ; i++)
    DrawTexture(heart, SCREEN_WIDTH/2 + (i*25), 5, RED);
    if (caneatghosts){
        DrawTexture (cherryT , 400 , 0 , WHITE);
        DrawText(TextFormat("Remaining : %d" , cherry.timer/(15 * 5)) , 435 , 10 , 20  , WHITE);
    }
    if (peper.active){
        DrawTexture (peperT , 400 , 0 , WHITE);
        DrawText(TextFormat("Remaining : %d" , peper.timer/(15 * 5)) , 435 , 10 , 20  , WHITE);        
    }

    EndDrawing();
}
