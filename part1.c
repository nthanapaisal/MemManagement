// CS3733 Assignment 3, Part1.c by Supakjeera Thanapaisal
// Part one for this assignment is to convert virtual address in binary fail into physical address using
// this array for mapping. mapInts[8] = {2,4,1,7,3,5,6};
// 
// System: 32bit(2^32), 1K physical(2^10), 4K virtual(2^12), 128 bytes per page(2^7) 
// sequence: 64 bits/8byte
// numpages: 2^12/2^7 = 2^5 = 32 pages
// 
//  notes: use hexdump -C file.in to check value of binary
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned int rotateLeft(unsigned int uiOrig, int k);

// array for mapping
static int mapInts[8] = {2,4,1,7,3,5,6};

int main(int argc, char** argv) {
    
    //check num of args
    if (argc != 3){
        printf("ERROR: Incorrect number of arguments");
        exit(101);
    }
    char *pInfile = argv[1];
    char *pOutfile = argv[2];
    char pszBuff[8];
    FILE *pFile, *pFile2;
    unsigned long addressIn;
    unsigned long pageNum;
    unsigned long pageOff;
    unsigned long addressOut;

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


    //read in each 8 bytes of the file for each address. 
    while(fread(pszBuff,8,1L,pFile) > 0) {
    
        //you can also read it into unsignedlong* addressIn
        addressIn = *((unsigned long *) pszBuff);
        //get pageNum
        pageNum = addressIn >> 7;
        //get Offset
        pageOff = (((1 << 7) - 1) & addressIn);
        //map it 
        pageNum = mapInts[pageNum];
        // new addy, shift to the left and merge with pageOff
        addressOut = (pageNum << 7) | pageOff;
        
        //write to file
        fwrite(&addressOut,8,1L,pFile2);
        
    }

    //close file pointers
    fclose(pFile);
    fclose(pFile2);
    return (EXIT_SUCCESS);
}


