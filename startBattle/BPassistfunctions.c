/**
* Description : This file contains the functions that are used for computations needed 
                to aid BPfunctions and startBattle
*
* Author/s : Sy, Jason Mark Lester B. 
*            Enerio, Gabrielle G.      
* Section : S19B
* Last Modified : March 31, 2025
*/

#include <stdio.h>
#include "../BPheaders.h"
#include "../Filemanips.c"

/**
 * This function searches for the pets used by the players and updates their match count 
 * @param struct BattlePet pet[] - contains all battlepets in the game
 * @param struct Player playerPets - is the current player
 * @param int dCurrentPets - is the total current pets
 * @return void
 */
void updatePetscount (struct BattlePet pet[], struct Player playerPets, int dCurrentPets)
{
    int x, y;
    for (x = 0; x < dCurrentPets; x++){ // loops through the pets in the game
        for (y = 0; y < MAX_ROSTER; y++){ // loops through the pets in the player's roster
            if (strcmp(playerPets.pet[y].name, pet[x].name) == 0){
                pet[x].matchCount++; 
            }
        }
    }
}

/**
 * This functions displays the choices for player selection the user can choose from
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
        for (x = 0; x < *dCurrentPlayers; x++){ // loops through the players
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
    printf ("Match Roster\n");   //shows the current location of the pets
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
 * @param struct Player* currentPlayer - the current player
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
    while(y < MAX_ROSTER)
    { // loop until roster is full 
        isChosen = 0;
        printf("Match Roster\n");
        if (currentPlayer->pet[y].name[0] == '\0') {
            strcpy(currentPlayer->pet[y].name, "?"); // replace empty slots with "?"
        }        
        for (x = 0; x < MAX_ROSTER; x++) { // loop through the player's pets
            if (x % 3 == 0) printf("\n");
                printf(" <%s>", currentPlayer->pet[x].name);
        }
        printf("\n");

        printf("ComPetDium\n");
        for (x = 0; x < dCurrentPets; x++) { // loop through the pets in the game
            printf("%d. %s\n", x + 1, pet[x].name);
        }

        printf("Your choice: ");
        scanf("%d", &dChoice);  
        for (x = 0; x < MAX_ROSTER; x++) { // loop through the player's pets
            if (dChoice == savedChoices[x]) { // check if the pet is already chosen
                printf("Pet already chosen\n");
                isChosen = 1;
            }
        }
        if (dChoice > 0 && 
            dChoice <= dCurrentPets &&
            !isChosen) 
            { // check if the choice is valid
            currentPlayer->pet[y] = pet[dChoice - 1]; // copy the pet to the player's roster
            savedChoices[y] = dChoice; // remember chosen pet
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
    string150 txtFilename;
    printf ("Enter your name: ");
    scanf ("%s", player[*dCurrentPlayers].name);
    printf ("Create your password: ");
    scanf ("%s", player[*dCurrentPlayers].savedPassword);
    getTxtname (player[*dCurrentPlayers].name, txtFilename, "saved_roster/");

    FILE *file = fopen (txtFilename, "w"); //create new txt file in saved_roster folder

    fclose (file); // close new roster file

    FILE *playerFile = fopen ("players.txt", "a");  //adds the player to players.txt with 0 0 0 W/L/D
        fprintf (playerFile, "\n\n%s\n", player[*dCurrentPlayers].name);
        fprintf (playerFile, "%s\n", player[*dCurrentPlayers].savedPassword);
        fprintf (playerFile, "%d\n%d\n%d", 0, 0, 0);
    fclose (playerFile); // close players.txt

    (*dCurrentPlayers)++;    
}

/**
 * This function goes through the saved_roster folder and loads the saved player roster txt file
 * @param string name - the name of the player
 * @param struct BattlePet pet[] - the array of battlepets
 * @param struct Player* currentPlayer - the current player
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
    string150 filename;
    getTxtname (name, filename, "saved_roster/");
    //ex. saved_roster/_Chainsmoker_.txt
    FILE *file = fopen (filename, "r"); //open the file in read mode
    if (file == NULL){
        printf ("File not found\n");
    } else{
        for (x = 0; x < MAX_ROSTER; x++){ //scans pet names from the file
            fscanf(file, "%s" ,currentPlayer->pet[x].name);
        }
        fclose (file); // close file
    }
    
    for (x = 0; x < MAX_ROSTER; x++){           //Loops through the 9 pets
        for (int y = 0; y < dCurrentPets; y++){ //loops through all the current battlepets
            if (strcmp (currentPlayer->pet[x].name, pet[y].name) == 0){ 
                currentPlayer->pet[x] = pet[y];  //copies the battlepet struct details to the player's roster
            }
        }
    }
}

/**
 * This function selects a player from struct player array and sets it as the current player if their password is correct
 * @param struct BattlePet pet[] - the array of pets
 * @param struct Player player[] - the array of players
 * @param struct Player *currentPlayer - the current player
 * @param int dChoice - the choice of the player
 * @param int* isDone - player 1 or player 2
 * @param int dCurrentPets - the number of current pets
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

    if (strcmp (password, player[dChoice].savedPassword) == 0) { //// check if password is correct
        *currentPlayer = player[dChoice];
        printf ("Welcome %s\n", player[dChoice].name);
        do 
        { // roster loop
            printf ("Player %d Current ", *isDone + 1);
            loadSavedRoster (player[dChoice].name, pet, currentPlayer, dCurrentPets);

            displayRoster (currentPlayer->pet);
            printf("%s\n%s\n%s",
                "[1] Load saved roster",
                "[2] Create roster for this match",
                "Your choice: ");
            scanf ("%d", &dSelect); 
            if (dSelect == 1 && currentPlayer->pet[0].name[0] == '\0') {  // check if roster is empty
                // exits roster loop
                printf ("No saved roster\n");
            } else if (dSelect == 1) {
                // exits roster loop
                printf ("Loaded saved_roster/%s.txt\n", player[dChoice].name);
            } else if (dSelect == 2) {
                //exits roster loop
                selectPets (pet, currentPlayer, dCurrentPets); // select pets for roster
            } else {
                printf ("Invalid input\n");
            }
        } while ((dSelect != 1 || currentPlayer->pet[0].name[0] == '\0') && dSelect != 2); 
        (*isDone)++;
    } else {
        printf ("Incorrect password.\n");
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
    // define element order mapping
    string elements[] = {"Fire", "Water", "Grass", "Earth", "Air", "Electric", "Ice", "Metal"};
    
    // define the matchup table
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

    char cResult, checkTable;
    int p1Index = -1, p2Index = -1;
    int i;

    // find index of Player1 and Player2 in elements array
    for (i = 0; i < 8; i++) {
        if (strcmp(Player1, elements[i]) == 0) p1Index = i;
        if (strcmp(Player2, elements[i]) == 0) p2Index = i;
    }

    // return 'E' if invalid inputs
    if (p1Index == -1 || p2Index == -1) cResult = 'E';

    // get the result from the table
    checkTable = matchup[p1Index][p2Index];
    cResult = (checkTable == 'W') ? '1' : (checkTable == 'L') ? '2' : 'D'; // 'W' = player1 wins, 'L' = player2 wins, 'D' = draw
    return cResult;
}

/**
 * This function is responsible for matching up the two players' pets
 * @param struct Player player1 - the first player
 * @param struct Player player2 - the second player
 * @return struct Results matchResult - the result of the match
 */
