#ifndef BPHEADERS
    #include <string.h>
    #define BPHEADERS
    #define NAME 36
    #define MAX_PLAYERS 50
    #define MAX_DESCRIPTION 240
    #define MAX_BATTLEPETS 60
    #define MAX_ROSTER 9


    /**
     * This typedef represents a string of 36 characters
     */
    typedef char string[NAME];

    /**
     * This struct represents a battlepet
     */
    struct BattlePet {
        string name;
        string affinity;
        char description[MAX_DESCRIPTION];
        int matchCount;
    };

    /**
     *  This struct represents a player in the game
     */
    struct Player {
        string name;
        string savedPassword;
        int wins;
        int loss;
        int draws;
        struct BattlePet pet[MAX_ROSTER]; //a player can only have 9 pets
    };

    /**
     * 
     */
    struct Results {
        char result [MAX_ROSTER];
    };

    
    void initializePlayers (struct Player player[]);
    void initializePets    (struct BattlePet pet[]);
    int  getComPetDium     (struct BattlePet pet[]);
    int  getPlayers        (struct Player player[]);

    void startBattle       (struct BattlePet pet[], 
                            struct Player player[],
                            struct Results matchResults,
                            int*, int);
    void displayRoster     (struct BattlePet roster[]);
    void displayChoices    (struct Player player[], int*);
    void newPlayer         (struct Player player[],int*);
    void selectPlayer      (struct BattlePet pet[] ,
                            struct Player player[],
                            struct Player *currentPlayer, 
                            int, int*, int);
    void selectPets        (struct BattlePet pet[],
                            struct Player *currentPlayer, int);                            

        
    void startComPetDium   (struct BattlePet pet[], int*);
    void viewBattlepets    (struct BattlePet pet[]);

    void viewStatistics    ();
    

#endif