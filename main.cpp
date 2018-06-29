#include "my_api.h"
#include "my_file_system.h"
#include "my_disk.h"

int main(){


// 512byte = 4096 bit, a disk of 128MB will take 31250 blocks.
    auto disk_name = (char*)"my_disk";
    init_fresh_disk(disk_name, 4096, 31250);



 return 0;
}