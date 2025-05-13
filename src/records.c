#include<stdio.h>
#include <raylib.h>
#include<conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include"records.h"

void writeDateToFile(FILE *fp) {

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char dateStr[100];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %H:%M:%S", t);

    fprintf(fp, "%s ", dateStr);
}
//
void recordplayer(recorder **list, char name[20], int score, char date[20], char time[20]) {
    recorder *head = *list;
    recorder *prev = NULL;

    if (*list == NULL) {
        *list = (recorder *)malloc(sizeof(recorder));
        if (*list == NULL) {
            printf("Unable to allocate memory for the list.\n");
            return;
        }
        head = *list;
        strncpy(head->name, name, sizeof(head->name) - 1);
        head->name[sizeof(head->name) - 1] = '\0';
        head->index = 0;
        head->best = 0;
        head->scores[head->index] = score;
        strncpy(head->time[head->index], time, sizeof(head->time[head->index]) - 1);
        head->time[head->index][sizeof(head->time[head->index]) - 1] = '\0';
        strncpy(head->date[head->index], date, sizeof(head->date[head->index]) - 1);
        head->date[head->index][sizeof(head->date[head->index]) - 1] = '\0';
        head->index++;
        if (score > head->best)
            head->best = score;
        head->next = NULL;
        return;
    }

    while (head != NULL && strcmp(head->name, name) != 0) {
        prev = head;
        head = head->next;
    }

    if (head != NULL && strcmp(head->name, name) == 0) {
        strncpy(head->time[head->index], time, sizeof(head->time[head->index]) - 1);
        head->time[head->index][sizeof(head->time[head->index]) - 1] = '\0';
        strncpy(head->date[head->index], date, sizeof(head->date[head->index]) - 1);
        head->date[head->index][sizeof(head->date[head->index]) - 1] = '\0';
        head->scores[head->index++] = score;
        if (head->best < score)
            head->best = score;
    } else {
        head = (recorder *)malloc(sizeof(recorder));
        if (head == NULL) {
            printf("Unable to allocate memory for the new node.\n");
            return;
        }
        strncpy(head->name, name, sizeof(head->name) - 1);
        head->name[sizeof(head->name) - 1] = '\0';
        head->index = 0;
        head->best = 0;
        head->scores[head->index] = score;
        strncpy(head->time[head->index], time, sizeof(head->time[head->index]) - 1);
        head->time[head->index][sizeof(head->time[head->index]) - 1] = '\0';
        strncpy(head->date[head->index], date, sizeof(head->date[head->index]) - 1);
        head->date[head->index][sizeof(head->date[head->index]) - 1] = '\0';
        head->index++;
        if (score > head->best)
            head->best = score;
        head->next = NULL;
        prev->next = head;
    }
}
//scrollOffset = global
void records(int scrollOffset) {
    //printf("2.records function called\n");//debug


    int max = 0;
    char time[20];
    char date[20];
    char name[20];
    char bestplayername[20] = "";
    char buff[100];
    char *token;
    recorder *list = NULL;
    recorder *head = NULL;

    FILE *fp = fopen(pacmanlog , "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return;
    }

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        token = strtok(buff, " \n");
        strcpy(date, token);
        token = strtok(NULL, " \n");
        strcpy(time, token);
        token = strtok(NULL, " \n");
        strcpy(name, token);
        token = strtok(NULL, " \n");
        int score = atoi(token);
        //printf("3.recordplayer function called\n");//debug
        recordplayer(&list, name, score, date, time);
        //printf("4.recordplayer funcition finished\n");//debug
    }
    fclose(fp);

    ClearBackground(BLACK);
BeginScissorMode(0, 50, SCREEN_WIDTH, SCREEN_HEIGHT);

head = list;
int prevy = 50 + scrollOffset;

while (head != NULL) {
    int yOffset = prevy; 
    if (yOffset + 60 + head->index * 20 > 50 && yOffset < SCREEN_HEIGHT + 50) { 
        DrawText(TextFormat("%s :", head->name), 50, yOffset, 30, YELLOW);
        DrawText(TextFormat("Best: %d", head->best), 50, yOffset + 30, 20, RED);
        for (int j = 0; j < head->index; j++) {
            DrawText(TextFormat("%d: %s %s %d", j + 1, head->date[j], head->time[j], head->scores[j]), 50, yOffset + 60 + j * 20, 15, WHITE);
        }
    }
    prevy = yOffset + 60 + head->index * 20;
    head = head->next;
}

EndScissorMode();

    // Find the best player
    head = list;
    while (head != NULL) {
        if (head->best > max) {
            max = head->best;
            strcpy(bestplayername, head->name);
        }
        head = head->next;
    }


    DrawText(TextFormat("BEST Player: %s", bestplayername), SCREEN_WIDTH / 2 - 200, 10, 40, DARKGREEN);
    DrawText(TextFormat("Best Record: %d", max), SCREEN_WIDTH / 2 - 160, 50, 40, DARKGREEN);
    EndDrawing();
}
