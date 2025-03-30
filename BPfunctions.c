/**
* Description : This file contains the primary functions responsible for the flow of the game
*
* Author/s : Sy, Jason Mark Lester B. 
*            Enerio, Gabrielle G.      
* Section : S19B
* Last Modified : March 31, 2025
*/
    
#include <stdio.h>
#include "BPheaders.h"
#include "startBattle/BPassistfunctions.c"
#include "startCompetdium/BPmainfunctions.c"
#include "viewStatistics/BPassistfunctions.c"

/**
 * This function is responsible for the main gameplay of the program
 * @param struct BattlePet pet[] - the array of battlepets
 * @param struct Player player[] - the array of players
 * @param struct Results* matchResults - the address to the match results
 * @param int* dCurrentPlayers - the address to the number of current players
 * @param int dCurrentPets - the number of current pets
 * @return void
 */  
void 
startBattle(struct BattlePet pet[], 
            struct Player player[],
            struct Results* matchResults, // change to pointer for modification
            int* dCurrentPlayers, 
            int dCurrentPets) 
{
    int dChoice, dPrevChoice = -1, isDone = 0;
    int dFirst, dSecond;
    struct Player player1, player2;
    string sWinner; // stores winner name

    do 
    { // loop until both players are selected or user chooses to exit
        if (isDone == 0) {
            printf("Player 1\n");
            displayChoices(player, dCurrentPlayers); // display player choices
            scanf("%d", &dChoice);
            dFirst = dChoice - 2; // adjust for array index
        }

        switch (dChoice) {
            case 1: // new player
                if (*dCurrentPlayers == MAX_PLAYERS) { // exit if max players reached
                    printf("Maximum number of players reached\n");
                } else {
                    newPlayer(player, dCurrentPlayers); // add new player
                }
                break;

            case 0: // exit menu
                printf("Returning to main menu\n");
                break; 

            default: // select existing player
                if (dChoice >= 2 && dChoice <= *dCurrentPlayers + 1 && isDone == 0) {
                    selectPlayer(pet, player, &player1, dChoice - 2, &isDone, dCurrentPets); // select player 1
                    dPrevChoice = dChoice - 2; // store previous choice
                } else if (isDone == 0) {
                    printf("Invalid input\n");
                }

                if (isDone) {  
                    printf("Player 2\n");
                    displayChoices(player, dCurrentPlayers); // display player choices for player 2
                    scanf("%d", &dChoice);
                    dSecond = dChoice - 2; // adjust for array index
                    if (dChoice >= 2 && dChoice <= *dCurrentPlayers + 1 && dChoice != dPrevChoice) {
                        selectPlayer(pet, player, &player2, dChoice - 2, &isDone, dCurrentPets); // select player 2
                    } else {
                        printf("Invalid choice\n");
                    }
                }
            break;
        }
    } while (isDone != 2 && dChoice != 0); 

    if (isDone == 2) 
    { // check if both players are selected
        *matchResults = computeBattle(player2, player1); // compute match results
        printf("%s (player1) vs %s (player2)\n\n", player1.name, player2.name); 
        printf("Battlepets, Fight!\n");
        displayMatch(&player2, &player1); // display match details
        printf("Match Results\n");
        displayResult(*matchResults); // display match results
        returnWinner (*matchResults, &player1, &player2, sWinner); // determine winner
        printf("%s\n", sWinner);

        // update player statistics
        player[dFirst] = player1;
        player[dSecond] = player2;
        updatePetscount (pet, player1, dCurrentPets); //check player1 roster
        updatePetscount (pet, player2, dCurrentPets); //check player2 roster

        // save match results
        updateCompetdiumTxt (pet, dCurrentPets);
        updatePlayerTxt (player, *dCurrentPlayers);

        // create match history
        createMatchHistory (player1, player2, *matchResults);
    }
}


/**
 * This function is responsible for the manipulation of the battlepets
 * @param struct BattlePet pet[] - the array of battlepets
 * @param struct Player player[] - the array of players
 * @param int* dCurrentPets - the address to the number of current pets
 * @param int* dCurrentPlayers - the address to the number of current players
 * @return void
 */
void 
startComPetDium (struct BattlePet pet[], struct Player player[], int* dCurrentPets, int* dCurrentPlayers)
{
    int dChoice;
    do
    { // loop until user chooses to exit and chooses a valid option
        printf(" total pets: %d\n", *dCurrentPets); ///// remove when patapos n
        printf ("%s%s%s%s%s%s%sYour choice: ", 
        "[1] View Battle Pet/s\n",
        "[2] Add BattlePet\n",
        "[3] Edit BattlePet\n",
        "[4] Delete BattlePet\n",
        "[5] Save Roster\n",
        "[6] Pet Expansion\n",
        "[0] Exit\n");
        scanf ("%d", &dChoice);
        switch (dChoice)
        {
        case 1:
            viewBattlepets (pet, *dCurrentPets); // view all available battlepets
            break;
        case 2:
            addBattlepet (pet, dCurrentPets); // add new battlepet
            break;
        case 3:
            editBattlepet (pet, dCurrentPets); // edit existing battlepet
            break;
        case 4:
            deleteBattlepet(pet, dCurrentPets); // delete existing battlepet
            break;
        case 5:
            saveRoster (pet, player, dCurrentPlayers, *dCurrentPets); // save or edit player roster
            break;
        case 6:
            addPetsFromExpansion(pet, dCurrentPets); // add pets from petExpansion.txt
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
 * @param struct Player player[] - the array of players
 * @param struct BattlePet pet[] - the array of battlepets
 * @param int dCurrentPlayers - the number of current players
 * @param int dCurrentPets - the number of current pets
 * @return void
 */
void viewStatistics (struct Player player[], struct BattlePet pet[], int dCurrentPlayers, int dCurrentPets)
{
    struct Player localPlayers[MAX_PLAYERS];
    struct BattlePet localPets[MAX_BATTLEPETS];

    initializePlayers (localPlayers); //set values to 0 or to null
    initializePets (localPets);

    int x;
    for (x = 0; x < dCurrentPlayers; x++)
        localPlayers[x] = player[x];
    for (x = 0; x < dCurrentPets; x++)
        localPets[x] = pet[x];        //copy values 

    do
    { // loop until user chooses to exit and chooses a valid option
       printf ("%s\n%s\n%s\n%s",
        "[1] view top 5 players",
        "[2] view top 5 pets",
        "[0] exit",
        "Your choice:");
        scanf ("%d", &x);
        switch (x){
            case 1:
                displayTop5players(localPlayers, dCurrentPlayers); // display top 5 players
                break;
            case 2:
                displayTop5pets (localPets, dCurrentPets); // display top 5 pets
                break;
            case 0:
                printf ("Returning to Menu\n");
                break;
            default:
                printf ("Out or range choice\n");
                break;
        }
    }while (x != 0);
}