#ifndef ASSIGNMENT3_MY_FILE_SYSTEM_H
#define ASSIGNMENT3_MY_FILE_SYSTEM_H

#include "my_disk.h"


using namespace std;

typedef struct INIT_INFO{
    char* disk_name;
    unsigned int disk_size;
    unsigned int block_total_number;
    unsigned int fnt_size;
    unsigned int meta_data_size;
};


typedef struct FILE_NAME{

    char name[8];
    unsigned int i_node;

} fnt;

typedef struct META_DATA{

    size_t file_size;
    time_t creation;
    time_t last_modified;
    time_t last_accessed;
    unsigned int block_start;
    unsigned int block_end;

}META_DATA;






#endif //ASSIGNMENT3_MY_FILE_SYSTEM_H
