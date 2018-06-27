#ifndef ASSIGNMENT3_HEADER_H
#define ASSIGNMENT3_HEADER_H

#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <ctime>

using namespace std;


FILE* fp = nullptr;
double L, p;
double r;
int BLOCK_SIZE, MAX_BLOCK, MAX_RETRY, lru;

/*---------------------------------------*/
/*Initializes a disk file filled with 0's*/
/*---------------------------------------*/
int init_fresh_disk(char* filename, int block_size, int num_blocks)
{
    int i, j;

    /*Set up latency at 0.02 second*/
    L = 00000.f;
    /*Set up failure at 10%*/
    p = -1.f;
    /*Set up max retry attempts after failure to 3*/
    MAX_RETRY = 3;

    BLOCK_SIZE = block_size;
    MAX_BLOCK = num_blocks;

    /*Initializes the random number generator*/
    srand((unsigned int)(time( nullptr )) );

    /*Creates a new file*/
    fp = fopen (filename, "w+b");

    if (fp == nullptr)
    {
        printf("Could not create new disk file %s\n\n", filename);
        return -1;
    }

    /*Fills the file with 0's to its given size*/
    for (i = 0; i < MAX_BLOCK; i++)
    {
        for (j = 0; j < BLOCK_SIZE; j++)
        {
            fputc(0, fp);
        }
    }
    return 0;
}








#endif //ASSIGNMENT3_HEADER_H
