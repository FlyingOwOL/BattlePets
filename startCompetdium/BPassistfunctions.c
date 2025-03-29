/*
    This file contains the functions that are used for computations and to aid the BPmainfunctions
*/
#include <stdio.h>
#include "../BPheaders.h"

/**
 * This function edits a battlepet's name and asks the user what they want
 * to replace it with. Returns 1 if successful, returns 0 if not
 * @param struct BattlePet pet - the BattlePet struct to be modified
 */
int
editBPname (struct BattlePet* pet){
    int dResult;
    char cValid;
    dResult = 0;

    do
    { // check if name is valid
        printf("Input BattlePet Name (MAX 35 CHARACTERS): ");
        scanf(" %35s", pet->name);
        while (getchar() != '\n'); // clear buffer
            
        if (strlen(pet->name) <= 35){
            do
            {
            printf("\n Is your BattlePet's name '%s'? [y/n]", pet->name);
            scanf(" %c", &cValid);
                switch (cValid){
                    case 'y':
                        printf("BattlePet name is successfully changed to '%s'.\n", pet->name);
                        dResult = 1; //successful execution
                        break;
                    case 'n':
                        printf("Please input a new name.");
                        break;
                    default:
                        printf("\n Invalid response. Please try again.");
                }
            } while(cValid!='y' && cValid!='n');
        } else{
            printf("Invalid response. Please input a name 35 characters or below.");
        }

    } while(cValid!='y');        

    return dResult;
}

/**
 * This function edits a battlepet's affinity and asks the user what they want
 * to replace it with. Returns 1 if successful, returns 0 if not
 * @param struct BattlePet pet - the BattlePet struct to be modified
 */
int
editBPaffinity (struct BattlePet* pet){
    int dChoice, dResult;
    char cValid;
    string affinity[] = {"Fire", "Water", "Grass", "Earth", "Air", "Electric", "Ice", "Metal"};
    dResult = 0;
    
    printf("\n BATTLEPET AFFINITY\n");
    for (int i=0; i<8; i++){
        printf("[%d] %s\n", i+1, affinity[i]);
    }
    
    do
    {
     //check if affinity is valid
        printf("Choose your BattlePet's affinity:");
        scanf(" %d", &dChoice);

        if(dChoice>0 && dChoice<9){
            do{
        printf("\n Is your BattlePet's affinity '%s'? [y/n]", affinity[dChoice-1]);
        scanf(" %c", &cValid);

        switch (cValid){
            case 'y':
                printf("BattlePet affinity is successfully changed to '%s'.\n", pet->affinity);
                strcpy(pet->affinity, affinity[dChoice-1]);
                dResult = 1; // successful execution
                break;
            case 'n':
                printf("Please input the new affinity.");
                break;
            default:
                printf("\n Invalid response. Please try again.");
            } 
        } while(cValid!='y' && cValid!='n');
    } else{
            printf("Invalid response. Please choose between 1-9.");
        }
} while (cValid != 'y');
    
    return dResult;
}
   
/**
 * This function edits a battlepet's description and asks the user what they want
 * to replace it with. Returns 1 if successful, returns 0 if not
 * @param struct BattlePet pet - the BattlePet struct to be modified
 */
int
editBPdesc (struct BattlePet* pet){
    int dResult;
    char cValid;
    dResult=0;

    do
    {
        printf("Input BattlePet Description (MAX 239 CHARACTERS): ");

        scanf(" %239[^\n]", pet->description);
        while (getchar() != '\n'); // clear buffer
            
        if (strlen(pet->description) <= 239){
            do
            {
            printf(" %s\n", pet->description);
            printf("Is this the description of your BattlePet? [y/n]");
            scanf(" %c", &cValid);
                switch (cValid){
                    case 'y':
                        printf("BattlePet description is successfully changed.\n");
                        dResult = 1;
                        break;
                    case 'n':
                        printf("Please input a new description.");
                        break;
                    default:
                        printf("\n Invalid response. Please try again.");
                }
            } while(cValid!='y' && cValid!='n');
        } else{
            printf("Invalid response. Please input a description 239 characters or below.");
        }
    } while (cValid!='y');

    return dResult;
}