struct Results 
computeBattle (struct Player player1, 
               struct Player player2)
{
    struct Results matchResult;
    int x;
    for (x = 0; x < MAX_ROSTER; x++){ // loops through the pets
        matchResult.result[x] = determineWinner(player1.pet[x].affinity, player2.pet[x].affinity); // documents the result of the match
    }
    return matchResult;
}

/**
 * This function displays the match between the pets of the two players and
 * determines the winner of the match
 * @param struct Player* player1 - the first player
 * @param struct Player* player2 - the second player
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
    for (x = 0; x < MAX_ROSTER; x++){ // loops through the pets
        matchResult = determineWinner(player1->pet[x].affinity, player2->pet[x].affinity); // determines the winner of the match
        if (matchResult == '1'){
            dFirst++;
        } else if (matchResult == '2'){
            dSecond++;
        } 
        // prints the match result
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
    for (x = 0; x < MAX_ROSTER; x++){ // loops through the results
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
 * @return 1 if there is a tic-tac-toe winning pattern and 0 if not
 */
int 
checkLuckywin(struct Results matchResult, 
              int* dWinner) 
{
    int isLucky = 0;
    int invalidWin = 0;
    char grid[MAX_ROSTER];
    int x;
    for (x = 0; x < MAX_ROSTER; x++){ // stores the results in a grid
        grid[x] = matchResult.result[x];
    }
    // check rows
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

    // check columns
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

    // check diagonals
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
        strcpy(winType, "Majority Win");
    } else if (count2 > count1) {
        strcpy(winType, "Majority Win");
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
    char winType[50]; // fixed winType as char array
    char result[60 + NAME] = "Winner: ";
    int dWinner = -1;
    for (int x = 0; x < MAX_ROSTER; x++) { // loops through the results
        if (matchResult.result[x] == '1') count1++;
        if (matchResult.result[x] == '2') count2++;
        if (matchResult.result[x] == 'D') countDraw++;
    }
    if (checkLuckywin(matchResult, &dWinner)){ // check if lucky winner
        typeOfwin(matchResult, count1, count2, winType); // get type of win
        printf ("luckywinner is detected\n");
        if (dWinner == 1) { // if player 1 is the lucky winner
            strcat(result, player1->name);
            strcat(result, " (Player1) ");
            strcat(result, winType);
            // update player stats
            player1->wins++;
            player2->loss++;
        } else if (dWinner == 2) { // if player 2 is the lucky winner
            strcat(result, player2->name);
            strcat(result, " (Player2) ");
            strcat(result, winType);
            // update player stats
            player2->wins++;
            player1->loss++;
        }
    } else if (count1 > count2) { // if player 1 wins is greater than player 2 wins
        strcat(result, player1->name);
        strcat(result, " (Player1) ");
        typeOfwin(matchResult, count1, count2, winType); // get type of win
        strcat(result, winType);
        // update player stats
        player1->wins++;
        player2->loss++;
    } else if (count2 > count1) { // if player 2 wins is greater than player 1 wins
        strcat(result, player2->name);
        strcat(result, " (Player2) ");
        typeOfwin(matchResult, count1, count2, winType); // get type of win
        strcat(result, winType);
        // update player stats
        player2->wins++;
        player1->loss++;
    } else { // if there is a draw
        strcpy(result, "Draw: no winner");
        // update player stats
        player1->draws++;
        player2->draws++;
    }
    strcpy(cWinner, result);
}

