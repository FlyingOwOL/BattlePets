/**
* Description : This file contains the functions that are required for startComPetdium and to aid BPfunctions
*
* Author/s : Sy, Jason Mark Lester B. 
*            Enerio, Gabrielle G.      
* Section : S19B
* Last Modified : March 31, 2025
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
    updateCompetdiumTxt(pet, dCurrentPets); //update competdium.txt
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
 * in the import_pets folder
 * @param struct BattlePet pet[] - the array of battlepets
 * @param int* dCurrentPets - current total of battlepets
 * @return void
 */
void
addBattlepet (struct BattlePet pet[], int* dCurrentPets){
    int dChoice;

    do{
    printf("Total Battlepets: %d\n", *dCurrentPets);
    printf("Add one manually or multiple from import_pets folder?\n");
    printf("[1] Add one manually \n");
    printf("[2] Add multiple from folder\n");
    printf("[0] Exit\n");
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
            break;\
        default:
            printf("Invalid input. Please try again.");
            break;
        }
    } while (dChoice != 0);

}

/**
 * This function asks the user which BattlePet and what characteristic they want to modify
 * @param struct BattlePet pet[] - the array of pets
 * @param int* dCurrentPets - current total of battlepets
 * @return void
 */
void
editBattlepet(struct BattlePet pet[], int* dCurrentPets) {
    int dChoice, dEditChoice, dConfirmValid;
    char cConfirm;
    int exitOuterLoop = 0; // flag to control the outer loop

    while (!exitOuterLoop) { // outer loop
        printf("\n EDIT BATTLEPET \n");
        viewBattlepets(pet, *dCurrentPets); //displays battlepets
        printf("[0] Exit\n");

        printf("\nWhich BattlePet do you want to edit?\n");
        scanf(" %d", &dChoice); 

        if (dChoice == 0) {
            printf("Exiting Edit BattlePet...\n");
            exitOuterLoop = 1; // if 0, exit the outer loop/ exit function
        } else if (dChoice > 16 && dChoice <= *dCurrentPets) {
            dConfirmValid = 0; // reset confirmation 
            while (!dConfirmValid) { // confirmation loop
                printf("Would you like to edit '%s'? [y/n] \n", pet[dChoice - 1].name);
                scanf(" %c", &cConfirm);

                if (cConfirm == 'y') {
                    dEditChoice = -1; // reset edit choice
                    while (dEditChoice != 0) { // edit loop
                        printf ("\n%s{%s} - used %d times\n%s\n", // display pet details
                            pet[dChoice-1].name,
                            pet[dChoice-1].affinity,
                            pet[dChoice-1].matchCount,
                            pet[dChoice-1].description);
                        
                        printf("\n%s\n%s\n%s\n%s\n", // display edit choices
                               "[1] Name",
                               "[2] Affinity",
                               "[3] Description",
                               "[0] Back");
                        printf("What do you want to modify?\n");
                        scanf(" %d", &dEditChoice);

                        if (dEditChoice >= 0 && dEditChoice <= 3) {
                            switch (dEditChoice) {
                                case 1:
                                    dConfirmValid = editBPname(&pet[dChoice - 1]); // confirm can exit edit loop
                                    break;
                                case 2:
                                    dConfirmValid = editBPaffinity(&pet[dChoice - 1]); // confirm can exit edit loop
                                    break;
                                case 3:
                                    dConfirmValid = editBPdesc(&pet[dChoice - 1]); // confirm can exit edit loop
                                    break;
                                case 0:
                                    printf("Returning to edit selection...\n");
                                    dConfirmValid = 1; // exit confirmation loop
                                    break;
                                default:
                                    printf("Invalid response. Please try again.\n");
                                    break;
                            }
                            if (dConfirmValid) { // check if edit was successful
                                printf("BattlePet edit of '%s' is successful.\n", pet[dChoice - 1].name);
                                updateCompetdiumTxt(pet, *dCurrentPets); // update competdium
                            }
                        } else {
                            printf("Invalid response. Please try again.\n");
                        }
                    }
                } else if (cConfirm == 'n') {
                    printf("Please choose the BattlePet you want to edit.\n");
                    dConfirmValid = 1; // exit confirmation loop
                } else {
                    printf("Invalid response. Please try again.\n");
                }
            }
        } else if (dChoice <= 16) {
            printf("You are not allowed to edit the initial BattlePets. Please try again.\n");
        } else if (dChoice > *dCurrentPets) {
            printf("Invalid response. Please try again.\n");
        } else {
            printf("Invalid response. Please try again.\n");
        }
    }
}

