/*
    This file contains the functions that are used for computations and to aid the BPfunctions
*/
#include <stdio.h>
#include "../BPheaders.h"

/**
 * This function displays the top pets used 
 * @param struct BattlePet localPets[] - struct array containing pets
 * @param int dCurrentPets - current total pets
 */
void 
displayTop5pets (struct BattlePet localPets[], int dCurrentPets)
{
    rearrangePets (localPets, dCurrentPets);
    int dChoice;
    printf ("Pick up to which rank you want to display (1 to %d): ", dCurrentPets);
    do{
        scanf ("%d", &dChoice);     
        if (dChoice <= 0){
            printf ("Invalid number\n");
        } else if (dChoice > dCurrentPets){
            printf ("Number out of bounds\n");
        } else{
            printf ("%sMatch Count:-%s%s%s", 
                    "----------",
                    "----------",
                    "----------",
                    "----------");
            int x, y;
            for (x = 0; x < localPets[0].matchCount; x++)
                printf ("-%d", x + 1);
            printf ("\n");
            for (x = 0; x < dChoice; x++){
                printf ("[%2d] %36s (%d matches)", x + 1, localPets[x].name, localPets[x].matchCount);
                for (y = 0; y < localPets[x].matchCount; y++)
                    printf ("-*");
                printf ("\n");
            }            
        }
    }while (dChoice <= 0 || dChoice > dCurrentPets);
    printf ("\n");
}

/**
 * This function rearranges the pets from highest matchcount to lowest
 * @param struct BattlePet localPets[] - contains the array of pets
 * @param int dCurrentPets - is the total pets ingame
 */
void 
rearrangePets (struct BattlePet localPets[], int dCurrentPets)
{
    struct BattlePet holder;
    int x, y;
    for (y = 0; y < dCurrentPets - 1; y++){
        for (x = 0; x < dCurrentPets - 1; x++){
            if (localPets[x + 1].matchCount > localPets[x].matchCount){
                holder = localPets[x];
                localPets[x] = localPets[x + 1];
                localPets[x + 1] = holder;
            } else if (localPets[x + 1].matchCount == localPets[x].matchCount &&
                       localPets[x + 1].name[0] < localPets[x].name[0]){
                holder = localPets[x];
                localPets[x] = localPets[x + 1];
                localPets[x + 1] = holder;
            }
        }        
    }
}

/**
 * This function displays the top players
 * @param struct Player localPlayers[] - array of player structs 
 * @param int dCurrentPlayers - current total players
 */
void 
displayTop5players(struct Player localPlayers[], int dCurrentPlayers)
{
    rearrangePlayers (localPlayers, dCurrentPlayers);
    int dChoice;
    printf ("Pick up to which rank you want to display (1 to %d): ", dCurrentPlayers);
    do{
        scanf ("%d", &dChoice);     
        if (dChoice <= 0){
            printf ("Invalid number\n");
        } else if (dChoice > dCurrentPlayers){
            printf ("Number out of bounds\n");
        } else{
            int x;
            for (x = 0; x < dChoice; x++){
                printf ("[%2d] %s (W: %2d, L: %2d, D: %2d)\n", x + 1, 
                localPlayers[x].name, 
                localPlayers[x].wins, 
                localPlayers[x].loss,
                localPlayers[x].draws);
            }       
        }
    }while (dChoice <= 0 || dChoice > dCurrentPlayers);
    printf("\n");
}

/**
 * This function rearranges the pets from highest matchcount to lowest
 * @param struct Player localPlayers[] - contains the array of players
 * @param int dCurrentPlayers - is the total players ingame
 */
void 
rearrangePlayers (struct Player localPlayers[], int dCurrentPlayers)
{
    struct Player holder;
    int x, y;
    for (y = 0; y < dCurrentPlayers; y++){
        for (x = 0; x < dCurrentPlayers - 1; x++){
            if (localPlayers[x + 1].wins > localPlayers[x].wins){ 
                holder = localPlayers[x];
                localPlayers[x] = localPlayers[x + 1];
                localPlayers[x + 1] = holder;
            } else if (localPlayers[x + 1].wins == localPlayers[x].wins &&
                       localPlayers[x + 1].loss < localPlayers[x].loss){
                holder = localPlayers[x];
                localPlayers[x] = localPlayers[x + 1];
                localPlayers[x + 1] = holder;
            } else if (localPlayers[x + 1].loss == localPlayers[x].loss &&
                       localPlayers[x + 1].draws < localPlayers[x].draws){
                holder = localPlayers[x];
                localPlayers[x] = localPlayers[x + 1];
                localPlayers[x + 1] = holder;
            } else if (localPlayers[x + 1].draws == localPlayers[x].draws &&
                       localPlayers[x + 1].name[0] < localPlayers[x].name[0]){
                holder = localPlayers[x];
                localPlayers[x] = localPlayers[x + 1];
                localPlayers[x + 1] = holder;                
            }
        }
    }
}