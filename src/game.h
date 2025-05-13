#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include <stdbool.h>

//game
#define SCREEN_WIDTH 1200 //800
#define SCREEN_HEIGHT 450 //600
#define TILE_SIZE 30 //40
#define MAP_WIDTH 40
#define MAP_HEIGHT 15

#define pacmanlog "C:/Users/YAHOO/Desktop/p/src/pacmanlog.txt"

extern int gameMap[MAP_HEIGHT][MAP_WIDTH] ;


// Player structure
typedef struct {
    int x, y;   
    float dx, dy;  
    int score;  
} Player;

// Ghost structure
typedef struct {
    int x, y;  
    int dx, dy; 
    bool active; 
} Ghost;
//Cherry Structure
typedef struct { //can eat ghost
    int x , y;
    bool active;
    int timer;
}Cherry;
// Apple Structure
typedef struct { // increase health 
    int x , y;
    bool active;
}Apple;
// Mushroom Struct
typedef struct { //decrease health
    int x , y;
    bool active;
}Mushroom;
// peper struct
typedef struct { //add speed
    int x , y;
    bool active;
    int timer;
}Peper;


//global vaialbles
//charecters
extern Player pacman;
extern Ghost ghosts[5];
// control instructions
extern int option ;
extern int replay ;
extern int animcounter;
extern int health ;
extern  int starcount ;  
extern bool gameRunning ;
extern bool recordsRunning;
extern bool caneatghosts ;
// textures
extern Texture pacr , pacl , pacu , pacd ; // right left up down
extern Texture pac2; // closed
extern Texture heart;
extern Texture ghost; 
extern Texture cherryT ;  
//color of pacman  
extern Color red ;
//sounds
extern Sound ghosteat;
extern Sound ClaimStar;
extern Sound GameOver;
//functions
void loadtexture();
void loadsound();
void DrawGame(int map[MAP_HEIGHT][MAP_WIDTH]);
void UpdatePacman(int map[MAP_HEIGHT][MAP_WIDTH]);
void UpdateGhosts();
void InitGame(int Map[MAP_HEIGHT][MAP_WIDTH]);


#endif