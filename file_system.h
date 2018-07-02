//
// Created by kaite on 7/1/18.
//

#ifndef ASSIGNMENT3_FILE_SYSTEM_H
#define ASSIGNMENT3_FILE_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <memory.h>
#include <malloc.h>


#define MAX_BLOCK 250000

typedef struct FNT{
    char* name;
    int inode;
}FNT;

typedef struct DIR{
    int size;
    time_t creation;
    time_t lastaccess;
    time_t lastmodify;
}DIR;

typedef struct FREEBLOCK{
    int list[MAX_BLOCK];
}FREEBLOCK;

typedef union SUPERBLOCK{
    FNT fnt;
    DIR dir;
    FREEBLOCK fbl;
}SUPERBLOCK;



#endif //ASSIGNMENT3_FILE_SYSTEM_H
