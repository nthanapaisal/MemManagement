// CS3733 Assignment 3, Part3.c by Supakjeera Thanapaisal
// similar to part2 but the parameters is customizable. note if pagenum > pagetablesize = segfault, its impossible.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "part2.h"

int main(int argc, char** argv) {
    //vars
    char *pInfile = argv[4];
    char *pOutfile = argv[5];
    char pszBuff[8];
    FILE *pFile, *pFile2;
    unsigned long addressIn;
    unsigned long pageNum;
    unsigned long pageOff;
    unsigned long addressOut;
    int fetchF;
    int pageFault = 0;
    int iRef = 0;
    char *p;

    //math get number of pages and frames
    int totalPage = (strtol(argv[2],&p,10))/(strtol(argv[1],&p,10));
    int totalFrame = (strtol(argv[3],&p,10))/(strtol(argv[1],&p,10));
    int offsetBits = strtol(argv[1],&p,10);
    offsetBits = (log(offsetBits)/log(2));

    //inilized structures
    struct Page pageTable[totalPage];
    int frameTable[totalFrame];
    initialized(pageTable,frameTable,totalPage,totalFrame);

     //check num of args
    if (argc != 6){
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
        
        //parse out pagenum and offset
        addressIn = *((unsigned long *) pszBuff);
        pageNum = addressIn >> offsetBits;
        pageOff = (((1 << offsetBits) - 1) & addressIn);
        
        //if page is valid grab frameValue and translate
        if (pageTable[pageNum].valid == 1){
           
            //set as recently access keeptracker
            pageTable[pageNum].reference = iRef;
            iRef += 1;

            //set name pagenum output value then write ofile
            pageNum = pageTable[pageNum].value;
            addressOut = (pageNum << offsetBits) | pageOff;
           
            fwrite(&addressOut,8,1L,pFile2);
            continue;
        }

        //count pagefault if not valid
        pageFault += 1;
        //get free frame
        fetchF = fetchFrame(frameTable,totalFrame);
        //not found
        if(fetchF == -1){
            //free the smellst referenceb value one.
            fetchF = resetRef(pageTable,frameTable,iRef,totalPage);
            
          
        }
        //fill fetch frame, change values in page entry, increment iRef
        frameTable[fetchF] = 1;
        managePage(pageTable,pageNum,fetchF,iRef);
        iRef += 1;

        //grab new pageNum, merge, and write
        pageNum = fetchF;
        addressOut = (pageNum << offsetBits) | pageOff;
        fwrite(&addressOut,8,1L,pFile2);
    }

    printf("Number of pagefaults: %d\n",pageFault);
    
    //close file
    fclose(pFile);
    fclose(pFile2);
    return (EXIT_SUCCESS);


}

/*initialized frame and pages, they are differemt sizr. notes: Frame[0] is reservered for OS*/
void initialized(struct Page *pageTable,int frameTable[],int pageSize,int frameSize){
    //set page table
    int i;
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
