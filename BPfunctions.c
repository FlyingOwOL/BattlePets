/**
 * This file contains the functions responsible for the flow of the game
 */
    
#include <stdio.h>
#include "BPheaders.h"
#include "BPassistfunctions.c"
#include "BPdesigns.c"

/**
 * 
 */ 
void startBattle (){
    printf ("Function in process\n");
}

/**
 * 
 */
void startComPetDium (){
    printf ("Function in process\n");
}

/**
 * 
 */
void viewStatistics (){
    printf ("Function in process\n");
}

/** 
 * This function initializes the values of the struct player array to default values
 * @param struct Player player[] - the array of players
 * @return void
 */
void initializePlayers (struct Player player[]){
    int x, y;
    for (x = 0; x < MAX_PLAYERS; x++){
        player[x].name[0] = '\0';
        player[x].savedPassword[0] = '\0';
        player[x].wins = 0;
        player[x].loss = 0;
        player[x].draws = 0;
        for (y = 0; y < MAX_ROSTER; y++){
            player[x].pet[y].name[0] = '\0';
            player[x].pet[y].affinity[0] = '\0';
            player[x].pet[y].description[0] = '\0';
            player[x].pet[y].matchCount = 0;
        }
    }
}

/**
 * This function initializes the values of the struct pet array to default values
 * @param struct BattlePet pet[] - the array of pets
 * @return void
 */
void initializePets (struct BattlePet pet[]){
    int x;
    for (x = 0; x < MAX_ROSTER; x++){
        pet[x].name[0] = '\0';
        pet[x].affinity[0] = '\0';
        pet[x].description[0] = '\0';
        pet[x].matchCount = 0;
    }
}