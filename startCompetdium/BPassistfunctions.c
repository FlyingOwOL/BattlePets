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
 * This function is used to edit the details of an existing pet in competdium.txt 
 * and its structure in the BattlePets array
 * @param struct BattlePet pet[] - the array of pets
 * @return void
 */
void
editBattlepetDetails (struct BattlePet pet[]){

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
    // makes a temporary file, copy updated competdium with battlepet array to temp file
    FILE *cpdfile = fopen ("competdium.txt", "r");
    FILE *temp = fopen ("temp.txt", "w");

    if (cpdfile == NULL || temp == NULL){
        printf("error detected in file manipulation");
    }

    for(i=0; i<dPetTotal; i++){
        fprintf(temp, "%s\n%s\n%s\n%d\n", pet[i].name, pet[i].affinity, pet[i].description, pet[i].matchCount);
        if (i!=dPetTotal-1){
            fprintf(temp, "\n");
        }
    }
    fclose(cpdfile);
    fclose(temp);

    //replace competdium with the updated temp file
    remove("competdium.txt");
    rename("temp.txt", "competdium.txt");

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
    char cTempValid, dFinalCheck;
    int dTempChoice, dAffChoice;
    int dPetTotal = **dCurrentPets;
    struct BattlePet addPet;
    string affinity[] = {"Fire", "Water", "Grass", "Earth", "Air", "Electric", "Ice", "Metal"};

    do
    { // user can restart creation process
    do
    { // check if name is valid
        printf("Input BattlePet Name (MAX 36 CHARACTERS): ");
        scanf(" %s", &addPet.name);
        dTempChoice=1;
            do
            {
            printf("\n Is your BattlePet's name '%s'? [y/n]", addPet.name);
            scanf(" %c", &cTempValid);
            while (getchar() != '\n'); // clear buffer
                if(cTempValid=='y' || cTempValid=='n'){ //check if user responded y or n
                    dTempChoice=0;
                } else{
                    printf("\n Invalid response. Please try again.");
                } 
            } while(dTempChoice);
        } while(cTempValid!='y');
        cTempValid='n';

        //check if affinity is valid
        printf("\n BATTLEPET AFFINITY\n");
        for (int i=0; i<8; i++){
            printf("[%d] %s\n", i+1, affinity[i]);
        }

        do
        {
            printf("Choose your BattlePet's affinity:");
            dTempChoice = scanf(" %d", &dAffChoice);
            while (getchar() != '\n'); // clear buffer

            if(dTempChoice && dAffChoice>0 && dAffChoice<9){
            do
            {
            printf("\n Is your BattlePet's affinity '%s'? [y/n]", affinity[dAffChoice-1]);
            scanf(" %c", &cTempValid);
            while (getchar() != '\n'); // clear buffer
                if(cTempValid=='y' || cTempValid=='n'){ //check if user responded y or n
                    strcpy(addPet.affinity, affinity[dAffChoice-1]);
                    dTempChoice=0;
                } else{
                    printf("\n Invalid response. Please try again.");
                } 
            } while(dTempChoice);
            } 
            else{
                printf("Invalid input. Please try again.\n");
            } 
        } while (cTempValid!='y');
        cTempValid='n';

        // check if description is valid
        do
        {
            printf("Input BattlePet Description (MAX 240 CHARACTERS): ");
            scanf(" %[^\n]", &addPet.description);
            dTempChoice=1;
                do
                {
         /////////////////////////////////////////////////// PUT PRINTFORMAT FUNCTION HERE        
                printf("%s\n", addPet.description);
                printf("Is this the description of your BattlePet? [y/n]");
                scanf(" %c", &cTempValid);
                while (getchar() != '\n'); // clear buffer
                    if(cTempValid=='y' || cTempValid=='n'){ //check if user responded y or n
                        dTempChoice=0;
                    } else{
                        printf("\n Invalid response. Please try again.");
                    } 
                } while(dTempChoice);
        } while(cTempValid!='y');  
        cTempValid='n';  
    
        //recheck pet details
        printf("\nADD BATTLEPET\n");
        printf("BattlePet Name: %s\n", addPet.name);
        printf("Affinity: %s\n", addPet.affinity);
        printf("Description:\n");
        /////////////////////////////////////////////////// PUT PRINTFORMAT FUNCTION HERE
        printf("%s\n", addPet.description);

        dTempChoice=1;
        do
        {
        printf("\n Are the details of your BattlePet correct?\n");
        printf("[1] Yes. Add it to the ComPetdium \n");
        printf("[2] No. Restart pet creation \n");
        printf("[0] Exit. Pet will not be added to the ComPetdium \n");
            scanf(" %d", &dFinalCheck);
            switch(dFinalCheck){
                case 1: 
                    printf("\nPet has been added to the ComPetdium.");
                    dTempChoice--;
                    break;
                case 2: 
                    printf("\nRestarting pet creation.");
                    dTempChoice--;
                    break;
                case 0:
                    printf("\nExiting BattlePet Creation.");
                    dTempChoice--;
                    break;
                default:
                    printf("Invalid input\n");
                    break;
            }
            while (getchar() != '\n'); // clear buffer
        } while(dTempChoice);
    } while(dFinalCheck!=1 && dFinalCheck!=0);

    // copy addPet to competdium.txt and add to battlepets array
    if(dFinalCheck==1){
        // check if competdium is past max amount
        

        // add to competdium.txt
        FILE *cpdfile = fopen ("competdium.txt", "a");
        if (cpdfile == NULL){
            printf("competdium.txt not found");
        }
        fprintf(cpdfile, "\n%s\n%s\n%s\n%d\n", addPet.name, addPet.affinity, addPet.description, 0);
        fclose(cpdfile);
    
        // add to battlepets array
        strcpy(pet[dPetTotal].name,addPet.name);
        strcpy(pet[dPetTotal].affinity,addPet.affinity);
        strcpy(pet[dPetTotal].description,addPet.description);
        pet[dPetTotal].matchCount=0;
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
