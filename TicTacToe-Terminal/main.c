#include "common.h"
#include "multiplayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main ()
{
    int decision; 
    Data *game = (Data *)calloc(1, sizeof(Data)); 

    srand(time(NULL)); //to use rand() and get new random numbers

    do
    {
        startUi(); //Simple UI
        decision = getOp(); //Get option

        switchMode(&decision, game); //start selected option

    } while(decision != 4); //loop to be able to play again

    free(game); //Clean memory

    return 0;
}