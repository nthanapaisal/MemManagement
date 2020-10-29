#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "part2.h"

//pagetable.c will manage the page table for the process.
void managePage(struct Page *pageTable,long pageNum,int fetch, int iRef){
    pageTable[pageNum].valid = VALID;
    pageTable[pageNum].value = fetch;
    pageTable[pageNum].reference = iRef;
}

int resetRef(struct Page *pageTable,int frameTable[],int min,int pageSize){
    //get location in frameTable on the one we have free
    //find smallest reference than get the location on pageT also save location in FrameT
    int i;
    int location = 0;
    int locationInFrame = -1;
    for(i = 0; i < pageSize; i++){
        if(pageTable[i].valid == VALID){
            //look for smallest referece value out of 8
            if(pageTable[i].reference < min){
                min = pageTable[i].reference;
                location = i;
            }
            
        }     
    }
    
    //got the min and location then reset
    locationInFrame = pageTable[location].value;
    //free frame
    frameTable[locationInFrame] = 0;
    pageTable[location].valid = INVALID;
    pageTable[location].value = -1;
    pageTable[location].reference = -1;
    
    return locationInFrame;
    
}