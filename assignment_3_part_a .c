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
 int bit_map_temp[125000];
 char* diskname;


typedef struct directoryEntry{
     char filename[60];
     int size;
     time_t time_date;
     int block_ptr;

 } directoryEntry;

int bit_map_first_free(char* diskname) {
    int bit_map[125000];
    fp = fopen(diskname, "rb+");
    fseek(fp, sizeof(int) + sizeof(struct directoryEntry) * 10, SEEK_SET);
    fread(bit_map, sizeof(bit_map), 1, fp);
    for (int j = 2000; j < 125000; j++) {
        if (bit_map[j] == 0) {
            return j;
        }
    }
}

int filename_len(char* filename){
    int cnt = 0;
    for(int i = 0; i < 60; i++){
        if(filename[i] != '@') cnt++;
        else return cnt;
    }

}

int createRepository(int numBlocks, char* diskname){

    if(access(diskname,F_OK) == 0) {
        printf("Repository exists under the name \"%s\"\n\n",diskname);
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

int formatRepository(char* diskname){

    fp = fopen(diskname, "rb+");
    int format_status_check;
    fseek(fp,0,SEEK_SET);
//    fread(&format_status_check,sizeof(int),1,fp);
//    if(format_status_check == 1){
//        printf("Disk has already been formatted\n");
//        return 1;
//    }
    int format_status = 1;
    fwrite(&format_status,sizeof(int),1,fp);
    directoryEntry DE[10];
    for(int i = 0;i < 10; i++){
        DE[i].filename[0] = '!';
        DE[i].size = 0;
        DE[i].time_date = 0;
        DE[i].block_ptr = 0;
    }
    fwrite(DE,sizeof(struct directoryEntry),10,fp);
    for(int i = 0; i<2000; i++){
        bit_map_temp[i] = 1;
    }
    for(int i=2000; i<125000;i++){
        bit_map_temp[i] = 0;
    }
    fwrite(bit_map_temp,sizeof(int),125000,fp);
    fclose(fp);
    return 0;
}

int addFile(char* filename, char* diskname){
    FILE* n = NULL;
    n = fopen(filename, "rb+");
    fp = fopen(diskname, "rb+");
    int numEntry;
    size_t size = 0;
    char c = ' ';
    char* buff = NULL;
    int bit_map[125000];
    directoryEntry DE_read[50];

    // Load directory struct and bitmap
    fseek(fp,sizeof(int),SEEK_SET);
    fread(&DE_read,sizeof(struct directoryEntry),10,fp);
    fread(bit_map,sizeof(int),125000,fp);

    // Allocate buffer and get the addFile size
    fseek(n,0,SEEK_END);
    size = (size_t)ftell(n);
    rewind(n);
    buff = (char*)malloc(size);
    memset(buff,0,size);

    //Update directory and bitmap for the add file
    for(int i = 0; i < 10; i++){
        if(DE_read[i].filename[0] == '!'){
            char* eof = "@";
            sprintf(DE_read[i].filename,"%s%s",filename,eof);
            DE_read[i].size = size;
            DE_read[i].time_date = time(NULL);
            DE_read[i].block_ptr = bit_map_first_free(diskname);
//            printf("%d\n", bit_map_first_free(diskname));
            for(int k = DE_read[i].block_ptr; k < DE_read[i].block_ptr+1 + (size/BLOCK_SIZE); k++){
                bit_map[k] = 1;
            }
//            printf("bitmap at 190 = %d, at 191 = %d, at 192 = %d.\n\n", bit_map[2190], bit_map[2191], bit_map[2192]);
            numEntry = i;
            break;
        }
    }
//    printf("bitmap at 190 = %d, at 191 = %d, at 192 = %d.\n\n", bit_map[2190], bit_map[2191], bit_map[2192]);


    //Writing
    fread(buff,1,size,n);
    fseek(fp,BLOCK_SIZE*(DE_read[numEntry].block_ptr),SEEK_SET);
    fwrite(buff,1,size,fp);
    fseek(fp,sizeof(int),SEEK_SET);
    fwrite(DE_read,sizeof(directoryEntry),10,fp);
    fwrite(bit_map,sizeof(bit_map),1,fp);
//    printf("First free bit location = %d\n", bit_map_first_free(diskname));
    fclose(fp);
    fclose(n);

    return 0;
}

int listDirectory(char* diskname){

    fp = fopen(diskname, "rb+");
    char c = ' ';
    fseek(fp,sizeof(int),SEEK_SET);
    directoryEntry DE_read[50];
    fread(&DE_read,sizeof(struct directoryEntry),10,fp);
    printf("#N    FILENAME%13cSIZE%21cDATE_TIME\n",c,c);

    for(int i = 0;i < 10; i++){

        if(DE_read[i].filename[0] != '!'){
            printf("%1d     ", i);
            for(int j = 0; j < 60; j++){
               if(DE_read[i].filename[j] == '@') break;
               printf("%c",DE_read[i].filename[j]);

            }
            printf("%15d KB %35s\n",
                   DE_read[i].size/1000,
                   ctime(&DE_read[i].time_date));
        }

    }
    fclose(fp);
}

int getCopy(int file_number, char* diskname){

    fp = fopen(diskname, "rb+");
    directoryEntry DE_read[50];
    int bit_map[125000];
    fseek(fp,sizeof(int),SEEK_SET);
    fread(&DE_read,sizeof(struct directoryEntry),10,fp);
    fread(bit_map,sizeof(int),125000,fp);

    int length = filename_len(DE_read[file_number].filename);
    char temp[length+6];
    temp[length] = '-';
    temp[length+1] = 'C';
    temp[length+2] = 'O';
    temp[length+3] = 'P';
    temp[length+4] = 'Y';
    temp[length+5] = '\0';
    for(int i = 0; i < length; i++){
        temp[i] = DE_read[file_number].filename[i];
    }
    char* newfile = &temp[0];

    FILE* n;
    n = fopen(newfile,"wb+");
    size_t size = (size_t)DE_read[file_number].size;
    char* buff =NULL;
    buff = (char*)malloc(size);
    memset(buff, 0, size);
    fseek(fp, DE_read[file_number].block_ptr*BLOCK_SIZE,SEEK_SET);
    fread(buff,1,size,fp);
    fseek(n,0,SEEK_SET);
    fwrite(buff,1,size,n);
    fclose(fp);
    fclose(n);
    return 0;
}

int deleteFile(int filenumber){

    // Load directory struct and bitmap
    fp = fopen(diskname, "rb+");
    int bit_map[125000];
    directoryEntry DE_read[50];
    fseek(fp,sizeof(int),SEEK_SET);
    fread(&DE_read,sizeof(struct directoryEntry),10,fp);
    fread(bit_map,sizeof(int),125000,fp);

    sprintf(DE_read[filenumber].filename,"%s","DELETED@");
    DE_read[filenumber].size = 0;
    DE_read[filenumber].time_date = time(NULL);

    fseek(fp,sizeof(int),SEEK_SET);
    fwrite(DE_read,sizeof(directoryEntry),10,fp);
    fwrite(bit_map,sizeof(bit_map),1,fp);
    fclose(fp);
    return 0;
}

int trashFile(int filenumber){
    // Load directory struct and bitmap
    fp = fopen(diskname, "rb+");
    int bit_map[125000];
    directoryEntry DE_read[50];
    fseek(fp,sizeof(int),SEEK_SET);
    fread(&DE_read,sizeof(struct directoryEntry),10,fp);
    fread(bit_map,sizeof(int),125000,fp);

    directoryEntry temp[10];
    for(int i=0;i<filenumber;i++) temp[i] = DE_read[i];
    for(int j=filenumber;j<9;j++) temp[j] = DE_read[j+1];
    temp[9].filename[0] = '!';



    fseek(fp,sizeof(int),SEEK_SET);
    fwrite(temp,sizeof(directoryEntry),10,fp);
    fwrite(bit_map,sizeof(bit_map),1,fp);
    fclose(fp);
    return 0;
}


void print_operation_list(){
    printf("\nOperations: ");
    printf("\n         c. create a new repository with name"
           "\n         a. add a file to repository"
           "\n         d. delete a file"
           "\n         t. trash a file"
           "\n         l. list directory "
           "\n         g. get a copy of the file into your cwd "
           "\n         e. exit"
           "\n");
}

int main(){
    ////TESTING FIELD
//    diskname = "my_repository";
//    createRepository(BLOCK_NUM, "my_repository");
//    formatRepository(diskname);
//    addFile("fig1.png","my_repository");
//    addFile("fig2.png","my_repository");
//    listDirectory(diskname);
//    getCopy(0,diskname);
//    getCopy(1, diskname);

//    deleteFile(0);
//    trashFile(0);
//    listDirectory(diskname);

while(1) {
    char s[20];
    int i = 0;
    print_operation_list();
    printf("\nPlease enter operation command: ");
    int operation = getchar();
    switch (operation) {
        case 'c':
            printf("Type in your new repository name: ");
            scanf("%s", s);
            diskname = s;
            createRepository(BLOCK_NUM, s);
            formatRepository(s);
            getchar();
            break;

        case'l':
            listDirectory(diskname);
            getchar();
            break;

        case 'a':
           addFile("fig1.png",diskname);
           addFile("fig2.png",diskname);
           getchar();
           break;

        case 'g':
            getCopy(0,diskname);
            getCopy(1, diskname);
            getchar();
            break;

        case 'd':
            deleteFile(0);
            getchar();
            break;

        case 't':
            trashFile(0);
            getchar();
            break;

        case 'e':
            exit(0);

        default:
            printf("Command not valid.\n\n");
            getchar();
            break;
        }
    }
}
