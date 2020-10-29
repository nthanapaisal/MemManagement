#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "part2.h"

//phypages.c is used to manage the physical pages
// look for first freeframe

int fetchFrame(int frameTable[],int frameSize){
    int i;

    for(i = 1; i < frameSize; i++){
        //found empty
        if(frameTable[i] == 0){
            return i;
        } 

    }
    return -1;
}