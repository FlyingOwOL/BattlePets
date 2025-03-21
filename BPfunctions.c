/**
 * This file contains the functions responsible for the flow of the game
 */
    
#include <stdio.h>
#include "BPheaders.h"
#include "startBattle/BPassistfunctions.c"
#include "startCompetdium/BPassistfunctions.c"
#include "viewStatistics/BPassistfunctions.c"
#include "BPdesigns.c"

/**
 * This function is responsible for the main gameplay of the program
 * @param struct Player player[] - the array of players
 * @param int* dCurrentPlayers - the address to the number of current players
 * @return void
 */  
void 
startBattle(struct BattlePet pet[], 
            struct Player player[],
            struct Results* matchResults, // Change to pointer for modification
            int* dCurrentPlayers, 
            int dCurrentPets) 
{
    int dChoice, dPrevChoice = -1, isDone = 0;
    int dFirst, dSecond;
    struct Player player1, player2;
    char cWinner[50];
    do {
        if (isDone == 0) {
            printf("Player 1\n");
            displayChoices(player, dCurrentPlayers);
            scanf("%d", &dChoice);
            dFirst = dChoice - 2;
        }

        switch (dChoice) {
            case 1:
            if (*dCurrentPlayers == MAX_PLAYERS) {
                printf("Maximum number of players reached\n");
            } else {
                newPlayer(player, dCurrentPlayers);
            }
            break;

            case 0:
            printf("Returning to main menu\n");
            break; 

            default:
                if (dChoice >= 2 && dChoice <= *dCurrentPlayers + 1 && isDone == 0) {
                    selectPlayer(pet, player, &player1, dChoice - 2, &isDone, dCurrentPets);
                    dPrevChoice = dChoice - 2;
                } else if (isDone == 0) {
                    printf("Invalid input\n");
                }

                if (isDone) {  
                    printf("Player 2\n");
                    displayChoices(player, dCurrentPlayers);
                    scanf("%d", &dChoice);
                    dSecond = dChoice - 2;
                    if (dChoice >= 2 && dChoice <= *dCurrentPlayers + 1 && dChoice != dPrevChoice) {
                        selectPlayer(pet, player, &player2, dChoice - 2, &isDone, dCurrentPets);
                    } else {
                        printf("Invalid choice\n");
                    }
                }
            break;
        }
    } while (isDone != 2 && dChoice != 0);

    if (isDone == 2) {
        *matchResults = computeBattle(player2, player1);
        printf("%s (player1) vs %s (player2)\n\n", player1.name, player2.name);
        printf("Battlepets, Fight!\n");
        displayMatch(&player2, &player1);
        printf("Match Results\n");
        displayResult(*matchResults);
        returnWinner (*matchResults, &player1, &player2, cWinner);
        printf("%s\n", cWinner);
        player[dFirst] = player1;
        player[dSecond] = player2;
    }
}


/**
 * This function is responsibe for the manipulation of the battlepets
 * @param struct BattlePet pet[] - the array of battlepets
 * @param int* dCurrentPets - the address to the number of current pets
 * @return void
 */
void 
startComPetDium (struct BattlePet pet[], int* dCurrentPets)
{
    int dChoice;
    do{
        printf("current pets: %d\n", *dCurrentPets); //debug line////////////////////////////////////
        printf ("%s%s%s%s%s%sYour choice: ", 
        "[1] View Battle Pet/s\n",
        "[2] Add BattlePet\n",
        "[3] Edit BattlePet\n",
        "[4] Delete BattlePet\n",
        "[5] Save Roster\n",
        "[0] Exit\n");
        scanf ("%d", &dChoice);
        switch (dChoice)
        {
        case 1:
            viewBattlepets (pet);
            break;
        case 2:
            addBattlepet (pet, dCurrentPets);
            break;
        case 0:
            printf ("returning to main menu\n");
            break;
        default:
            printf ("Invalid input\n");
            break;
        }
    }while (dChoice != 0);
    
}

/**
 * This function is responsible for showing the game statistics and previous matches.
 */
void viewStatistics ()
{
    printf ("Function in process\n");
}