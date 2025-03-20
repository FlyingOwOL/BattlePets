/*
    This file contains the functions that are used for computations and to aid the BPfunctions
*/
#include <stdio.h>
#include "BPheaders.h"

/**
 * This function uploads the battlepets from the file ComPetDium.txt
 * @param struct BattlePet pet[] - the array of battlepets
 * @return void
 */
int 
getComPetDium (struct BattlePet pet[])
{
    int dCurrentPets = 0;
    FILE *file = fopen ("ComPetDium.txt", "r");
    if (file == NULL){
        printf ("File not found\n");
    } else{
        int x = 0;
        while (fscanf (file, "%s", pet[x].name) != EOF){  //read name
            fscanf (file, "%s", pet[x].affinity);       //read affinity
            fscanf (file, " %[^\n]", pet[x].description); //read description
            fscanf (file, "%d", &pet[x].matchCount);    //read match count
            fgetc (file);                               //eat the new line
            x++;
            dCurrentPets++;
        }
        fclose (file);
    }
    return dCurrentPets;
}

/**
 * THis function gets the players from the file Players.txt
 * @param struct Player player[] - the array of players
 * @return void
 */
int 
getPlayers (struct Player player[])
{
    int dCurrentPlayers = 0;
    FILE *file = fopen ("Players.txt", "r");
    if (file == NULL){
        printf ("File not found\n");
    } else{
        int x = 0;
        while (fscanf (file, "%s", player[x].name) != EOF){  //read name
            fscanf (file, "%s", player[x].savedPassword);       //read password
            fscanf (file, "%d", &player[x].wins);    //read wins
            fscanf (file, "%d", &player[x].loss);    //read loss
            fscanf (file, "%d", &player[x].draws);    //read draws
            fgetc (file);                               //eat the new line
            x++;
            dCurrentPlayers++;
        }
        fclose (file);
    }
    return dCurrentPlayers;
}

/** 
 * This function initializes the values of the struct player array to default values
 * @param struct Player player[] - the array of players
 * @return void
 */
void 
initializePlayers (struct Player player[])
{
    int x, y;
    for (x = 0; x < MAX_PLAYERS; x++){
        player[x].name[0] = '\0';
        player[x].savedPassword[0] = '\0';
        player[x].wins = 0;
        player[x].loss = 0;
        player[x].draws = 0;
        for (y = 0; y < MAX_ROSTER; y++){
            player[x].pet[y].name[0] = '\0';
            player[x].pet[y].affinity[0] = '\0';
            player[x].pet[y].description[0] = '\0';
            player[x].pet[y].matchCount = 0;
        }
    }
}

/**
 * This function initializes the values of the struct pet array to default values
 * @param struct BattlePet pet[] - the array of pets
 * @return void
 */
void 
initializePets (struct BattlePet pet[])
{
    int x;
    for (x = 0; x < MAX_ROSTER; x++){
        pet[x].name[0] = '\0';
        pet[x].affinity[0] = '\0';
        pet[x].description[0] = '\0';
        pet[x].matchCount = 0;
    }
}

/**
 * This functions displays the choices for the player to choose from
 * @param struct Player player[] - the array of players
 * @param int* dCurrentPlayers - the address to the number of current players
 * @return void
 */ 
void 
displayChoices (struct Player player[], 
                int* dCurrentPlayers)
{
    printf("[1] <New Player>\n");
        int x;
        for (x = 0; x < *dCurrentPlayers; x++){
            printf("[%d] %s\n", x + 2, player[x].name);
        }
        printf("[0] Exit\nYour choice: ");
}

/**
 * This function displays the roster of the player
 * @param struct BattlePet roster[] - the array of pets
 * @return void
 */
void displayRoster (struct BattlePet roster[])
{
    int x;
    printf ("Match Roster\n");                      //shows the current location of the pets
        for (x = 0; x < MAX_ROSTER; x++){
            if (x % 3 == 0){
                printf ("\n");
            }            
            printf (" <%s>", roster[x].name);
        }
        printf ("\n");
}

/**
 * This functions lets existing users select their pets for the match
 * @param struct BattlePet pet[] - the array of pets
 * @param struct Player currentPlayer - the current player
 * @param int dCurrentPets - the number of current pets
 * @return void
 */
void 
selectPets (struct BattlePet pet[],
            struct Player *currentPlayer, 
            int dCurrentPets)
{
    initializePets (currentPlayer->pet);
    int y = 0, x;
    int dChoice;
    int savedChoices [MAX_ROSTER];
    int isChosen;
    while(y < MAX_ROSTER){
        isChosen = 0;
        printf("Match Roster\n");
        if (currentPlayer->pet[y].name[0] == '\0') {
            strcpy(currentPlayer->pet[y].name, "?");
        }        
        for (x = 0; x < MAX_ROSTER; x++) {
            
            if (x % 3 == 0) printf("\n");
                printf(" <%s>", currentPlayer->pet[x].name);
        }
        printf("\n");

        printf("ComPetDium\n");
        for (x = 0; x < dCurrentPets; x++) {
            printf("%d. %s\n", x + 1, pet[x].name);
        }

        printf("Your choice: ");
        scanf("%d", &dChoice);  
        for (x = 0; x < MAX_ROSTER; x++) {
            if (dChoice == savedChoices[x]) {
                printf("Pet already chosen\n");
                isChosen = 1;
            }
        }
        if (dChoice > 0 && 
            dChoice <= dCurrentPets &&
            !isChosen) {
            currentPlayer->pet[y] = pet[dChoice - 1];
            savedChoices[y] = dChoice; 
            y++;
        } else if (!isChosen) {
            printf("Invalid input\n");
        }
    }
}


