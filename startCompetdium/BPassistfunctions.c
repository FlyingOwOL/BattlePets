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