/**
 * This function is used to delete the details of an existing pet in competdium.txt
 * and its structure in the BattlePets array.
 * @param struct BattlePet pet[] - the array of pets
 * @param int** dCurrentPets - current total of battlepets
 * @param int index - index of pet in BattlePet array to be deleted 
 * @return void
 */
void
deleteBattlepetDetails (struct BattlePet pet[], int** dCurrentPets, int index){
    int i;
    int dPetTotal;

    (**dCurrentPets)--; //subtract from current pets
    dPetTotal=(**dCurrentPets);

    //shift elements in struct array to overwrite pet to be deleted
    for(i=index; i<dPetTotal; i++){
        pet[i] = pet[i+1];
    }
    //*clear out last index in array
    /*
    strcpy(pet[dPetTotal].name,"");
    strcpy(pet[dPetTotal].affinity,"");
    strcpy(pet[dPetTotal].description,"");
    pet[dPetTotal].matchCount = 0;
    */

    //delete in competdium.txt
    updateCompetdiumTxt(pet, dPetTotal);
}

/**
 * This function checks if the number of battlepets to be added will make the competdium
 * reach its max amount. If it does, it asks the user if they want to continue and remove
 * the recently added pets or cancel the addition.
 * 
 * @param struct BattlePet pet[] - the array of pets
 * @param int* dCurrentPets - pointer to the current total of battlepets
 * @param int dPetsToAdd - the number of pets to be added
 * @return int - 1 if the user decides to continue, 0 if they cancel
 */
int checkIfPetMax(struct BattlePet pet[], int* dCurrentPets, int dPetsToAdd) {
    //cant delete first 16 initial battlepets
    
    int dNewTotal = *dCurrentPets + dPetsToAdd;
    int dResult = 0; // Default to not continuing

    // Check if the new total exceeds the maximum allowed pets
    if (dNewTotal > MAX_BATTLEPETS) {
        char cConfirm;
        int petsToRemove = dNewTotal - MAX_BATTLEPETS;

        printf("\nAdding %d pets will exceed the maximum allowed number of %d pets.\n", dPetsToAdd, MAX_BATTLEPETS);
        printf("The following BattlePets will be removed:\n");

        // Display the BattlePets that will be removed
        for (int i = MAX_BATTLEPETS; i < dNewTotal; i++) {
            if (strlen(pet[i].name) > 0) { // Check if the pet has a valid name
                printf("%d. %s {%s} - used %d times\n%s\n\n",
                       i + 1,
                       pet[i].name,
                       pet[i].affinity,
                       pet[i].matchCount,
                       pet[i].description);
            } else {
                printf("%d. [Empty Slot] - No valid data\n\n", i + 1);
            }
        }

        do {
            printf("Do you want to continue? This will remove the recently added pets. [y/n]: ");
            scanf(" %c", &cConfirm);
            if (cConfirm == 'y') {
                // Remove the recently added pets
                printf("Removing the last %d recently added pets to stay within the limit.\n", petsToRemove);

                // Adjust the current pets count and remove the excess pets
                *dCurrentPets = MAX_BATTLEPETS;

                // Clear the excess pets from the array
                for (int i = MAX_BATTLEPETS; i < dNewTotal; i++) {
                    deleteBattlepetDetails(pet, &dCurrentPets, i); //deletes battlepet and updates competdium
                }
                dResult = 1; // User decided to continue
            } else if (cConfirm == 'n') {
                printf("Operation canceled. No pets were added.\n");
                dResult = 0; // User decided to cancel
            } else {
                printf("Invalid response. Please enter 'y' or 'n': ");
            }
        } while (cConfirm != 'y' && cConfirm != 'n');
    } else {
        // If the new total does not exceed the maximum, allow the addition
        dResult = 1;
    }

    return dResult;
}

/**
 * This function is used to add one pet manually to competdium.txt and to the BattlePets array
 * Returns updated pet total
 * @param struct BattlePet pet[] - the array of battlepets
 * @param struct BattlePet - the struct of the battlepet to be added
 * @param int dCurrentPets - current total of battlepets
 * @return int 
 */
