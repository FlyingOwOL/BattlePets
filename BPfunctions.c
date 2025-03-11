/**
 * This file contains the functions responsible for the flow of the game
 */
    
#include <stdio.h>
#include "BPheaders.h"
#include "BPassistfunctions.c"
#include "BPdesigns.c"

/**
 * This function is responsible for the main gameplay of the program
 * @param struct Player player[] - the array of players
 * @param int* dCurrentPlayers - the address to the number of current players
 * @return void
 */ 
void startBattle (struct Player player[],int* dCurrentPlayers){
    int dChoice;
    int isFull = 0;
    int isDone = 0;
    struct Player player1;
    struct Player player2;
    do{
        printf("[1] <New Player>\n");
        int x;
        for (x = 0; x < *dCurrentPlayers; x++){
            printf("[%d] %s\n", x + 2, player[x].name);
        }
        printf("[0] Exit\nYour choice: ");
        scanf ("%d", &dChoice);
        switch (dChoice)
        {
            case 1:
                if (*dCurrentPlayers == MAX_PLAYERS){
                    printf ("Maximum number of players reached\n");
                    isFull = 1;
                } else{
                    newPlayer (player, dCurrentPlayers);
                }               
                break;
            case 0:
                printf ("returning to main menu\n");
                break;
            default:
                if (dChoice > 1 && dChoice <= *dCurrentPlayers + 1 && isDone == 0){ //selects for player 1
                    selectPlayer (player, player1, dChoice);
                    isDone = 1;
                } else{
                    printf ("Invalid input\n");
                }
                if (isDone){                                                       //selects for player 2
                    scanf("%d", &dChoice);
                    if (dChoice > 1 && dChoice <= *dCurrentPlayers + 1)
                        selectPlayer (player, player2, dChoice);
                    else
                        printf ("Invalid input\n");
                }          
                break;
        }
    }while(dChoice != 0 && isFull == 0);
    //battle (player, dCurrentPlayers, dChoice - 2);   
}        

/**
 * This function is responsibe for the manipulation of the battlepets
 * @param struct BattlePet pet[] - the array of battlepets
 * @param int* dCurrentPets - the address to the number of current pets
 * @return void
 */
void startComPetDium (struct BattlePet pet[], int* dCurrentPets){
    int dChoice;
    do{
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
            viewBattlepets (pet, dCurrentPets);
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
 * 
 */
void viewStatistics (){
    printf ("Function in process\n");
}