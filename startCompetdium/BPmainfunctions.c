/*
    This file contains the functions that are required for startComPetdium and to aid BPfunctions
*/
#include <stdio.h>
#include "../BPheaders.h"
#include "BPassistfunctions.c"

/**
 * This function is used to view the pets saved in the battlepets array
 * @param struct BattlePet pet[] - the array of pets
 * @param int dCurrentPets - total number of pets
 * @return void
 */
void 
viewBattlepets (struct BattlePet pet[], int dCurrentPets)
{
    int x;
    for (x = 0; x < dCurrentPets; x++){   //loop through the array of battlepets
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

/**
 * This function is used to add a pet with its details to competdium.txt
 * The user can choose to add one manually or add multiple from a file 
 * in the importpets folder
 * @param struct BattlePet pet[] - the array of battlepets
 * @param int* dCurrentPets - current total of battlepets
 */
void
addBattlepet (struct BattlePet pet[], int* dCurrentPets){
    int dChoice;

    do{
    printf("Add one manually or multiple from import_pets folder?\n");
    printf("[1] Add one manually \n");
    printf("[2] Add multiple from folder\n");
    printf("[0] Exit\n"); // add one or multiple?
    scanf (" %d", &dChoice);
    switch(dChoice)
        {
        case 1:
           addOnePet(pet, &dCurrentPets);
           break;
        case 2:
            addMultiplePets(pet, &dCurrentPets);
        case 0:
            printf("returning to competdium");
            break;
        default:
            printf("Invalid input. Please try again.");
            break;
        }
    } while (dChoice != 0);

}

/**
 * This function asks the user which BattlePet and what characteristic they want to modify
 * @param struct BattlePet pet[] - the array of pets
 * @param int dCurrentPets - current total of battlepets
 * @return void
 */
void
editBattlepet (struct BattlePet pet[], int* dCurrentPets){
    int dChoice, dEditChoice, dValid, dConfirmValid;
    char cConfirm;

    printf("\n EDIT BATTLEPET \n");
    viewBattlepets(pet, *dCurrentPets);
    printf("[0] Exit");

    do{
        printf("\nWhich BattlePet do you want to edit?\n");
        dValid = scanf(" %d", &dChoice);

        if (dValid && dChoice==0){
            printf("Exiting Edit BattlePet...");
        }
        else if (dValid && dChoice<=16 && dChoice>0){ // not allowed to edit initial battlepets
            dValid=0;
            printf("You are not allowed to edit the initial BattlePets. Please try again.");
        } 
        else if (dValid && dChoice>16 && dChoice<= *dCurrentPets){
            dValid=0;
            dConfirmValid=0;
            do // ask for confirmation
            {
            printf("Would you like to edit '%s'? [y/n] \n", pet[dChoice-1].name);
            scanf(" %c", &cConfirm);
            while (getchar() != '\n'); // clear buffer
                //check if user responded y or n
                switch(cConfirm){
                    case 'y':
                        printf("\n%s\n%s\n%s\n%s\n%s\n",
                            pet[dChoice-1].name,
                            "[1] Name",
                            "[2] Affinity",
                            "[3] Description",
                            "[0] Back");    
                        do{ //ask what to modify
                        printf("What do you want to modify?\n");
                        scanf(" %d", &dEditChoice);
                            if(dEditChoice>=1 && dEditChoice<=3){ 
                                switch(dEditChoice){
                                    case 1:
                                        dConfirmValid=editBPname(&pet[dChoice-1]);
                                        break;
                                    case 2:
                                        dConfirmValid=editBPaffinity(&pet[dChoice-1]);
                                        break;
                                    case 3:
                                        dConfirmValid=editBPdesc(&pet[dChoice-1]);
                                        break;
                                    case 0:
                                        printf("Returning to edit selection...\n");
                                        break;
                                    default:
                                        printf("Invalid response. Please try again.\n");
                                        break;
                                }
                                dValid=1;
                                if(dConfirmValid==1){ // check if edit was successful
                                    printf("BattlePet edit of '%s' is successful.\n", pet[dChoice-1].name);
                                    updateCompetdiumTxt(pet, *dCurrentPets);
                                } else{
                                    printf("BattlePet edit was unsuccessful.\n");
                                }

                            } else{
                                printf("Invalid response. Please try again.\n");
                            } 
                        } while(dEditChoice!=0);
                        break;

                    case 'n':
                        dConfirmValid=1;
                        break;
                    default:
                        printf("Invalid response. Please try again.\n");
                }
            } while(!dConfirmValid);
        } 
        else{
            printf("Invalid response. Please try again.\n");
            dValid=0;
        }
    } while (!dValid);   
}

/**
 * This function asks the user which pet they want to delete from the ComPetDium
 * 
 * @param struct BattlePet pet[] - the array of pets
 * @param int* dCurrentPets - current total of battlepets
 * @param int index - index of pet in BattlePet array to be deleted 
 * @return void
 */
void
deleteBattlepet (struct BattlePet pet[], int* dCurrentPets){
    int dChoice, dValid, dConfirmValid;
    char cConfirm;

    printf("\n DELETE BATTLEPET \n");
    viewBattlepets(pet, *dCurrentPets);
    printf("[0] Exit");

    do{
        printf("\nWhich BattlePet do you want to delete?\n");
        dValid = scanf(" %d", &dChoice);
        while (getchar() != '\n'); // clear buffer

        if (dValid && dChoice==0){
            printf("Exiting Delete BattlePet...");
        }
        else if (dValid && dChoice<=16 && dChoice>0){ // not allowed to delete initial battlepets
            dValid=0;
            printf("You are not allowed to delete the initial BattlePets. Please try again.");
        } 
        else if (dValid && dChoice>16 && dChoice<= *dCurrentPets){
            dValid=0;
            dConfirmValid=0;
            do // ask for confirmation
            {
            printf("Would you like to delete '%s'? [y/n] \n", pet[dChoice-1].name);
            scanf(" %c", &cConfirm);
            while (getchar() != '\n'); // clear buffer
                //check if user responded y or n
                switch(cConfirm){
                    case 'y':
                        deleteBattlepetDetails(pet, &dCurrentPets, dChoice-1);
                        printf("Successfully deleted BattlePet.\n");
                        dValid=1;
                        dConfirmValid=1;
                        break;
                    case 'n':
                        dConfirmValid=1;
                        break;
                    default:
                        printf("Invalid response. Please try again.\n");
                }
            } while(!dConfirmValid);
        } 
        else{
            printf("Invalid response. Please try again.\n");
            dValid=0;
        }
    } while (!dValid);
}

/**
 * This function is used to create and save or edit a 3x3 Battlepet roster for a player
 *
 * @param struct Player player[] - the array of players
 * @param int* dCurrentPlayers - the address to the number of current players
 * @return void
 */
void
saveRoster (struct BattlePet pet[], struct Player player[], int* dCurrentPlayers, int dCurrentPets){
    struct BattlePet roster[3][3];
    string150 txtFilename;
    struct Player* currentPlayer;
    string password;
    int dChoice, dValid, dStartRoster;
    char cConfirm;

    printf("\n SAVE ROSTER \n");

    do{ //PLAYER SELECTION
        printf("Save roster for which player?\n");
        displayChoices(player, dCurrentPlayers);
        dValid = scanf(" %d", &dChoice);

        if (dValid && dChoice==0){
            printf("Exiting Save Roster...");
        }
        else if (dValid && dChoice==1){
            printf("New Player Creation");
            newPlayer(player, dCurrentPlayers);
            dStartRoster=1;
        } else if (dValid){
            //input password of player chosen
            printf ("Hello! %s\n", player[dChoice].name);
            printf ("Your password: %s\n", player[dChoice].savedPassword);
            printf ("Enter your password: ");
            scanf ("%s", password);
            
            if(strcmp (password, player[dChoice].savedPassword) == 0){
                printf ("Welcome %s\n", player[dChoice].name);
                *currentPlayer = player[dChoice];
                dStartRoster=1;
            } else{
                printf ("Get out\n");
            }
        } else{
            printf("Invalid response. Please try again.\n");
            dValid=0;
        }
    } while (!dValid);
    dValid=0;

    if(dStartRoster==1){ //SAVE ROSTER
        printf("%s's Currently Saved Roster:\n", player[dChoice].name);
        
        loadSavedRoster (currentPlayer->name, pet, currentPlayer, dCurrentPets);
        displayRoster (currentPlayer->pet);

        do {
            // Check if player already has a roster
            if (currentPlayer->pet[0].name[0] == '\0') {
                printf("You don't have a roster yet, would you like to create one?\n");
                printf("\n%s\n%s", "[1] Yes", "[0] Exit");
                scanf("%d", &dChoice);

                if (dChoice == 1) {
                    selectPets(pet, currentPlayer, dCurrentPets);
                    // make new file in saved_roster folder
                    getTxtname(currentPlayer->name, txtFilename, "saved_roster/");
                    FILE *file = fopen(txtFilename, "w");
                    if (file == NULL) {
                        printf("File not found\n");
                    } else {
                        for (int x = 0; x < MAX_ROSTER; x++) {
                            fprintf(file, "%s\n", currentPlayer->pet[x].name);
                        }
                        fclose(file);
                    }
                    dValid = 1; // exit the loop after saving
                } else {
                    printf("Exiting Save Roster...\n");
                    return; // exit function if user chooses to exit
                }
            } else {
                printf("You already have a roster. Would you like to edit it or create a new one?\n");
                // Add logic to edit existing roster or create a new one
                // For simplicity, we'll assume they want to edit it
                selectPets(pet, currentPlayer, dCurrentPets);
                getTxtname(currentPlayer->name, txtFilename, "saved_roster/");
                FILE *file = fopen(txtFilename, "w");
                if (file == NULL) {
                    printf("File not found\n");
                } else {
                    for (int x = 0; x < MAX_ROSTER; x++) {
                        fprintf(file, "%s\n", currentPlayer->pet[x].name);
                    }
                    fclose(file);
                }
                dValid = 1; // exit the loop after saving
            }
        } while (!dValid);
    }
}