/**
 * This creates a new txt file which contains the previous match result
 * @param struct Player player1 - contains player1 info
 * @param struct Player player2 - contains player2 info
 * @param struct Results matchResult - contains the match result after a battle
 * @return void
 */
void createMatchHistory (struct Player player1, struct Player player2, struct Results matchResult)
{
    int dCurrentMatch = 1;
    int isFound = 1;
    string150 txtFilename;
    char strNumber[NAME];

    while (isFound){    //should return the index for the match result
        if (dCurrentMatch > 100) dCurrentMatch = 1; //reset back to 1 and start forgetting

        sprintf (strNumber, "%d", dCurrentMatch);   //convert int to string
        getTxtname (strNumber, txtFilename, "results/match_");  //get file name ex "results/match_0.txt"
        FILE *file = fopen (txtFilename, "r");
        if (file == NULL){      //if file is not found end loop
            isFound = 0;
        } else {
            fclose (file);            
            dCurrentMatch++;
        }
    }

    if (dCurrentMatch == 50) {  //delete first 50 files
        int x;
        for (x = 1; x <= 50; x++) {
            string150 oldFile;
            sprintf(strNumber, "%d", x);
            getTxtname(strNumber, oldFile, "results/match_");
            remove(oldFile);
        }
    }

    int count1 = 0, 
        count2 = 0, 
        countDraw = 0;
    char cWinner[50];
    string winType;
    int x;
    for (x = 0; x < MAX_ROSTER; x++) {
        if (matchResult.result[x] == '1') count1++;
        if (matchResult.result[x] == '2') count2++;
        if (matchResult.result[x] == 'D') countDraw++;
    }
    typeOfwin (matchResult, count1, count2, winType); 
    returnWinner (matchResult, &player1, &player2, cWinner);
    char winner[NAME + 20];
    winner[0] = '\0';
    int dSpaceCount = 0;
    for (x = 0; dSpaceCount < 2 && x < 40; x++){
        winner[x] = cWinner[x];
        if (cWinner[x] == ' '){
            dSpaceCount++;
        }
        if (dSpaceCount == 2){
            winner[x + 1] = '\0';
        } 
    }

    FILE *match = fopen (txtFilename, "w");
    if (match == NULL){
        printf ("Error opening file\n");
    } else {
        fprintf (match, "Player1: %s\n", player1.name);
        fprintf (match, "Player2: %s\n\n", player2.name);
        fprintf (match, "P1 Roster vs P2 Roster\n");
        for (x = 0; x < MAX_ROSTER; x++){
            fprintf (match, "%s vs %s\n", player1.pet[x].name, player2.pet[x].name);
        }
        fprintf (match, "\n");
        fprintf (match, "Match Results\n");
        for (x = 0; x < MAX_ROSTER; x++){
            if (x > 0 && x % 3 == 0){
                fprintf (match, "\n");
            }
            fprintf (match, "%c ", matchResult.result[x]);
        }
        fprintf (match, "\n\n");
        fprintf (match, "%s\n", winner);
        fprintf (match, "Type of Win: %s\n", winType);
        fclose (match);
    }
}
