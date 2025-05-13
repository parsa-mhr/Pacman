#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "raylib.h"
#include "game.h"
#include "menu.h"
#include "records.h"

int main() {
    srand(time(NULL));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pacman_Final");
    InitAudioDevice();
    SetTargetFPS(20);
        loadtexture();
        loadsound();
        
        usernameinput();
    while(!WindowShouldClose()){

        int menust=1;

while(menust){
    if(WindowShouldClose())
        exit(2);

    BeginDrawing();
    ClearBackground(BLACK);
    button();

    if (IsKeyPressed(KEY_DOWN)){
        option++;
    }
    if (IsKeyPressed(KEY_UP)){
        option--;
    }

    if(option == 0){
        if(IsKeyPressed(KEY_ENTER)){
            gameRunning = true;
            health = 3 ;
            menust = 0;
        }
    }

    if (option == 1){
        if(IsKeyPressed(KEY_ENTER)){
            recordsRunning = true; 
            menust = 0;
            
        }
    }

    if (option == 2){
        if(IsKeyPressed(KEY_ENTER)){
            menust = 0;
            exit(1);
        }
    }

    option = (option > 2) ? 0 : (option < 0) ? 2 : option;

    EndDrawing();
}
int scrollOffset = 0; 
while(recordsRunning){
    if(WindowShouldClose()){
    exit(2);
    }
    if (IsKeyDown(KEY_DOWN)) scrollOffset -= 10; 
    if (IsKeyDown(KEY_UP)) scrollOffset += 10; 
    records(scrollOffset); 
    }

    recordsRunning = false;
    int Map[MAP_HEIGHT][MAP_WIDTH] ;
    for(int i = 0 ;  i < MAP_HEIGHT ; i++){
        for(int j =0 ; j < MAP_WIDTH ; j++)
        Map[i][j] = gameMap[i][j];
    }
    InitGame(Map);

    while (gameRunning ) {
            if(WindowShouldClose())
            exit(2);
            // house by house program
            pacman.dx = 0 ;
            pacman.dy = 0 ;
        if (IsKeyDown(KEY_UP)) {
            pacman.dx = 0;
            pacman.dy = -1;
        } else if (IsKeyDown(KEY_DOWN)) {
            pacman.dx = 0;
            pacman.dy = 1;
        } else if (IsKeyDown(KEY_LEFT)) {
            pacman.dx = -1;
            pacman.dy = 0;
        } else if (IsKeyDown(KEY_RIGHT)) {
            pacman.dx = 1;
            pacman.dy = 0;
        }

        UpdatePacman(Map);
        UpdateGhosts();


        DrawGame(Map);
        animcounter++;
        if (animcounter>10)
        animcounter = 0;
        
    }
            FILE *fp = fopen(pacmanlog, "a");
            writeDateToFile(fp);
            fprintf(fp , "%s" , name);
        fprintf(fp , " %d\n" , pacman.score);
        fclose(fp);
            if(WindowShouldClose())
    exit(2);
    while(!replay ){
            if(WindowShouldClose())
    exit(2);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(TextFormat("GAME OVER!") , SCREEN_WIDTH/2 - 220, SCREEN_HEIGHT/2 - 70 , 70, RED);
    DrawText(TextFormat("Score: %d", pacman.score), SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 , 40, WHITE);
    DrawText(TextFormat("PLAY AGAIN"), SCREEN_WIDTH/2 - 180, SCREEN_HEIGHT/2 + 60 , 55, GREEN);
    if(IsKeyDown(KEY_ENTER))
    replay=1;
    
    EndDrawing();
    }
        
 }  
 CloseAudioDevice(); 
 CloseWindow();

    return 0;
}
