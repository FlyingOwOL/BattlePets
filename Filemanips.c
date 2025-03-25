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
 * This function gets the player name and returns it as a .txt file format
 * @param string input - contains the name of the player
 * @param string prefix - example "saved_roster/" or "match_"
 * @param string output - returns "prefix""name".txt
 * @return void 
 */
void 
getTxtname(string input, 
           string150 output,
           char* prefix)
{
    string150 holder;
    strcpy (holder, prefix);
    strcat (holder, input);
    strcat (holder, ".txt");
    strcpy (output, holder);
}

/**
 * This updates the Wins Lost Draws of all players in players.txt
 * @param struct Player players[] - array of playeers
 * @param int dCurrentPlayers - total number of current players 
 * @return void
 */
void 
updatePlayerTxt (struct Player players[], 
                 int dCurrentPlayers)
{
    FILE *file = fopen ("players.txt", "w");
    if (file == NULL){
        printf ("File not found\n");
    } else{
        int x;
        for (x = 0; x < dCurrentPlayers; x++){
            fprintf (file, "%s\n", players[x].name);
            fprintf (file, "%s\n", players[x].savedPassword);
            fprintf (file, "%d\n%d\n%d\n", players[x].wins, players[x].loss, players[x].draws);
            fprintf (file, "\n");
        }
        fclose (file);
    }
}

/**
 * This function overwrites saved info in competdium.txt to update match count
 * @param struct BattlePet pets[] - array of current pets in struct
 * @param int dCurrentPets - is the total amount of current pets
 * @return void
 */
void 
updateCompetdiumTxt (struct BattlePet pets[], 
                     int dCurrentPets)
{
    FILE *file = fopen ("competdium.txt", "w");
    if (file == NULL){
        printf ("file not found\n");
    } else {
        int x;
        for (x = 0; x < dCurrentPets; x++){
            fprintf (file, "%s\n", pets[x].name);
            fprintf (file, "%s\n", pets[x].affinity);
            fprintf (file, "%s\n", pets[x].description);
            fprintf (file, "%d\n\n", pets[x].matchCount);
        }
        fclose (file);
    }
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