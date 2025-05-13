#ifndef records_h
#define records_h
// players that recorded struct
typedef struct recorder{
    char name[20];
    int scores [10000];
    int index ;
    int best ; 
    char date[1000][20];
    char time [1000][20];
    struct recorder *next;
}recorder ;
// link list of recorders 
extern recorder *list ;
//functions
void writeDateToFile(FILE *) ;
void records(int scrollOffset);

#endif