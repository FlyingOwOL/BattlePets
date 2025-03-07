#ifndef BPHEADERS
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

    
    void initializePlayers (struct Player player[]);
    void initializePets (struct BattlePet pet[]);
    void startBattle ();
    void startComPetDium ();
    void viewStatistics ();
#endif