/**
 * This function asks the user which pet they want to delete from the ComPetDium
 * 
 * @param struct BattlePet pet[] - the array of pets
 * @param int* dCurrentPets - current total of battlepets
 * @return void
 */
void
deleteBattlepet (struct BattlePet pet[], int* dCurrentPets){
    int dChoice, dConfirmValid;
    char cConfirm;
    dConfirmValid=0;

    do{
        printf("\n DELETE BATTLEPET \n");
        viewBattlepets(pet, *dCurrentPets); // displays battlepets
        printf("[0] Exit");
        printf("\nWhich BattlePet do you want to delete?\n");
        scanf(" %d", &dChoice);

        if(dChoice>16 && dChoice<= *dCurrentPets){ // check if input is valid
            do // ask for confirmation
            {
            printf("Would you like to delete '%s'? [y/n] \n", pet[dChoice-1].name);
            scanf(" %c", &cConfirm);
                //check if user responded y or n
                switch(cConfirm){
                    case 'y':
                        deleteBattlepetDetails(pet, &dCurrentPets, dChoice-1);
                        printf("Successfully deleted BattlePet.\n");
                        dConfirmValid=1;
                        break;
                    case 'n':
                        printf("Please choose the BattlePet you want to delete.\n");
                        dConfirmValid=1;
                        break;
                    default:
                        printf("Invalid response. Please try again.\n");
                        break;
                }
            } while(!dConfirmValid);

        } else if (dChoice<=16 && dChoice>0){ //exclude 16 initial battlepets
            printf("You are not allowed to delete the initial BattlePets. Please try again.");
        } else if (dChoice>*dCurrentPets){
            printf("Invalid response. Please try again.\n");
        } else if (dChoice==0){
            printf("Exiting Delete BattlePet...");

        } else {
            printf("Invalid response. Please try again.\n");
        }

    } while (dChoice!=0); // loop until user chooses to exit
}

/**
 * This function is used to create and save or edit a 3x3 BattlePet roster for a player
 *
 * @param struct Player pet[] - the array of pets
 * @param struct Player player[] - the array of players
 * @param int* dCurrentPlayers - the number of current players
 * @param int dCurrentPets - the number of current pets
 * @return void
 */
