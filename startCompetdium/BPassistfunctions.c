/**
* Description : This file contains the functions that are used for computations and to aid the BPmainfunctions
*
* Author/s : Sy, Jason Mark Lester B. 
*            Enerio, Gabrielle G.      
* Section : S19B
* Last Modified : March 31, 2025
*/

#include <stdio.h>
#include "../BPheaders.h"

/**
 * This function edits a BattlePet's name and asks the user what they want
 * to replace it with. Returns 1 if successful, returns 0 if not
 * @param struct BattlePet* pet - the BattlePet struct to be modified
 * @return int - 1 if successful, 0 if not
 */
int
editBPname (struct BattlePet* pet){
    int dResult;
    char cValid;
    dResult = 0;

    do
    { // input pet name loop
        printf("Input BattlePet Name (MAX 35 CHARACTERS): ");
        scanf(" %35s", pet->name);
        while (getchar() != '\n'); // clear buffer
            
        if (strlen(pet->name) <= 35){ // ensure it fits string limit
            do
            {
            printf("\n Is your BattlePet's name '%s'? [y/n]", pet->name);
            scanf(" %c", &cValid);
                switch (cValid){
                    case 'y': // can now exit pet name loop
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
 * This function edits a BattlePet's affinity and asks the user what they want
 * to replace it with. Returns 1 if successful, returns 0 if not
 * @param struct BattlePet* pet - the BattlePet struct to be modified
 * @return int - 1 if successful, 0 if not
 */
int
editBPaffinity (struct BattlePet* pet){
    int dChoice, dResult;
    char cValid;
    string affinity[] = {"Fire", "Water", "Grass", "Earth", "Air", "Electric", "Ice", "Metal"};
    dResult = 0;
    
    printf("\n BATTLEPET AFFINITY\n");
    for (int i=0; i<8; i++){ // display affinities
        printf("[%d] %s\n", i+1, affinity[i]);
    }
    
    do
    { // input pet affinity loop
     //check if affinity is valid
        printf("Choose your BattlePet's affinity:");
        scanf(" %d", &dChoice);

        if(dChoice>0 && dChoice<9){
            do{ // confirmation loop
                if(strcmp(pet->affinity, affinity[dChoice-1])==0){ 
                    // notifies the player that they chose the same affinity as their pet
                    printf("This is already your BattlePet's affinity.\n");
                    printf("Would you like to keep it? [y/n] \n");
                } else {
                printf("\n Is your BattlePet's affinity '%s'? [y/n]", affinity[dChoice-1]);
                }
                scanf(" %c", &cValid);

                switch (cValid){
                    case 'y': // can now leave affinity loop and confirmation loop
                        strcpy(pet->affinity, affinity[dChoice-1]); // change pet's affinity to the chosen one
                        if(strcmp(pet->affinity, affinity[dChoice-1])==0){
                            printf("%s BattlePet affinity retained.\n", pet->affinity);
                        } else {
                            printf("BattlePet affinity is successfully changed to '%s'.\n", pet->affinity);
                        }

                        dResult = 1; // successful execution
                        break;
                    case 'n': // only leave confirmation loop
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
 * This function edits a BattlePet's description and asks the user what they want
 * to replace it with. Returns 1 if successful, returns 0 if not
 * @param struct BattlePet* pet - the BattlePet struct to be modified
 * @return int - 1 if successful, 0 if not
 */
int
editBPdesc (struct BattlePet* pet){
    int dResult;
    char cValid;
    dResult=0;

    do
    { // input pet description loop
        printf("Input BattlePet Description (MAX 239 CHARACTERS): ");

        scanf(" %239[^\n]", pet->description);
        while (getchar() != '\n'); // clear buffer
            
        if (strlen(pet->description) <= MAX_DESCRIPTION-1){ // ensure it fits max description limit
            do
            { //confirmation loop
            printf(" %s\n", pet->description); // display new description
            printf("Is this the description of your BattlePet? [y/n]");
            scanf(" %c", &cValid);
                switch (cValid){
                    case 'y': // can now exit pet description loop
                        printf("BattlePet description is successfully changed.\n");
                        dResult = 1;
                        break;
                    case 'n': // only leave confirmation loop
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

    //delete in competdium.txt
    updateCompetdiumTxt(pet, dPetTotal);
}

/**
 * This function checks if the number of BattlePets to be added will make the ComPetDium
 * reach its max amount. If it does, it asks the user if they want to be redirected to
 * the delete menu to remove a pet.
 * 
 * @param struct BattlePet pet[] - the array of pets
 * @param int* dCurrentPets - pointer to the current total of battlepets
 * @param int dPetsToAdd - the number of pets to be added
 * @return int - 1 if it doesn't reach pet max, 0 if it does
 */
int checkIfPetMax(struct BattlePet pet[], int* dCurrentPets, int dPetsToAdd) {
    char cConfirm;
    int dNewTotal = *dCurrentPets + dPetsToAdd; // total pets after addition
    int petsToRemove = dNewTotal - MAX_BATTLEPETS; // pets to remove to fit max
    int dResult = 0; // default to not continuing

    if(dNewTotal > MAX_BATTLEPETS) {
    printf("Adding %d pets will exceed the maximum limit of %d.\n", dPetsToAdd, MAX_BATTLEPETS);
        printf("You need to remove %d pets to continue.\n", petsToRemove);
    printf("Please delete a BattlePet before adding a new one.\n");
    printf("Would you like to be redirected to the delete menu? [y/n] \n");
    do
    {
        scanf(" %c", &cConfirm);
        switch (cConfirm){
            case 'y':
                printf("You have reached the maximum number of BattlePets.\n");
                printf("Exiting BattlePet addition...");
                deleteBattlepet(pet, dCurrentPets); // redirected to delete menu
                break;
            case 'n':
                break;
            default:
                printf("Invalid response. Please try again.\n");
                break;
        }
    } while(cConfirm!='y' && cConfirm!='n');
    } else {
        dResult=1; // user may continue adding pets
    }

    return dResult;
}

/**
 * This function is used to add one pet manually to competdium.txt and to the BattlePets array
 * Returns updated pet total
 * @param struct BattlePet pet[] - the array of pets
 * @param struct BattlePet addPet - the struct of the battlepet to be added
 * @param int dCurrentPets - current total of pets
 * @return int - updated pet total
 */
int
addOnePetDetails (struct BattlePet pet[], struct BattlePet addPet, int dCurrentPets){
        // add to competdium.txt
        FILE *cpdfile = fopen ("competdium.txt", "a"); //open file in append mode
        if (cpdfile == NULL){
            printf("competdium.txt not found");
        } 
        //update competdium txt file
        fprintf(cpdfile, "%s\n%s\n%s\n%d\n\n", addPet.name, addPet.affinity, addPet.description, 0);
        fclose(cpdfile);
    
        // add to battlepets array
        strcpy(pet[dCurrentPets].name, addPet.name);
        strcpy(pet[dCurrentPets].affinity, addPet.affinity);
        strcpy(pet[dCurrentPets].description, addPet.description);
        pet[dCurrentPets].matchCount = 0;
        
        return ++dCurrentPets; //update pet total
}

/**
 * This function adds multiple pets from a struct BattlePet array to the main
 * Battlepets array and to the competdium.txt
 * Returns updated pet total
 * @param struct BattlePet pet[] - the array of pets
 * @param struct BattlePet addPets[] - the array of the pets to be added
 * @param int dCurrentPets - current total of pets
 * @param int dTotalAddPets - total amount of pets to be added
 * @return int - updated pet total
 */
int
addMultiplePetsDetails (struct BattlePet pet[], struct BattlePet addPets[], 
                        int dCurrentPets, int dTotalAddPets){
    
    int i;

    FILE *cpdfile = fopen ("competdium.txt", "a"); //open file in append mode
    if (cpdfile == NULL){
        printf("competdium.txt not found");
    } else{

    for(i=0; i<dTotalAddPets; i++){ //update competdium txt file
    fprintf(cpdfile, "%s\n%s\n%s\n%d\n\n", addPets[i].name, addPets[i].affinity, addPets[i].description, 0);
    }
    fclose(cpdfile); // close file
    
    // add to battlepets array
    for(i=0; i<dTotalAddPets; i++){
    strcpy(pet[dCurrentPets].name, addPets[i].name);
    strcpy(pet[dCurrentPets].affinity, addPets[i].affinity);
    strcpy(pet[dCurrentPets].description, addPets[i].description);
    pet[dCurrentPets].matchCount = 0; // automatically set matchCount to 0
    dCurrentPets++;
        }
    }

    return dCurrentPets; //update pet total
}


/**
 * This function aids the user in creating one BattlePet and
 * adding it manually to competdium.txt and to the BattlePets array
 * @param struct BattlePet pet[] - the array of battlepets
 * @param int** dCurrentPets - current total of battlepets
 * @return void
 */
void
addOnePet (struct BattlePet pet[], int** dCurrentPets){
    struct BattlePet addPet;
    int status[3] = {0,0,0}; // status of all 3 edits
    int dFinalCheck, dScanValid, dPetMaxCheck;

    //check if max_battlepets is reached
    dPetMaxCheck = checkIfPetMax(pet, *dCurrentPets, 1);
    
    if (dPetMaxCheck) { // check if max_battlepets is not reached
    do { // user can restart creation process
        
        //edit name
        status[0]=editBPname(&addPet);
        //edit affinity
        status[1]=editBPaffinity(&addPet);
        //edit description
        status[2]=editBPdesc(&addPet);
        
        if(status[0]==1 && status[1]==1 && status[2]==1){
            // commence final check of pet details when all edits are successful
            //recheck pet details
            printf("\nADD BATTLEPET\n");
            printf("BattlePet Name: %s\n", addPet.name);
            printf("Affinity: %s\n", addPet.affinity);
            printf("Description:\n");
            /////////////////////////////////////////////////// PUT PRINTFORMAT FUNCTION HERE
            printf("%s\n", addPet.description);

            do { // confirmation loop
                printf("\n Are the details of your BattlePet correct?\n");
                printf("[1] Yes. Add it to the ComPetdium \n");
                printf("[2] No. Restart pet creation \n");
                printf("[0] Exit. Pet will not be added to the ComPetdium \n");
                dScanValid = scanf(" %d", &dFinalCheck);
                while (getchar() != '\n'); // clear buffer

                if (dScanValid){
                    switch(dFinalCheck){
                        case 1: // can exit pet creation loop
                            **dCurrentPets = addOnePetDetails(pet, addPet, **dCurrentPets);
                            printf("\nPet has been added to the ComPetdium.");
                            dScanValid--;
                            break;
                        case 2: 
                            printf("\nRestarting pet creation.");
                            dScanValid--;
                            break;
                        case 0: // can exit pet creation loop
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
            } while(dScanValid); // loop until valid response or exit
        } 
    } while(dFinalCheck!=1 && dFinalCheck!=0);
    }
}

/**
 * This function aids the user in adding multiple pets at once 
 * by selecting a file in the import_pets folder
 * @param struct BattlePet pet[] - the array of pets
 * @param int** dCurrentPets - current total of pets
 * @return void
 */
void
addMultiplePets(struct BattlePet pet[], int** dCurrentPets){
    int dChoice, dTotalAddPets, dPetMaxCheck;
    char cConfirm;
    struct BattlePet addPets[MAX_BATTLEPETS];
    string150 txtfiles[10];
    string150 filename;

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

    do
    { // import loop, exit after importing or if user chooses to exit
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
            
            if(dTotalAddPets>=44){ // not allowed to edit initial battlepets
                printf("You have reached the maximum number of BattlePets to add in one file.\n");
                printf("Exiting BattlePet addition...");
                break;
            } else if (dTotalAddPets==0){ // check if file is empty
                printf("No pets found in '%s'.\n", filename);
                break;
            } else if (dTotalAddPets>0 && dTotalAddPets<44){
                printf("You have selected %d pets to be added.\n", dTotalAddPets);
                    do{
                    printf("Would you like to add these pets? [y/n] \n");
                        scanf(" %c", &cConfirm); //confirm selection
                            //check if user responded y or n
                            switch(cConfirm){
                                case 'y': // can exit import loop
                                    //check if competdium is past max amount
                                    dPetMaxCheck = checkIfPetMax(pet, *dCurrentPets, dTotalAddPets);
                                    if (dPetMaxCheck) {
                                        printf("Adding pets...\n");
                                        **dCurrentPets = addMultiplePetsDetails(pet, addPets, **dCurrentPets, dTotalAddPets); 
                                        //add pets and update pet total    
                                        printf("Successfully added BattlePet/s.\n");
                                    }
                                    break;
                                case 'n': // can exit import loop
                                    printf("Please choose the file that you want to import\n");
                                    break;
                                default:
                                    printf("Invalid response. Please try again.\n");
                                    break;
                            }
                    } while(cConfirm!='y' && cConfirm!='n');
            }
        } else if (dChoice==0){
            printf("Exiting BattlePet addition...");
        } else{
            printf("Invalid input. Please try again.");
        }
    } while (dChoice!=0 && cConfirm!='y');
}

