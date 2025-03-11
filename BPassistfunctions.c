/*
    This file contains the functions that are used for computations and to aid the BPfunctions
*/
#include <stdio.h>
#include "BPheaders.h"

/**
 * This function uploads the battlepets from the file ComPetDium.txt
 * @param struct BattlePet pet[] - the array of battlepets
 * @return void
 */
void getComPetDium (struct BattlePet pet[]){
    FILE *file = fopen ("ComPetDium.txt", "r");
    if (file == NULL){
        printf ("File not found\n");
    } else{
        int x = 0;
        while (fscanf (file, "%s", pet[x].name) != EOF){  //read name
            fscanf (file, "%s", pet[x].affinity);       //read affinity
            fscanf (file, " %[^\n]", pet[x].description); //read description
            fscanf (file, "%d", &pet[x].matchCount);    //read match count
            fgetc (file);                               //eat the new line
            x++;
        }
        fclose (file);
    }
}

/**
 * THis function gets the players from the file Players.txt
 * @param struct Player player[] - the array of players
 * @return void
 */
void getPlayers (struct Player player[], int *dCurrentPlayers){
    FILE *file = fopen ("Players.txt", "r");
    if (file == NULL){
        printf ("File not found\n");
    } else{
        int x = 0;
        while (fscanf (file, "%s", player[x].name) != EOF){  //read name
            fscanf (file, "%s", player[x].savedPassword);       //read password
            fscanf (file, "%d", &player[x].wins);    //read wins
            fscanf (file, "%d", &player[x].loss);    //read loss
            fscanf (file, "%d", &player[x].draws);    //read draws
            fgetc (file);                               //eat the new line
            x++;
            (*dCurrentPlayers)++;
        }
        fclose (file);
    }
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

/**
 * This function creates a new player and saves it to the player array
 * @param struct Player player[] - the array of players
 * @param int* dCurrentPlayers - the address to the number of current players
 * @return void
 */
void newPlayer (struct Player player[],int* dCurrentPlayers){
    printf ("Enter your name: ");
    scanf ("%s", player[*dCurrentPlayers].name);
    printf ("Create your password: ");
    scanf ("%s", player[*dCurrentPlayers].savedPassword);
    (*dCurrentPlayers)++;
}

/**
 * This function selects a player from struct player array and sets it as the current player if the password is correct
 * @param struct Player player[] - the array of players
 * @param struct Player currentPlayer - the current player
 * @param int* dChoice - the choice of the player
 * @return void
 */
void selectPlayer (struct Player player[],struct Player currentPlayer, int dChoice){
    string password;
    printf ("Enter your password: ");
    scanf ("%s", password);
    if (strcmp (password, currentPlayer.savedPassword) == 0){
        printf ("Welcome %s\n", currentPlayer.name);
        currentPlayer = player[dChoice];
    } else{
        printf ("Invalid password\n");
    }
}

/**
 * This function is used to view the pets saved in the battlepets array
 * @param struct BattlePet pet[] - the array of pets
 * @return void
 */
void viewBattlepets (struct BattlePet pet[], int* dCurrentPets){
    int x;
    for (x = 0; x < MAX_BATTLEPETS; x++){   //loop through the array of battlepets
        if (pet[x].name[0] != '\0'){        //only print if the name is not empty
            printf ("%d. %s{%s} - used %d times\n%s\n\n",
            x + 1,
            pet[x].name,
            pet[x].affinity,
            pet[x].matchCount,
            pet[x].description);

            *dCurrentPets = x;
        }
    }
}