#include <stdio.h>
#include "BPheaders.h"
#include "BPfunctions.c"
#include "BPdesigns.c"

int main(){
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