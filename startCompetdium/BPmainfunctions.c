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
 * in the importpets folder
 * @param struct BattlePet pet[] - the array of battlepets
 * @param int* dCurrentPets - current total of battlepets
 */
void
addBattlepet (struct BattlePet pet[], int* dCurrentPets){
    int dChoice;

    do{
    printf("total battlepets: %d\n", *dCurrentPets); ///// remove when patapos n
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
            break;
        default:
            printf("Invalid input. Please try again.");
            break;
        }
    updateCompetdiumTxt(pet, *dCurrentPets); //update competdium.txt
    } while (dChoice != 0);

}

/**
 * This function asks the user which BattlePet and what characteristic they want to modify
 * @param struct BattlePet pet[] - the array of pets
 * @param int dCurrentPets - current total of battlepets
 * @return void
 */
void
editBattlepet(struct BattlePet pet[], int* dCurrentPets) {
    int dChoice, dEditChoice, dConfirmValid;
    char cConfirm;
    int exitOuterLoop = 0; // Flag to control the outer loop

    while (!exitOuterLoop) { // outer loop
        printf("\n EDIT BATTLEPET \n");
        viewBattlepets(pet, *dCurrentPets);
        printf("[0] Exit\n");

        printf("\nWhich BattlePet do you want to edit?\n");
        scanf(" %d", &dChoice);

        if (dChoice == 0) {
            printf("Exiting Edit BattlePet...\n");
            exitOuterLoop = 1; // exit the outer loop
        } else if (dChoice > 16 && dChoice <= *dCurrentPets) {
            dConfirmValid = 0; // reset confirmation 
            while (!dConfirmValid) { // confirmation loop
                printf("Would you like to edit '%s'? [y/n] \n", pet[dChoice - 1].name);
                scanf(" %c", &cConfirm);

                if (cConfirm == 'y') {
                    dEditChoice = -1; // reset edit choice
                    while (dEditChoice != 0) { // edit loop
                        printf ("\n%s{%s} - used %d times\n%s\n",
                            pet[dChoice-1].name,
                            pet[dChoice-1].affinity,
                            pet[dChoice-1].matchCount,
                            pet[dChoice-1].description);
                        
                        printf("\n%s\n%s\n%s\n%s\n",
                               "[1] Name",
                               "[2] Affinity",
                               "[3] Description",
                               "[0] Back");
                        printf("What do you want to modify?\n");
                        scanf(" %d", &dEditChoice);

                        if (dEditChoice >= 0 && dEditChoice <= 3) {
                            switch (dEditChoice) {
                                case 1:
                                    dConfirmValid = editBPname(&pet[dChoice - 1]);
                                    break;
                                case 2:
                                    dConfirmValid = editBPaffinity(&pet[dChoice - 1]);
                                    break;
                                case 3:
                                    dConfirmValid = editBPdesc(&pet[dChoice - 1]);
                                    break;
                                case 0:
                                    printf("Returning to edit selection...\n");
                                    break;
                                default:
                                    printf("Invalid response. Please try again.\n");
                                    break;
                            }
                            if (dConfirmValid) { // check if edit was successful
                                printf("BattlePet edit of '%s' is successful.\n", pet[dChoice - 1].name);
                                updateCompetdiumTxt(pet, *dCurrentPets);
                            }
                        } else {
                            printf("Invalid response. Please try again.\n");
                        }
                    }
                    dConfirmValid = 1; // exit confirmation loop after editing
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
 * @param int index - index of pet in BattlePet array to be deleted 
 * @return void
 */
void
deleteBattlepet (struct BattlePet pet[], int* dCurrentPets){
    int dChoice, dConfirmValid;
    char cConfirm;
    dConfirmValid=0;

    do{
        printf("\n DELETE BATTLEPET \n");
        viewBattlepets(pet, *dCurrentPets);
        printf("[0] Exit");
        printf("\nWhich BattlePet do you want to delete?\n");
        scanf(" %d", &dChoice);

        if(dChoice>16 && dChoice<= *dCurrentPets){
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

        } else if (dChoice<=16 && dChoice>0){
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
 * This function is used to create and save or edit a 3x3 Battlepet roster for a player
 *
 * @param struct Player player[] - the array of players
 * @param int* dCurrentPlayers - the address to the number of current players
 * @return void
 */
void
saveRoster (struct BattlePet pet[], struct Player player[], int* dCurrentPlayers, int dCurrentPets){
    struct BattlePet editRoster[MAX_ROSTER];
    string150 txtFilename;
    struct Player* currentPlayer;
    string password;
    int dChoice, dValid, dStartRoster, dNewPetIndex;
    char truncatedName[sizeof(currentPlayer->pet[0].name)]; // Buffer for truncated names
    int maxNameLength = sizeof(editRoster[0].name) - 5;    // Reserve space for "[%d] " and the null terminator

    printf("\n SAVE ROSTER \n");

    do{ //PLAYER SELECTION
        printf("Save roster for which player?\n");
        displayChoices(player, dCurrentPlayers);
        dValid = scanf(" %d", &dChoice);

        if (dValid != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            dChoice = -1; // Set to an invalid value to prevent further processing
        } else if (dChoice == 0) {
            printf("Exiting Save Roster...\n");
        } else if (dChoice == 1) {
            printf("New Player Creation\n");
            newPlayer(player, dCurrentPlayers);
            dValid = 0;
        } else if (dChoice > 0 && dChoice <= (*dCurrentPlayers+1)) {
            
            // Input password of player chosen
            printf("Hello! %s\n", player[dChoice - 2].name);
            printf("Your password: %s\n", player[dChoice - 2].savedPassword);
            printf("Enter your password: ");
            scanf("%s", password);
     
            if(strcmp (password, player[dChoice-2].savedPassword) == 0){
                printf ("Welcome %s\n", player[dChoice-2].name);
                currentPlayer = &player[dChoice-2]; // set current player to the selected player
                dStartRoster=1;
            } else{
                printf ("Get out\n");
                dValid=0;
            }
        } else{
            printf("Invalid response. Please try again.\n");
            dValid=0;
        }
    } while (!dValid);
    
    if(dStartRoster==1){ //SAVE ROSTER
        dValid=0;
        printf("%s's Currently Saved Roster:\n", currentPlayer->name);
        
        loadSavedRoster (currentPlayer->name, pet, currentPlayer, dCurrentPets);
        displayRoster (currentPlayer->pet);

    do {
            // Check if player already has a roster
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
                        //copy roster with indexes
                        for (int i = 0; i < MAX_ROSTER; i++) {
                            // Copy and truncate the pet name manually
                            strncpy(truncatedName, currentPlayer->pet[i].name, maxNameLength);
                            truncatedName[maxNameLength] = '\0'; // Ensure null termination

                            // Format the string with the truncated name
                            sprintf(editRoster[i].name, "[%d] %s", i + 1, truncatedName);
                        }

                        displayRoster(editRoster); // display the roster with index numbers

                        printf("Please select the index of the pet you want to replace: ");
                        scanf("%d", &dChoice);
                        
                        if (dChoice > 0 && dChoice <= MAX_ROSTER) {
                            printf("Select a new BattlePet from the ComPetDium:\n");
                            viewBattlepets(pet, dCurrentPets); // display all available BattlePets
                
                            printf("Enter the index of the new BattlePet: ");
                            scanf("%d", &dNewPetIndex);
                        
                            if (dNewPetIndex > 0 && dNewPetIndex <= dCurrentPets) {
                                // Check if the selected pet is already in the current player's roster
                                int isDuplicate = 0;
                                for (int i = 0; i < MAX_ROSTER; i++) {
                                    if (strcmp(currentPlayer->pet[i].name, pet[dNewPetIndex - 1].name) == 0) {
                                        isDuplicate = 1; // Mark as duplicate
                                        break;
                                    }
                                }

                                if (isDuplicate) {
                                    printf("The selected BattlePet '%s' is already in your roster. No changes were made.\n", pet[dNewPetIndex - 1].name);
                                } else {
                                    // Overwrite the selected pet in the roster
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
                        selectPets(pet, currentPlayer, dCurrentPets);
                        getTxtname(currentPlayer->name, txtFilename, "saved_roster/");
                        saveRosterToFile(txtFilename, currentPlayer); // update roster
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
 * This function is used to ask the user if they want to add pets from the petExpansion.txt file to the ComPetDium
 * It allows the user to add one pet or all pets from the file.
 * 
 * @param struct BattlePet pet[] - the array of pets
 * @param int** dCurrentPets - current total of battlepets
 * @return void
 */
void addPetsFromExpansion(struct BattlePet pet[], int* dCurrentPets) {
    struct BattlePet addPets[MAX_BATTLEPETS]; // Array to hold pets from the file
    int dTotalAddPets, dPetMaxCheck, dPetTotal = *dCurrentPets;
    int dChoice, petIndex;

    // Load pets from petExpansion.txt
    printf("\nLoading pets from 'petExpansion.txt'...\n");
    dTotalAddPets = getComPetDium(addPets, "petExpansion.txt"); // Read pets from the file
    if (dTotalAddPets == 0) {
        printf("No pets found in 'petExpansion.txt'.\n");
        return;
    }

    // Display the pets from the file
    printf("\nThe following pets are available in 'petExpansion.txt':\n");
    viewBattlepets(addPets, dTotalAddPets);

    // Ask the user if they want to add one or all pets
    do {
        printf("\nWould you like to:\n");
        printf("[1] Add one pet\n");
        printf("[2] Add all pets\n");
        printf("[0] Cancel\n");
        printf("Enter your choice: ");
        scanf(" %d", &dChoice);
        while (getchar() != '\n'); // Clear input buffer

        switch (dChoice) {
            case 1: // Add one pet
            do{
                printf("\nEnter the index of the pet you want to add (1 to %d): ", dTotalAddPets);
                scanf(" %d", &petIndex);

                if (petIndex < 1 || petIndex > dTotalAddPets) {
                    printf("Invalid index. Please try again.\n");
                } else {
                    // Check if adding one pet exceeds the max limit
                    dPetMaxCheck = checkIfPetMax(pet, dCurrentPets, 1);
                    if (dPetMaxCheck){
                        // Add the selected pet
                        printf("Adding pet '%s'...\n", addPets[petIndex - 1].name);
                        *dCurrentPets = addOnePetDetails(pet, addPets[petIndex - 1], dPetTotal);
                        printf("Pet '%s' has been successfully added to the ComPetdium.\n", addPets[petIndex - 1].name);
                    }
                }
            } while (petIndex < 1 || petIndex > dTotalAddPets); // Loop until a valid index is entered
                break;

            case 2: // Add all pets
                // Check if adding all pets exceeds the max limit
                dPetMaxCheck = checkIfPetMax(pet, dCurrentPets, dTotalAddPets);
                if (dPetMaxCheck) {
                    // Add all pets
                    printf("Adding all pets from 'petExpansion.txt'...\n");
                    *dCurrentPets = addMultiplePetsDetails(pet, addPets, dPetTotal, dTotalAddPets);
                    printf("All pets have been successfully added to the ComPetdium.\n");
                }
                break;

            case 0: // Cancel
                printf("Operation canceled. No pets were added.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (dChoice != 0 && dChoice != 1 && dChoice != 2);
}