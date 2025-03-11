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
 * This function is responsibe for the manipulation of the battlepets
 * @param struct BattlePet pet[] - the array of battlepets
 * @return void
 */
void startComPetDium (struct BattlePet pet[]){
    int dChoice;
    do{
        printf ("%s%s%s%s%s%sYour choice:", 
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