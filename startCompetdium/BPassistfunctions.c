/*
    This file contains the functions that are used for computations and to aid the BPfunctions
*/
#include <stdio.h>
#include <dirent.h>
#include "../BPheaders.h"

/**
 * This function is used to view the pets saved in the battlepets array
 * @param struct BattlePet pet[] - the array of pets
 * @return void
 */
void 
viewBattlepets (struct BattlePet pet[])
{
    int x;
    for (x = 0; x < MAX_BATTLEPETS; x++){   //loop through the array of battlepets
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
 * This function edits a battlepet's name and asks the user what they want
 * to replace it with. Returns 1 if successful, returns 0 if not
 * @param struct BattlePet pet - the BattlePet struct to be modified
 */
int
editBPname (struct BattlePet* pet){
    int dChoice, dResult, dScanValid;
    char cValid;
    do
    { // check if name is valid
        printf("Input BattlePet Name (MAX 35 CHARACTERS): ");
        dScanValid=scanf(" %35s", &pet->name);
        while (getchar() != '\n'); // clear buffer
            
        if(dScanValid){
            do
            {
            printf("\n Is your BattlePet's name '%s'? [y/n]", pet->name);
            scanf(" %c", &cValid);
            while (getchar() != '\n'); // clear buffer
                if(cValid=='y' || cValid=='n'){ //check if user responded y or n
                    dScanValid=0;
                } else{
                    printf("\n Invalid response. Please try again.");
                } 
            } while(dScanValid);
        } else{
            printf("Invalid input. Please try again.\n");
        }
    } while(cValid!='y');        

    // output result
    if(cValid=='y'){
        dResult = 1;
    } else{
        dResult = 0;
    }
    return dResult;
}

/**
 * This function edits a battlepet's affinity and asks the user what they want
 * to replace it with. Returns 1 if successful, returns 0 if not
 * @param struct BattlePet pet - the BattlePet struct to be modified
 */
int
editBPaffinity (struct BattlePet* pet){
    int dChoice, dScanValid, dResult;
    char cValid;
    string affinity[] = {"Fire", "Water", "Grass", "Earth", "Air", "Electric", "Ice", "Metal"};

    printf("\n BATTLEPET AFFINITY\n");
    for (int i=0; i<8; i++){
        printf("[%d] %s\n", i+1, affinity[i]);
    }

    do
    { //check if affinity is valid
        printf("Choose your BattlePet's affinity:");
        dScanValid = scanf(" %d", &dChoice);
        while (getchar() != '\n'); // clear buffer

        if(dScanValid && dChoice>0 && dChoice<9){
        do
        {
        printf("\n Is your BattlePet's affinity '%s'? [y/n]", affinity[dChoice-1]);
        scanf(" %c", &cValid);
        while (getchar() != '\n'); // clear buffer
            if(cValid=='y' || cValid=='n'){ //check if user responded y or n
                strcpy(pet->affinity, affinity[dChoice-1]);
                dScanValid=0;
            } else{
                printf("\n Invalid response. Please try again.");
            } 
        } while(dScanValid);
        } 
        else{
            printf("Invalid input. Please try again.\n");
        } 
    } while (cValid!='y');

    // output result
    if(cValid=='y'){
        dResult = 1;
    } else{
        dResult = 0;
    }
    return dResult;
}

/**
 * This function edits a battlepet's description and asks the user what they want
 * to replace it with. Returns 1 if successful, returns 0 if not
 * @param struct BattlePet pet - the BattlePet struct to be modified
 */
int
editBPdesc (struct BattlePet* pet){
    int dScanValid, dResult;
    char cValid;
    
    do
    {
        printf("Input BattlePet Description (MAX 239 CHARACTERS): ");
        dScanValid=scanf(" %239[^\n]", &pet->description);
        while (getchar() != '\n'); // clear buffer

        if (dScanValid){
            do
            {
     /////////////////////////////////////////////////// PUT PRINTFORMAT FUNCTION HERE        
            printf(" %s\n", pet->description);
            printf("Is this the description of your BattlePet? [y/n]");
            scanf(" %c", &cValid);
            while (getchar() != '\n'); // clear buffer
                if(cValid=='y' || cValid=='n'){ //check if user responded y or n
                    dScanValid=0;
                } else{
                    printf("\n Invalid response. Please try again.");
                } 
            } while(dScanValid);
        } else{
            printf("Invalid input. Please try again.\n");
        }
    } while(cValid!='y');  

    // output result
    if(cValid=='y'){
        dResult = 1;
    } else{
        dResult = 0;
    }
    return dResult;
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
    viewBattlepets(pet);
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
    string filename = "competdium.txt";

    (**dCurrentPets)--; //subtract from current pets
    dPetTotal=(**dCurrentPets);

    //shift elements in struct array to overwrite pet to be deleted
    for(i=index; i<dPetTotal; i++){
        pet[i] = pet[i+1];
    }
    //clear out last index in array
    strcpy(pet[dPetTotal].name,"");
    strcpy(pet[dPetTotal].affinity,"");
    strcpy(pet[dPetTotal].description,"");
    pet[dPetTotal].matchCount = 0;

    //delete in competdium.txt
    updateCompetdiumTxt(pet, dPetTotal);

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
    viewBattlepets(pet);
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
 * This function checks if the the number of battlepets to be added will make the competdium
 * reach its max amount. If it does, removes recently added battlepets (excludes initial battlepets)
 * @param struct BattlePet pet[] - the array of pets
 *
 */
int
checkIfPetMax (struct BattlePet pet[], int** dCurrentPets){
    int dResult;

}

/**
 * This function is used to add one pet manually to competdium.txt and to the BattlePets array
 * @param struct BattlePet pet[] - the array of battlepets
 * @param int* dCurrentPets - current total of battlepets
 */
void
addOnePet (struct BattlePet pet[], int** dCurrentPets){
    int dPetTotal = **dCurrentPets;
    struct BattlePet addPet;
    int status[3] = {0,0,0};
    int dFinalCheck, dScanValid;

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
        // check if competdium is past max amount
        
        // add to competdium.txt
        FILE *cpdfile = fopen ("competdium.txt", "a");
        if (cpdfile == NULL){
            printf("competdium.txt not found");
        }
        fprintf(cpdfile, "%s\n%s\n%s\n%d\n\n", addPet.name, addPet.affinity, addPet.description, 0);
        fclose(cpdfile);
    
        // add to battlepets array
        strcpy(pet[dPetTotal].name, addPet.name);
        strcpy(pet[dPetTotal].affinity, addPet.affinity);
        strcpy(pet[dPetTotal].description, addPet.description);
        pet[dPetTotal].matchCount = 0;
        (**dCurrentPets)++;
    }        
}

/**
 * This function is used to add multiple pets at once by selecting 
 * a file in the import_pets folder
 */
void
addMultiplePets(struct BattlePet pet[], int** dCurrentPets){
    
    // display guidelines for importing multiple pets
    
    // list down files in import_pets folder

    // scan, show contents, and confirm selection (+number of battlepets to be added)

    // check if competdium is past max amount

    // 
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
 * This function is used to create and save a 3x3 Battlepet roster for a player
 */
void
saveRoster (){

}
