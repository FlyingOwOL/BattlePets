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
int 
getComPetDium (struct BattlePet pet[])
{
    int dCurrentPets = 0;
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
            dCurrentPets++;
        }
        fclose (file);
    }
    return dCurrentPets;
}

/**
 * THis function gets the players from the file Players.txt
 * @param struct Player player[] - the array of players
 * @return void
 */
int 
getPlayers (struct Player player[])
{
    int dCurrentPlayers = 0;
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
            dCurrentPlayers++;
        }
        fclose (file);
    }
    return dCurrentPlayers;
}

/** 
 * This function initializes the values of the struct player array to default values
 * @param struct Player player[] - the array of players
 * @return void
 */
void 
initializePlayers (struct Player player[])
{
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
void 
initializePets (struct BattlePet pet[])
{
    int x;
    for (x = 0; x < MAX_ROSTER; x++){
        pet[x].name[0] = '\0';
        pet[x].affinity[0] = '\0';
        pet[x].description[0] = '\0';
        pet[x].matchCount = 0;
    }
}

/**
 * This functions displays the choices for the player to choose from
 * @param struct Player player[] - the array of players
 * @param int* dCurrentPlayers - the address to the number of current players
 * @return void
 */ 
void 
displayChoices (struct Player player[], 
                int* dCurrentPlayers)
{
    printf("[1] <New Player>\n");
        int x;
        for (x = 0; x < *dCurrentPlayers; x++){
            printf("[%d] %s\n", x + 2, player[x].name);
        }
        printf("[0] Exit\nYour choice: ");
}

/**
 * This function creates a new player and saves it to the player array
 * @param struct Player player[] - the array of players
 * @param int* dCurrentPlayers - the address to the number of current players
 * @return void
 */
void newPlayer (struct Player player[],
                int* dCurrentPlayers)
{
    printf ("Enter your name: ");
    scanf ("%s", player[*dCurrentPlayers].name);
    printf ("Create your password: ");
    scanf ("%s", player[*dCurrentPlayers].savedPassword);
    (*dCurrentPlayers)++;
}

/**
 * 
 */
void 
selectPets (struct BattlePet pet[],
            struct Player currentPlayer, 
            int dCurrentPets)
{
    struct BattlePet roster[MAX_ROSTER];
    int y = 0, 
        x = 0;
    int dChoice;
    while(y < MAX_ROSTER){
        printf ("Match Roster\n");                      //shows the current location of the pets
        for (x = 0; x < MAX_ROSTER; x++){
            if (x % 3 == 0){
                printf ("\n");
            }            
            strcpy(roster[x].name, "?");
            printf (" <%s>", roster[x].name);
        }
        printf ("\n");
        printf ("ComPetDium\n");
        while (pet[x].name[0] != '\0'){                 //should ONLY print pets in competdium.txt
            printf ("%d. %s\n", x + 1, pet[x].name);
            x++;
        }
        printf ("Your choice: ");
        scanf ("%d", &dChoice);
        if (dChoice == 0){
            roster[y] = pet[dChoice - 1];
            y++;
        } else {
            printf ("Invalid input\n");
        }
        
        
    }
    currentPlayer.pet[0] = roster[0];
}

/**
 * This function selects a player from struct player array and sets it as the current player if the password is correct
 * @param struct Player player[] - the array of players
 * @param struct Player currentPlayer - the current player
 * @param int* dChoice - the choice of the player
 * @return void
 */
void 
selectPlayer (struct BattlePet pet[], 
              struct Player player[],
              struct Player currentPlayer, 
              int dChoice, 
              int* isDone, 
              int dCurrentPets)
{
    string password;
    printf ("Hello! %s\n", player[dChoice].name);
    printf ("Your password: %s\n", player[dChoice].savedPassword);
    printf ("Enter your password: ");
    scanf ("%s", password);
    if (strcmp (password, player[dChoice].savedPassword) == 0){
        int dChoice;
        printf ("Welcome %s\n", player[dChoice].name);

        do{
            printf ("Player %d roster\n", *isDone + 1);
            printf("%s\n%s\n%s",
            "[1] Load saved roster",
            "[2] Create roster for this match",
            "Your choice: ");
            scanf ("%d", &dChoice);
            if (dChoice == 1){  
                printf ("Loaded saved_roster/%s.txt\n", player[dChoice].name);
                currentPlayer = player[dChoice]; 
            } else if (dChoice == 2){
                selectPets (pet, currentPlayer, dCurrentPets);
            } else{
                printf ("Invalid input\n");
            }
        }while(dChoice != 1 && dChoice != 2);
        (*isDone)++;
    } else{
        printf ("Get out\n");
    }
}

/**
 * This function is used to view the pets saved in the battlepets array
 * @param struct BattlePet pet[] - the array of pets
 * @return void
 */
void 
viewBattlepets (struct BattlePet pet[])
{
    int x;
    for (x = 0; x < MAX_BATTLEPETS; x++){   //loop through the array of battlepets
        if (pet[x].name[0] != '\0'){        //only print if the name is not empty
            printf ("%d. %s{%s} - used %d times\n%s\n\n",
            x + 1,
            pet[x].name,
            pet[x].affinity,
            pet[x].matchCount,
            pet[x].description);
        }
    }
}