int
addOnePetDetails (struct BattlePet pet[], struct BattlePet addPet, int dCurrentPets){
        // add to competdium.txt
        FILE *cpdfile = fopen ("competdium.txt", "a");
        if (cpdfile == NULL){
            printf("competdium.txt not found");
        } //update competdium txt file
        fprintf(cpdfile, "%s\n%s\n%s\n%d\n\n", addPet.name, addPet.affinity, addPet.description, 0);
        fclose(cpdfile);
    
        // add to battlepets array
        strcpy(pet[dCurrentPets].name, addPet.name);
        strcpy(pet[dCurrentPets].affinity, addPet.affinity);
        strcpy(pet[dCurrentPets].description, addPet.description);
        pet[dCurrentPets].matchCount = 0;
        
        return dCurrentPets++; //update pet total
}

/**
 * This function adds multiple pets from a struct BattlePet array to the main
 * Battlepets array and to the competdium.txt
 * Returns updated pet total
 * @param struct BattlePet pet[] - the array of battlepets
 * @param struct BattlePet addPets[] - the array of the battlepets to be added
 * @param int dCurrentPets - current total of battlepets
 * @param int dTotalAddPets - total amount of battlepets to be added
 * @return int 
 */
int
addMultiplePetsDetails (struct BattlePet pet[], struct BattlePet addPets[], 
                        int dCurrentPets, int dTotalAddPets){
    
    int i;
    // check if past max amount

    FILE *cpdfile = fopen ("competdium.txt", "a");
    if (cpdfile == NULL){
        printf("competdium.txt not found");
    } else{

    for(i=0; i<dTotalAddPets; i++){ //update competdium txt file
    fprintf(cpdfile, "%s\n%s\n%s\n%d\n\n", addPets[i].name, addPets[i].affinity, addPets[i].description, 0);
    }
    fclose(cpdfile);
    
    // add to battlepets array
    for(i=0; i<dTotalAddPets; i++){
    strcpy(pet[dCurrentPets].name, addPets[i].name);
    strcpy(pet[dCurrentPets].affinity, addPets[i].affinity);
    strcpy(pet[dCurrentPets].description, addPets[i].description);
    pet[dCurrentPets].matchCount = 0;
    dCurrentPets++;
    }
    }
    
    printf("dcurrentpets = %d\n", dCurrentPets); ////////////
    printf("dtotalpets = %d\n", dTotalAddPets); /////////////
    
    return dCurrentPets; //update pet total
}


/**
 * This function aids the user in creating one BattlePet and
 * adding it manually to competdium.txt and to the BattlePets array
 * @param struct BattlePet pet[] - the array of battlepets
 * @param int* dCurrentPets - current total of battlepets
 */
void
addOnePet (struct BattlePet pet[], int** dCurrentPets){
    int dPetTotal = **dCurrentPets;
    struct BattlePet addPet;
    int status[3] = {0,0,0};
    int dFinalCheck, dScanValid, dPetMaxCheck;

    //check if max_battlepets is reached
    dPetMaxCheck = checkIfPetMax(pet, *dCurrentPets, 1);
    if (dPetMaxCheck == 0) {
        printf("You have reached the maximum number of BattlePets.\n");
    }
    else{
    do { // user can restart creation process
        
        //edit name
        status[0]=editBPname(&addPet);
        //edit affinity
        status[1]=editBPaffinity(&addPet);
        //edit description
        status[2]=editBPdesc(&addPet);
        
        if(status[0]==1 && status[1]==1 && status[2]==1){
            //recheck pet details
            printf("\nADD BATTLEPET\n");
            printf("BattlePet Name: %s\n", addPet.name);
            printf("Affinity: %s\n", addPet.affinity);
            printf("Description:\n");
            /////////////////////////////////////////////////// PUT PRINTFORMAT FUNCTION HERE
            printf("%s\n", addPet.description);

            do {
                printf("\n Are the details of your BattlePet correct?\n");
                printf("[1] Yes. Add it to the ComPetdium \n");
                printf("[2] No. Restart pet creation \n");
                printf("[0] Exit. Pet will not be added to the ComPetdium \n");
                dScanValid = scanf(" %d", &dFinalCheck);
                while (getchar() != '\n'); // clear buffer

                if (dScanValid){
                    switch(dFinalCheck){
                        case 1: 
                            printf("\nPet has been added to the ComPetdium.");
                            dScanValid--;
                            break;
                        case 2: 
                            printf("\nRestarting pet creation.");
                            dScanValid--;
                            break;
                        case 0:
                            printf("\nExiting BattlePet Creation.");
                            dScanValid--;
                            break;
                        default:
                            printf("Invalid input\n");
                            break;
                    }
                } else {
                    printf("Invalid input. Please try again.\n");
                }
            } while(dScanValid);
        } 
    } while(dFinalCheck!=1 && dFinalCheck!=0);
    
    if(dFinalCheck==1){
        **dCurrentPets = addOnePetDetails(pet, addPet, dPetTotal);
    }
    }        
}