void
saveRoster (struct BattlePet pet[], struct Player player[], int* dCurrentPlayers, int dCurrentPets){
    string150 txtFilename;
    struct Player* currentPlayer;
    string password;
    int dChoice, dValid, dStartRoster, dNewPetIndex, isDuplicate;

    printf("\n SAVE ROSTER \n");

    do{ //PLAYER SELECTION
        // loops if wrong password, invalid response, new player created 

        printf("Save roster for which player?\n");
        displayChoices(player, dCurrentPlayers);
        dValid = scanf(" %d", &dChoice);

        if (dValid != 1) {  //check if scan succeeded
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  // clear the input buffer
            dChoice = -1;   // set to an invalid value to prevent further processing
        } else if (dChoice == 0) {  
            printf("Exiting Save Roster...\n"); //exit if 0
        } else if (dChoice == 1) {
            printf("New Player Creation\n"); 
            newPlayer(player, dCurrentPlayers); // creates new player if 1
            dValid = 0;
        } else if (dChoice > 0 && dChoice <= (*dCurrentPlayers+1)) { // check if valid selection
            
            // input password of player chosen
            printf("Hello! %s\n", player[dChoice - 2].name);
            printf("Your password: %s\n", player[dChoice - 2].savedPassword);
            printf("Enter your password: ");
            scanf("%s", password);
     
            if(strcmp (password, player[dChoice-2].savedPassword) == 0){
                printf ("Welcome %s\n", player[dChoice-2].name);
                currentPlayer = &player[dChoice-2]; // set current player to the selected player
                dStartRoster=1; // flag to start roster edit or creation
            } else{
                printf ("Get out\n");
                dValid=0;
            }
        } else{
            printf("Invalid response. Please try again.\n");
            dValid=0;
        }
    } while (!dValid);
    
    if(dStartRoster==1){ // SAVE ROSTER
        // only start roster after inputting password
        dValid=0;  // reset valid scan checker
        printf("%s's Currently Saved Roster:\n", currentPlayer->name);
        
        loadSavedRoster (currentPlayer->name, pet, currentPlayer, dCurrentPets); // loads player's roster from saved_roster folder
        displayRoster (currentPlayer->pet); 

    do {
            // check if player already has a roster
            if (currentPlayer->pet[0].name[0] == '\0') { // no roster yet
                printf("You don't have a roster yet, would you like to create one?\n");
                printf("\n%s\n%s", "[1] Yes", "[0] Exit");
                dValid = scanf("%d", &dChoice);

                switch(dChoice){
                    case 1:
                        selectPets(pet, currentPlayer, dCurrentPets);
                        // make new file in saved_roster folder
                        getTxtname(currentPlayer->name, txtFilename, "saved_roster/");
                        saveRosterToFile(txtFilename, currentPlayer); // save the roster to a file
                            printf("Roster created successfully.\n");
                            dValid=1;
                        break;
                    case 0:
                        printf("Exiting Save Roster...\n");
                        dValid=1;
                        break;  
                    default:
                        printf("Invalid choice. Please try again.\n");
                        dValid = 0;
                        break;
                }
            } else{ // has an existing roster
                printf("You already have a roster. Would you like to replace one pet of your roster or create a new one?\n");
                printf("[1] Replace One Pet in Roster\n[2] Create New Roster\n[0] Exit\n");
                dValid = scanf("%d", &dChoice);
                
                switch(dChoice){
                    case 1:
                        //display roster with indexes
                            for (int x = 0; x < MAX_ROSTER; x++){
                                if (x > 0 && x % 3 == 0){
                                    printf ("\n");
                                }            
                                printf (" <[%d] %s>", x+1, currentPlayer->pet[x].name);
                            }
                            printf ("\n");

                        printf("Please select the index of the pet you want to replace: ");
                        scanf("%d", &dChoice);
                        
                        if (dChoice > 0 && dChoice <= MAX_ROSTER) {
                            printf("Select a new BattlePet from the ComPetDium:\n");
                            viewBattlepets(pet, dCurrentPets); // display all available BattlePets
                
                            printf("Enter the index of the new BattlePet: ");
                            scanf("%d", &dNewPetIndex);
                        
                            if (dNewPetIndex > 0 && dNewPetIndex <= dCurrentPets) {
                                // check if the selected pet is already in the current player's roster
                                isDuplicate = 0;
                                for (int i = 0; i < MAX_ROSTER; i++) {
                                    if (strcmp(currentPlayer->pet[i].name, pet[dNewPetIndex - 1].name) == 0) {
                                        isDuplicate = 1; // mark as duplicate
                                    }
                                }

                                if (isDuplicate) { // check if its a duplicate
                                    printf("The selected BattlePet '%s' is already in your roster. No changes were made.\n", pet[dNewPetIndex - 1].name);
                                } else {
                                    // overwrite the selected pet in the roster
                                    currentPlayer->pet[dChoice - 1] = pet[dNewPetIndex - 1];
                                    getTxtname(currentPlayer->name, txtFilename, "saved_roster/");
                                    saveRosterToFile(txtFilename, currentPlayer); // Update roster
                                    printf("BattlePet at index %d has been replaced with '%s'.\n", dChoice, pet[dNewPetIndex - 1].name);
                                    dValid = 1;
                                }
                            } else {
                                printf("Invalid BattlePet index. No changes were made.\n");
                            }
                        } else {
                            printf("Invalid roster index. No changes were made.\n");
                        }
                        break;
                    case 2:
                        selectPets(pet, currentPlayer, dCurrentPets); // select pets for roster
                        getTxtname(currentPlayer->name, txtFilename, "saved_roster/");
                        saveRosterToFile(txtFilename, currentPlayer); // update player roster to saved_roster folder
                        printf("Roster created successfully.\n");
                        dValid=1;
                        break;
                    case 0:
                        printf("Exiting Save Roster...\n");
                        dValid=1;
                        break;  
                    default:
                        printf("Invalid choice. Please try again.\n");
                        dValid = 0;
                        break;
                }
            }     
        } while (!dValid); // loop until valid response or exit   
    }
}
        