/**
 * This function creates a new player and saves it to the player array
 * @param struct Player player[] - the array of players
 * @param int* dCurrentPlayers - the address to the number of current players
 * @return void
 */
void newPlayer (struct Player player[],
                int* dCurrentPlayers)
{
    printf ("Enter your name: ");
    scanf ("%s", player[*dCurrentPlayers].name);
    printf ("Create your password: ");
    scanf ("%s", player[*dCurrentPlayers].savedPassword);
    (*dCurrentPlayers)++;
}

/**
 * This function goes through the saved_roster folder and loads the saved player roster txt file
 * @param string name - the name of the player
 * @param struct BattlePet pet[] - the array of battlepets
 * @param struct Player currentPlayer - the current player
 * @param int dCurrentPets - the number of current pets
 * @return void
 */
void 
loadSavedRoster (string name, struct BattlePet pet[], struct Player* currentPlayer, int dCurrentPets)
{
    int x;
    char filename[NAME + 20] = "saved_roster/";
    strcat(filename, name); //gets the saved player file from the saved_roster folder
    strcat(filename, ".txt");
    //ex. saved_roster/_Chainsmoker_.txt
    FILE *file = fopen (filename, "r");
    if (file == NULL){
        printf ("File not found\n");
    } else{
        for (x = 0; x < MAX_ROSTER; x++){
            fscanf(file, "%s" ,currentPlayer->pet[x].name);
        }
        fclose (file);
    }
    
    for (x = 0; x < MAX_ROSTER; x++){           //Loops through the 9 pets
        for (int y = 0; y < dCurrentPets; y++){ //loops through all the current battlepets
            if (strcmp (currentPlayer->pet[x].name, pet[y].name) == 0){ 
                currentPlayer->pet[x] = pet[y];  //copies the battlepet details to the player's roster
            }
        }
    }
}

/**
 * This function selects a player from struct player array and sets it as the current player if the password is correct
 * @param struct Player player[] - the array of players
 * @param struct Player currentPlayer - the current player
 * @param int* dChoice - the choice of the player
 * @return void
 */
void 
selectPlayer (struct BattlePet pet[], 
              struct Player player[],
              struct Player *currentPlayer, 
              int dChoice, 
              int* isDone, 
              int dCurrentPets)
{
    int dSelect; 
    string password;

    printf ("Hello! %s\n", player[dChoice].name);
    printf ("Your password: %s\n", player[dChoice].savedPassword);
    printf ("Enter your password: ");
    scanf ("%s", password);

    if (strcmp (password, player[dChoice].savedPassword) == 0) {
        printf ("Welcome %s\n", player[dChoice].name);
        do {
            printf ("Player %d Current ", *isDone + 1);
            loadSavedRoster (player[dChoice].name, pet, currentPlayer, dCurrentPets);

            displayRoster (currentPlayer->pet);
            printf("%s\n%s\n%s",
                "[1] Load saved roster",
                "[2] Create roster for this match",
                "Your choice: ");
            scanf ("%d", &dSelect); 
            if (dSelect == 1 && currentPlayer->pet[0].name[0] == '\0') {  
                printf ("No saved roster\n");
            } else if (dSelect == 1) {
                printf ("Loaded saved_roster/%s.txt\n", player[dChoice].name);
            } else if (dSelect == 2) {
                selectPets (pet, currentPlayer, dCurrentPets);      
            } else {
                printf ("Invalid input\n");
            }
        } while ((dSelect != 1 || currentPlayer->pet[0].name[0] == '\0') && dSelect != 2); 
        (*isDone)++;
    } else {
        printf ("Get out\n");
    }
}


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

        // check if affinity is valid
        printf("\n BATTLEPET AFFINITY \n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
            "[1] Fire",
            "[2] Water",
            "[3] Grass",
            "[4] Earth",
            "[5] Air",
            "[6] Electric",
            "[7] Ice",
            "[8] Metal");
        do
        {
            printf("Choose your BattlePet's affinity:");
            scanf(" %d", &dAffChoice);
            while (getchar() != '\n'); // clear buffer
            switch(dAffChoice){
                case 1:
                    strcpy(addPet.affinity,"Fire");
                    break;
                case 2:
                    strcpy(addPet.affinity,"Water");
                    break;
                case 3:
                    strcpy(addPet.affinity,"Grass");
                    break;
                case 4:
                    strcpy(addPet.affinity,"Earth");
                    break;
                case 5:
                    strcpy(addPet.affinity,"Air");
                    break;
                case 6:
                    strcpy(addPet.affinity,"Electric");
                    break;
                case 7:
                    strcpy(addPet.affinity,"Ice");
                    break;
                case 8:
                    strcpy(addPet.affinity,"Metal");
                    break;
                default:
                    printf("Invalid input. Please try again.\n");
                    break;
            }
            if(dAffChoice>0 && dAffChoice<9){
            dTempChoice=1;
            do
            {
            printf("\n Is your BattlePet's affinity '%s'? [y/n]", addPet.affinity);
            scanf(" %c", &cTempValid);
            while (getchar() != '\n'); // clear buffer
                if(cTempValid=='y' || cTempValid=='n'){ //check if user responded y or n
                    dTempChoice=0;
                } else{
                    printf("\n Invalid response. Please try again.");
                } 
            } while(dTempChoice);
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
                    printf("\nPet will be added to the ComPetdium.");
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
