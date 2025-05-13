#include "raylib.h"
#include <stdio.h>
#include<conio.h>
#include<stdbool.h>
#include "game.h"
#include "menu.h"


 char name[20] = "\0";
void usernameinput() {
    int letterCount = 0;

    Rectangle textBox = { SCREEN_WIDTH / 2.0f - 225, 180, 450, 50 };
    while (!WindowShouldClose()) { 
        if(IsKeyDown(KEY_ENTER))
        break;
        int key = GetCharPressed();

        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letterCount < 19)) {
                name[letterCount] = (char)key;
                name[letterCount + 1] = '\0'; 
                letterCount++;
            }

            key = GetCharPressed(); 
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(TextFormat("Enter Player Name"), SCREEN_WIDTH / 2.0f - 225, 150 , 30 , DARKPURPLE);
        DrawRectangleRec(textBox, LIGHTGRAY);
        DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
        DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 19), 315, 250, 20, DARKGRAY);

        EndDrawing();
    }
    WaitTime(0.03);
}

    

void button(){
    if (option == 0){
        DrawText(TextFormat("PLAY") , SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 , 30 , GREEN);
    }else 
        DrawText(TextFormat("PLAY") , SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 , 30 , WHITE);
    if(option == 1){    
        DrawText(TextFormat("RECORDS") , SCREEN_WIDTH/2 , SCREEN_HEIGHT/2+45 , 30 , GREEN);
    }else 
        DrawText(TextFormat("RECORDS") , SCREEN_WIDTH/2 , SCREEN_HEIGHT/2+45 , 30 , WHITE);
    if(option == 2){
        DrawText(TextFormat("EXIT") , SCREEN_WIDTH/2 , SCREEN_HEIGHT/2+90 , 30 , GREEN);
        }else 
        DrawText(TextFormat("EXIT") , SCREEN_WIDTH/2 , SCREEN_HEIGHT/2+90 , 30 , WHITE);


}
