// CS3733 Assignment 3, Part2.c by Supakjeera Thanapaisal
// similar to part1 but in the beginning the frame is empty and will start to fill up in sequenctial order
// if full, then choose to least recent use frame, (if the frame being access then its count as recently used)
// Algs: 1. fill up the frame 2. return frame num 3. new addy + old offset with frame num 4. else pick LRU and reset that frame and page's info 
// LRU alg: iRef is a var to keep track of LRU, continiously incrementing, each page that is VALID has one. while looking for LRU, the smallest iRef will be return. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "part2.h"

int main(int argc, char** argv) {
    
    //vars
    char *pInfile = argv[1];
    char *pOutfile = argv[2];
    char pszBuff[8];
    FILE *pFile, *pFile2;
    unsigned long addressIn;
    unsigned long pageNum;
    unsigned long pageOff;
    unsigned long addressOut;
    int fetchF;
    int pageFault = 0;
    int iRef = 0;

    //inilized structures
    struct Page pageTable[32];
    int frameTable[8];
    initialized(pageTable,frameTable,32,8);


     //check num of args
    if (argc != 3){
        printf("ERROR: Incorrect number of arguments");
        exit(101);
    }

    // open file for read and write
    pFile = fopen(pInfile, "rb");
    if(pFile == NULL){
        printf("ERROR: Unable to open input file\n");
        exit(102);
    }
    pFile2 = fopen(pOutfile, "wb");
    if(pFile2 == NULL){
        printf("ERROR: Unable to open write file\n");
        exit(103);
    }

    while(fread(pszBuff,8,1L,pFile) > 0) {
        
        //translate
        addressIn = *((unsigned long *) pszBuff);
        pageNum = addressIn >> 7;
        pageOff = (((1 << 7) - 1) & addressIn);
        
        //if valid grab frameValue and translate
        if (pageTable[pageNum].valid == 1){
            //set as recently access
            pageTable[pageNum].reference = iRef;
            iRef += 1;
            //set name pagenum output value
            pageNum = pageTable[pageNum].value;
            addressOut = (pageNum << 7) | pageOff;
           
            fwrite(&addressOut,8,1L,pFile2);
            continue;
        }
        //count page fault if not valid
        pageFault += 1;
        //get free frame
        fetchF = fetchFrame(frameTable,8);
        //not found
        if(fetchF == -1){
            //free the smellst referenceb value one.
            fetchF = resetRef(pageTable,frameTable,iRef,32);
            
          
        }
        //fill fetch frame, change values in page entry, inc iRef
        frameTable[fetchF] = 1;
        managePage(pageTable,pageNum,fetchF,iRef);
        iRef += 1;

        //grab new pageNum, merge, and write
        pageNum = fetchF;
        addressOut = (pageNum << 7) | pageOff;
        fwrite(&addressOut,8,1L,pFile2);
    }

    printf("Number of pagefaults: %d\n",pageFault);
    //close files
    fclose(pFile);
    fclose(pFile2);
    return (EXIT_SUCCESS);
    
  
}
/*initialized frame and pages, they are differemt sizr. notes: Frame[0] is reservered for OS*/
void initialized(struct Page *pageTable,int frameTable[],int pageSize,int frameSize){
    int i;
    //set page table
    for(i = 0; i< pageSize; i++){
            pageTable[i].valid = INVALID;
            pageTable[i].value = -1;
            pageTable[i].reference = -1;
            
    }
    //set frame table
    frameTable[0] = 1;
    for(i = 1; i < frameSize; i++){
        frameTable[i] = 0;
    }

}