/**
 * This function is used to add multiple pets at once by selecting 
 * a file in the import_pets folder
 */
void
addMultiplePets(struct BattlePet pet[], int** dCurrentPets){
    int dChoice, dTotalAddPets, dPetTotal, dPetMaxCheck;
    char cConfirm;
    struct BattlePet addPets[MAX_BATTLEPETS]; // excluding initial pets
    string150 txtfiles[10];
    string150 filename;

    dPetTotal = **dCurrentPets;

    // display guidelines for importing multiple pets
    printf("\n%s\n%s\n%s\n%s\n\n%s\n%s\n%s\n%s\n\n%s",
    "IMPORTING MULTIPLE PETS (MAX OF 44 PETS)",
    "MAX OF 10 FILES IN IMPORT_PETS FOLDER",
    "File name must be less than 36 characters long.",
    "Please make sure your pets follows the template:",
    "Pet Name",
    "Affinity",
    "Pet Description",
    "0",
    "You can check competdium.txt for reference.");
    
    /*for(int i=0; i<3; i++){
        printf("%s\n", txtfiles[i]);
    }*/
    do{
        // list down files in import_pets folder
        printf("\nTXT FILES IN IMPORT_PETS\n");
        listTxtFiles("./import_pets", txtfiles);
        printf("[0] Exit\n");    
        printf("\nWhich file do you want to import?\n");
        
        scanf(" %d", &dChoice);
    
        if (dChoice!=0)
        {
            strcpy(filename, "import_pets/");
            strcat(filename, txtfiles[dChoice-1]); //add "import_pets/" to .txt
            initializePets(addPets);
            dTotalAddPets = getComPetDium(addPets, filename); //get pets inside txt file
            viewBattlepets(addPets, dTotalAddPets); //display battlepets inside txt file
            
            do{
            printf("Would you like to add these pets? [y/n] \n");
                scanf(" %c", &cConfirm); //confirm selection
                    //check if user responded y or n
                    switch(cConfirm){
                        case 'y':
                            //check if competdium is past max amount
                            dPetMaxCheck = checkIfPetMax(pet, *dCurrentPets, dTotalAddPets);
                            if (dPetMaxCheck == 0) {
                                printf("You have reached the maximum number of BattlePets.\n");
                            } else {
                                printf("Adding pets...\n");
                                **dCurrentPets = addMultiplePetsDetails(pet, addPets, dPetTotal, dTotalAddPets); 
                                //add pets and update pet total    
                                printf("Successfully added BattlePet/s.\n");
                            }
                            break;
                        case 'n':
                            printf("Please choose the file that you want to import\n");
                            break;
                        default:
                            printf("Invalid response. Please try again.\n");
                            break;
                    }
            } while(cConfirm!='y' && cConfirm!='n');

        } else if (dChoice==0){
            printf("Exiting BattlePet addition...");
        } else{
            printf("Invalid input. Please try again.");
        }
    } while (dChoice!=0 && cConfirm!='y');
}

/**
 * This function saves the current player's roster to a file.
 * @param string filename - the name of the file to save the roster
 * @param struct Player* currentPlayer - the current player whose roster is being saved
 * @return void
 */
void saveRosterToFile(string filename, struct Player* currentPlayer) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create or open the file '%s'.\n", filename);
        return;
    }

    for (int x = 0; x < MAX_ROSTER; x++) {
        fprintf(file, "%s\n", currentPlayer->pet[x].name);
    }

    fclose(file);
    printf("Roster saved successfully to '%s'.\n", filename);
}