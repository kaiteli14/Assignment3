//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <time.h>
//#include <memory.h>
//#include <malloc.h>
//
//#include "file_system.h"
//
//FILE* fp = NULL;
//int BLOCK_SIZE = 512;
//
//int close_disk()
//{
//    if(NULL != fp)
//    {
//        fclose(fp);
//    }
//    return 0;
//}
//
//int Createfs(int numBlocks, char* filename){
//    int i, j;
//    fp = fopen (filename, "w+b");
//    if (fp == NULL)
//    {
//        printf("Could not create new disk file %s\n\n", filename);
//        return -1;
//    }
//
//    for (i = 0; i < numBlocks; i++)
//    {
//        for (j = 0; j < BLOCK_SIZE; j++)
//        {
//            fputc(0, fp);
//        }
//    }
//    return 0;
//}
//
//int Formatfs(int numFiles, int numEntries){
//    FNT fnt[numFiles];
//    DIR dir[numEntries];
//    FREEBLOCK fbl;
//    for(int i=0;i<25000;i++){
//        fbl.list[i] = 1;
//    }
//    for(int i=25000;i<MAX_BLOCK;i++){
//        fbl.list[i] = 0;
//    }
//
//
//    return 0;
//
//
//}
//
//int Openfs(char* filename){
//    fp = fopen (filename, "r+b");
//    if (fp == NULL)
//    {
//        printf("Could not open %s\n\n", filename);
//        return -1;
//    }
//    return 0;
//}
//
//int Savefs(char* old_filename,char* new_filename){
//    FILE* o = NULL;
//    FILE* n = NULL;
//    char* buff = NULL;
//    size_t size = 0;
//
//    o = fopen(old_filename, "rb");
//    if(o == NULL){
//        printf("Error: fopen\n");
//        return -1;
//    }
//
//    n = fopen(new_filename, "wb");
//    if(n == NULL){
//        printf("Error: fopen\n");
//        fclose(n);
//        return -2;
//    }
//
//    fseek(o, 0, SEEK_END);
//    size = (size_t)ftell(o);
//    rewind(o);
//
//    buff = (char*)malloc(size);
//    memset(buff, 0, size);
//
//    fread(buff,1,size,o);
//    fwrite(buff,1,size,n);
//
//    fclose(o);
//    fclose(n);
//
//    printf("Success\n");
//    return 0;
//}
//
//int main(){
//
//    int numFiles = 12;
//    int numEntries = 10;
//
////    Createfs(125000, "disk_0");
//
//    FNT fnt[numFiles];
//    DIR dir[numEntries];
//
//    FREEBLOCK fbl;
//    for(int i=0;i<25000;i++){
//        fbl.list[i] = 1;
//    }
//    for(int i=25000;i<MAX_BLOCK;i++){
//        fbl.list[i] = 0;
//    }
//
//
//    FILE* temp;
//    temp = fopen("disk_0","rb+");
//    fseek(temp,0,SEEK_SET);
//    fwrite(&fbl,sizeof(fbl),1,temp);
//
//    FREEBLOCK fbl_read;
//    fread(&fbl_read,sizeof(fbl_read),25000,temp);
//
//    for(int i=0;i<25000;i++){
//        printf("%d \n",fbl_read.list[i]);
//    }
//
//    return 0;
//}