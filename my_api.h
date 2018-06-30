//
// Created by kaite on 6/29/18.
//

#ifndef ASSIGNMENT3_MY_API_H
#define ASSIGNMENT3_MY_API_H

#include "my_file_system.h"
#include "my_disk.h"

using namespace std;

static INIT_INFO init_info;
static unsigned init_info_size = sizeof(init_info);

// Creating a disk
/*
 *Block size is fixed at 512bytes = 4096bits, minimum fputc can write is 1 byte instead of 1 bit due to the filesystem
 * limitation, therefore, our file representation is 8 times larger than it should be because we are writing
 * all 0s and 1s as characters instead of bits.
*/
void Createfs(char* name, unsigned int block_number){

    int status = init_fresh_disk(name, 512, block_number);
    if(status == 0) cout << "*****DISK CREATED*****" << endl;
    else cout << "*****CREATION FAILED*****" << endl;

    init_info.block_total_number = block_number;
    init_info.disk_size = block_number*512;

}

void Formatfs(unsigned int filename_number, unsigned int entry_number){

    static FILE_NAME fnt[filename_number];
    init_info.fnt_size = sizeof(fnt);
    static META_DATA meta_data[entry_number];
    init_info.meta_data_size = sizeof(meta_data);

}



#endif //ASSIGNMENT3_MY_API_H
