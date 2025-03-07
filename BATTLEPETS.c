/**
* Description : <short description of the project>
* Author/s : Sy, Jason Mark Lester B. 
*            Enerio, Gabriele G.      
* Section : S19B
* Last Modified : <date when last revision was made>
* Acknowledgments : <list of references used in the making of this project>
*/

#include <stdio.h>
#include "BPheaders.h"
#include "BPfunctions.c"
#include "BPdesigns.c"

int main(){
    struct Player player[MAX_PLAYERS];
    struct BattlePet pet[MAX_BATTLEPETS];

    initializePlayers (player); //sets the player array to default values
    initializePets (pet);       //sets the pet array to default values

    int x;
    do{
        printf("%s\n%s\n%s\n%s\n%s\n",
        "[1] Battle!",
        "[2] ComPetDium",
        "[3] View Statistics",
        "[0] Exit",
        "Your choice:");
        scanf ("%d", &x);
        switch (x){
            case 1:
                startBattle ();
                break;
            case 2:
                startComPetDium ();
                break;
            case 3:
                viewStatistics ();
                break;
            case 0:
                printf ("Thank you for playing!!\n");
                break;
            default:
                printf ("Invalid input\n");
        }
    } while(x != 0);
    return 0;
}

/**
* This is to certify that this project is my/our own work, based on my/our personal
* efforts in studying and applying the concepts learned. I/We have constructed the
* functions and their respective algorithms and corresponding code by myself/ourselves.
* The program was run, tested, and debugged by my/our own efforts. I/We further certify
* that I/we have not copied in part or whole or otherwise plagiarized the work of
* other students and/or persons.
*
* Sy, Jason Mark Lester B. (DLSU ID# 12414530)
* Enerio, Gabriele G.      (DLSU ID# <number>)
*/