/**
 * This function is used to add pets from the petExpansion.txt file to the ComPetDium
 * It allows the user to add one pet or all pets from the file
 * 
 * @param struct BattlePet pet[] - the array of pets
 * @param int* dCurrentPets - current total of battlepets
 * @return void
 */
void addPetsFromExpansion(struct BattlePet pet[], int* dCurrentPets) {
    struct BattlePet addPets[MAX_BATTLEPETS]; // array to hold pets from the file
    int dTotalAddPets, dPetMaxCheck, dPetTotal = *dCurrentPets;
    int dChoice, petIndex;

    // load pets from petExpansion.txt
    printf("\nLoading pets from 'petExpansion.txt'...\n");
    dTotalAddPets = getComPetDium(addPets, "petExpansion.txt"); // read pets from the file
    if (dTotalAddPets == 0) {
        printf("No pets found in 'petExpansion.txt'.\n");
    }
    else {
    // display the pets from the file
    printf("\nThe following pets are available in 'petExpansion.txt':\n");
    viewBattlepets(addPets, dTotalAddPets);

    // ask the user if they want to add one or all pets
    do {
        printf("\nWould you like to:\n");
        printf("[1] Add one pet\n");
        printf("[2] Add all pets\n");
        printf("[0] Cancel\n");
        printf("Enter your choice: ");
        scanf(" %d", &dChoice);
        while (getchar() != '\n'); // clear input buffer

        switch (dChoice) {
            case 1: // add one pet
            do{
                printf("\nEnter the index of the pet you want to add (1 to %d): ", dTotalAddPets);
                scanf(" %d", &petIndex);

                if (petIndex < 1 || petIndex > dTotalAddPets) {
                    printf("Invalid index. Please try again.\n");
                } else {
                    // check if adding one pet exceeds the max limit
                    dPetMaxCheck = checkIfPetMax(pet, dCurrentPets, 1);
                    if (dPetMaxCheck){
                        // add the selected pet
                        printf("Adding pet '%s'...\n", addPets[petIndex - 1].name);
                        *dCurrentPets = addOnePetDetails(pet, addPets[petIndex - 1], dPetTotal);
                        printf("Pet '%s' has been successfully added to the ComPetdium.\n", addPets[petIndex - 1].name);
                    }
                }
            } while (petIndex < 1 || petIndex > dTotalAddPets); // loop until a valid index is entered
                break;

            case 2: // add all pets
                // check if adding all pets exceeds the max limit
                dPetMaxCheck = checkIfPetMax(pet, dCurrentPets, dTotalAddPets);
                if (dPetMaxCheck) {
                    // add all pets
                    printf("Adding all pets from 'petExpansion.txt'...\n");
                    *dCurrentPets = addMultiplePetsDetails(pet, addPets, dPetTotal, dTotalAddPets);
                    printf("All pets have been successfully added to the ComPetdium.\n");
                }
                break;

            case 0: // exit
                printf("Operation canceled. No pets were added.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (dChoice != 0 && dChoice != 1 && dChoice != 2);
    } // end of else
}