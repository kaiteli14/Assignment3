#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <memory.h>
#include <malloc.h>

/*
Part (a)
Create a file repository - called STAR (Simple TAR) that has:
c - create a new repository with name
a - add a file to repository
d -delete a file
t - trash a file
l - list directory
g - get a copy of the file (don't remove)
The directory should be at the end or the repository
Keep file attributes: up to 60 characters of the local name, size, time and date
You may use any programming language you wish.
 */

 FILE* fp = NULL;
 int BLOCK_SIZE = 512;
 int BLOCK_NUM = 125000;
 int bit_map[125000];


typedef struct directoryEntry{
     char filename[60];
     int size;
     time_t time_date;
     int block_ptr;

 } directoryEntry;

int createRepository(int numBlocks, char* diskname){

    if(access(diskname,F_OK) == 0) {
        return 0;
    }
    int i, j;
    fp = fopen (diskname, "w+b");
    if (fp == NULL)
    {
        printf("Could not create new disk file %s\n\n", diskname);
        return -1;
    }

    for (i = 0; i < numBlocks; i++)
    {
        for (j = 0; j < BLOCK_SIZE; j++)
        {
            fputc(0, fp);
        }
    }
    fclose(fp);
    return 1;
}

int formatRepository(){
    directoryEntry DE[10];
    for(int i = 0;i < 10; i++){
        DE[i].block_ptr = 0;
    }
    fp = fopen("my_repository", "rb+");
    fwrite(DE,sizeof(struct directoryEntry),10,fp);
    for(int i=100; i<125000;i++){
        bit_map[i] = 0;
    }
    fwrite(bit_map,sizeof(int),125000,fp);
    fclose(fp);
}

int addFile(char* filename){







    return 0;
}


int listDirectory(){

    fp = fopen("my_repository", "rb+");
    directoryEntry DE_read[50];
    fread(&DE_read,sizeof(struct directoryEntry),10,fp);
    printf("FILENAME             SIZE DATE TIME");
    for(int i = 0;i < 10; i++){

        printf("%d", DE_read[i].block_ptr);
        printf("%c\n", DE_read[i].filename[0]);
    }
    fclose(fp);
}

int main(){

    createRepository(BLOCK_NUM, "my_repository");

    directoryEntry DE[10];
//    for(int i = 0;i < 10; i++){
//        DE[i].block_ptr = i;
//        DE[i].filename[0] = 'T';
//    }
//    fp = fopen("my_repository", "rb+");
//    fwrite(DE,sizeof(struct directoryEntry),10,fp);
//    fclose(fp);




//    printf("%ld\n",sizeof(bit_map));
//    printf("%ld\n",sizeof(DE));





    return 0;
}