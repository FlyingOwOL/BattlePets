/*
    This file contains the functions that are used for computations and to aid the BPfunctions
*/
#include <stdio.h>
#include "../BPheaders.h"
#include "../Filemanips.c"

/**
 * This function searches for the pets used by the players and updates their match count 
 * @param struct BattlePet pet[] - contains all battlepets in the game
 * @param struct Player playerPets - is the current player
 * @param int dCurrentPets - is the total current pets
 */
void updatePetscount (struct BattlePet pet[], struct Player playerPets, int dCurrentPets)
{
    int x, y;
    for (x = 0; x < dCurrentPets; x++){
        for (y = 0; y < MAX_ROSTER; y++){
            if (strcmp(playerPets.pet[y].name, pet[x].name) == 0){
                pet[x].matchCount++; 
            }
        }
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
void 
displayRoster (struct BattlePet roster[])
{
    int x;
    printf ("Match Roster\n");                      //shows the current location of the pets
        for (x = 0; x < MAX_ROSTER; x++){
            if (x > 0 && x % 3 == 0){
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
void 
newPlayer (struct Player player[],
                int* dCurrentPlayers)
{
    char txtFilename[NAME + 35];
    printf ("Enter your name: ");
    scanf ("%s", player[*dCurrentPlayers].name);
    printf ("Create your password: ");
    scanf ("%s", player[*dCurrentPlayers].savedPassword);
    getTxtname (player[*dCurrentPlayers].name, txtFilename);

    FILE *file = fopen (txtFilename, "w"); //create new txt file in saved_roster folder

    fclose (file);

    FILE *playerFile = fopen ("players.txt", "a");  //adds the player to players.txt with 0 0 0 W/L/D
        fprintf (playerFile, "\n\n%s\n", player[*dCurrentPlayers].name);
        fprintf (playerFile, "%s\n", player[*dCurrentPlayers].savedPassword);
        fprintf (playerFile, "%d\n%d\n%d", 0, 0, 0);
    fclose (playerFile);

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
loadSavedRoster (string name, 
                 struct BattlePet pet[], 
                 struct Player* currentPlayer, 
                 int dCurrentPets)
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
        *currentPlayer = player[dChoice];
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
 * This function returns the winner of the match
 * @param string Player1 - the first player's pet affinity
 * @param string Player2 - the second player's pet affinity
 * @return char - the winner of the match
 */
char 
determineWinner(string Player1, 
                string Player2) 
{
    // Define element order mapping
    string elements[] = {"Fire", "Water", "Grass", "Earth", "Air", "Electric", "Ice", "Metal"};
    
    // Define the matchup table
    char matchup[8][8] = {
        {'D', 'L', 'W', 'W', 'D', 'D', 'W', 'L'}, // Fire 
        {'W', 'D', 'L', 'D', 'D', 'L', 'L', 'W'}, // Water 
        {'L', 'W', 'D', 'L', 'L', 'D', 'W', 'D'}, // Grass 
        {'L', 'D', 'W', 'D', 'L', 'W', 'D', 'W'}, // Earth 
        {'D', 'D', 'W', 'W', 'D', 'L', 'L', 'D'}, // Air 
        {'D', 'W', 'D', 'L', 'W', 'D', 'L', 'L'}, // Electric 
        {'L', 'W', 'L', 'W', 'W', 'W', 'D', 'W'}, // Ice 
        {'W', 'L', 'D', 'L', 'D', 'W', 'L', 'D'}  // Metal 
    };

    int p1Index = -1, p2Index = -1;
    int i;
    // Find index of Player1 and Player2 in elements array
    for (i = 0; i < 8; i++) {
        if (strcmp(Player1, elements[i]) == 0) p1Index = i;
        if (strcmp(Player2, elements[i]) == 0) p2Index = i;
    }

    // Return 'E' if invalid inputs
    if (p1Index == -1 || p2Index == -1) return 'E';

    // Get the result from the table
    char result = matchup[p1Index][p2Index];
    return (result == 'W') ? '1' : (result == 'L') ? '2' : 'D';
}

/**
 * This function is responsible for matching up the two players' pets
 * @param struct Player player1 - the first player
 * @param struct Player player2 - the second player
 * @param struct Results matchResult - the result of the match
 * @return struct Results matchResult - the result of the match
 */
struct Results 
computeBattle (struct Player player1, 
               struct Player player2)
{
    struct Results matchResult;
    int x;
    for (x = 0; x < MAX_ROSTER; x++){
        matchResult.result[x] = determineWinner(player1.pet[x].affinity, player2.pet[x].affinity);
    }
    return matchResult;
}

/**
 * This function displays the match between the pets of the two players and
 * determines the winner of the match
 * @param struct Player player1 - the first player
 * @param struct Player player2 - the second player
 * @return void 
 */
void 
displayMatch (struct Player* player1,
              struct Player* player2)
{
    int dFirst = 0,
        dSecond = 0;
    char matchResult;
    int x;
    for (x = 0; x < MAX_ROSTER; x++){
        matchResult = determineWinner(player1->pet[x].affinity, player2->pet[x].affinity);
        if (matchResult == '1'){
            dFirst++;
        } else if (matchResult == '2'){
            dSecond++;
        } 
        printf ("[%d][%d] %s vs %s\n",
        dFirst, dSecond,
        player1->pet[x].name,
        player2->pet[x].name);
    }
    printf ("\n");
}

/**
 * This function displays the match results in a 3x3 grid
 * @param struct Results matchResult - the result of the match
 * @return void
 */
void 
displayResult (struct Results matchResult){
    int x;
    for (x = 0; x < MAX_ROSTER; x++){
        if (x > 0 && x % 3 == 0){
            printf ("\n");
        }        
        printf (" [%c]", matchResult.result[x]);
    }
    printf ("\n");
}


/**
 * This function returns 1 if the matchResult 3x3 has horizontal, diagonal, or vertical pattern
 * @param struct Results matchResult - struct of the results
 * @param int* dWinner - determines if player 1 or 2 is Lucky Winner
 * @return 1 if there is a tictactoe winning pattern and 0 if not
 */
int 
checkLuckywin(struct Results matchResult, 
              int* dWinner) 
{
    int isLucky = 0;
    int invalidWin = 0;
    char grid[MAX_ROSTER];
    int x;
    for (x = 0; x < MAX_ROSTER; x++){
        grid[x] = matchResult.result[x];
    }
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (grid[i] == grid[i + 1] && grid[i] == grid[i + 2]) {
            if (grid[i] == 'D') {
                invalidWin = 1; 
            } else {
                isLucky = 1;
                *dWinner = (grid[i] == '1') ? 1 : 2;
            }
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (grid[i] == grid[i + 3] && grid[i] == grid[i + 6]) {
            if (grid[i] == 'D') {
                invalidWin = 1;
            } else {
                isLucky = 1;
                *dWinner = (grid[i] == '1') ? 1 : 2;
            }
        }
    }

    // Check diagonals
    if (grid[0] == grid[4] && grid[0] == grid[8]) {
        if (grid[0] == 'D') {
            invalidWin = 1;
        } else {
            isLucky = 1;
            *dWinner = (grid[0] == '1') ? 1 : 2;
        }
    }
    if (grid[2] == grid[4] && grid[2] == grid[6]) {
        if (grid[2] == 'D') {
            invalidWin = 1;
        } else {
            isLucky = 1;
            *dWinner = (grid[2] == '1') ? 1 : 2;
        }
    }

    if (invalidWin) {
        isLucky = 0;
    }
    return isLucky;
}


/**
 * This function returns the type of win
 * @param struct Results matchResult - result
 * @param int count1 - number of wins for 1
 * @param int count2 = number of wins for 2
 * @return void
 */
void 
typeOfwin (struct Results matchResult, 
           int count1, 
           int count2, 
           string winType) 
{
    int dWinner = -1;
    if (checkLuckywin(matchResult, &dWinner)) {
        strcpy(winType, "Lucky Win");
    } else if (count1 > count2) {
        strcpy(winType, "Majority Win (Player1)");
    } else if (count2 > count1) {
        strcpy(winType, "Majority Win (Player2)");
    } else {
        strcpy(winType, "Draw");
    }
}

/**
 * This function returns the winner of the match
 * @param struct Results matchResult - contains the results of the match
 * @param struct Player player1 - is the 1st player
 * @param struct Player player2 - is the 2nd player
 * @return void
 */
void 
returnWinner(struct Results matchResult, 
             struct Player* player1, 
             struct Player* player2, 
             char cWinner[])
{
    int count1 = 0, count2 = 0, countDraw = 0;
    char winType[50]; // Fixed winType as char array
    char result[60 + NAME] = "Winner: ";
    int dWinner = -1;
    for (int x = 0; x < MAX_ROSTER; x++) {
        if (matchResult.result[x] == '1') count1++;
        if (matchResult.result[x] == '2') count2++;
        if (matchResult.result[x] == 'D') countDraw++;
    }
    if (checkLuckywin(matchResult, &dWinner)){
        typeOfwin(matchResult, count1, count2, winType);
        printf ("luckywinner is detected\n");
        if (dWinner == 1) {
            strcat(result, player1->name);
            strcat(result, " (Player1) ");
            strcat(result, winType);
            player1->wins++;
            player2->loss++;
        } else if (dWinner == 2) {
            strcat(result, player2->name);
            strcat(result, " (Player2) ");
            strcat(result, winType);
            player2->wins++;
            player1->loss++;
        }
    } else if (count1 > count2) {
        strcat(result, player1->name);
        strcat(result, " (Player1) ");
        typeOfwin(matchResult, count1, count2, winType);
        strcat(result, winType);
        player1->wins++;
        player2->loss++;
    } else if (count2 > count1) { // Fixed condition
        strcat(result, player2->name);
        strcat(result, " (Player2) ");
        typeOfwin(matchResult, count1, count2, winType);
        strcat(result, winType);
        player2->wins++;
        player1->loss++;
    } else {
        strcpy(result, "Draw: no winner");
        player1->draws++;
        player2->draws++;
    }
    strcpy(cWinner, result);
}
