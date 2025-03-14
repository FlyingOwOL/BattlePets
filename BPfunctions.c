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
void startBattle (struct BattlePet pet[], struct Player player[],int* dCurrentPlayers, int dCurrentPets){
    int dChoice;
    int dPrevChoice;
    int isDone = 0;
    struct Player player1;
    struct Player player2;
    do{         //loop for player 1 and player 2 to select their accounts
        if (isDone == 0){
            printf("Player 1\n");
            displayChoices (player, dCurrentPlayers);
            scanf ("%d", &dChoice);
        }    
        switch (dChoice)
        {
            case 1:
                if (*dCurrentPlayers == MAX_PLAYERS){       //if *dCurrentPlayers is equal to the maximum number of players
                    printf ("Maximum number of players reached\n"); //stop the player from creating a new player
                } else{
                    newPlayer (player, dCurrentPlayers);
                }               
                break;
            case 0:
                printf ("returning to main menu\n");
                break;
            default:
                
                if (dChoice > 1 && 
                    dChoice <= *dCurrentPlayers + 1 && 
                    isDone == 0){ //selects for player 1
                    selectPlayer (pet, player, player1, dChoice - 2, &isDone, dCurrentPets);
                    dPrevChoice = dChoice;
                } else if (isDone == 0 && 
                          (dChoice < 1 || dChoice > *dCurrentPlayers + 1)){
                    printf ("Invalid input\n");
                }
                if (isDone){  
                    printf("Player 2\n");      
                    displayChoices (player, dCurrentPlayers);
                    scanf ("%d", &dChoice);                                                  
                    if (dChoice > 1 && //selects for player 2
                        dChoice <= *dCurrentPlayers + 1 && 
                        dChoice != dPrevChoice){  
                        selectPlayer (pet, player, player2, dChoice - 2, &isDone, dCurrentPets);
                    }else if (dChoice == dPrevChoice){  //player can't choose the same as player 1
                        printf ("Player already taken\n");
                    }else if (dChoice == 0){
                        printf ("returning to main menu\n");
                    }else{
                        printf ("Invalid input\n");
                    }        
                }
                break;
        }
    }while(dChoice != 0 && isDone != 2); //either the player chooses to quit during/after player 1 chooses or both players have been selected
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
            viewBattlepets (pet);
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