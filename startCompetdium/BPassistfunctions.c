/*
    This file contains the functions that are used for computations and to aid the BPfunctions
*/
#include <stdio.h>
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
        printf("\n Are the details of your BattlePet correct? [y/n]\n");
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
        // add to competdium.txt
        FILE *cpdfile = fopen ("competdium.txt", "a");
        if (cpdfile == NULL){
            printf("competdium.txt not found");
        }
        fprintf(cpdfile, "\n\n%s\n%s\n%s\n%d", addPet.name, addPet.affinity, addPet.description, 0);
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
 * a file in the directory
 */
void
addMultiplePets(){
    
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
    printf("Add one manually or multiple from importpets folder?\n");
    printf("[1] Add one manually \n");
    printf("[2] Add multiple from folder\n");
    printf("[0] Exit\n"); // add one or multiple?
    scanf (" %d", &dChoice);
    switch(dChoice)
        {
        case 1:
           addOnePet(pet, &dCurrentPets);
           break;
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
 * This function is used to edit the details of an existing pet in competdium.txt
 */
void
editBattlepet (){

}

/**
 * This function is used to edit the details of an existing pet in competdium.txt
 */
void
deleteBattlepet (){

}

/**
 * This function is used to create and save a 3x3 Battlepet roster for a player
 */
void
saveRoster (){

}
