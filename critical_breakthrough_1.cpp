#include"file_system.h"

#include <fstream>
#include <iostream>

using namespace std;

int main(){

    auto disk_name = (char*)"my_disk";
//    Createfs(disk_name, 250000);

    FNT fnt[50];
    for(int i = 0; i < 50; i++){
        fnt[i].inode = (unsigned int)i;
    }

    FNT fnt2[50];
    for(int i = 0; i < 50; i++){
        fnt2[i].inode = (unsigned int)i+50;
    }


    ofstream output_file;
    output_file.open(disk_name,ios::binary|ios::in|ios::out);
    output_file.write((char*)&fnt,sizeof(fnt));
    output_file.write((char*)&fnt2,sizeof(fnt2));
    output_file.close();

    ifstream input_file(disk_name, ios::binary);
    FNT fnt_read[100];
    input_file.seekg(0, ios::beg);
    input_file.read((char*)&fnt_read, sizeof(fnt_read));


    for(int i = 0; i < 100; i++)
        cout << fnt_read[i].inode << endl;

    return 0;
}
