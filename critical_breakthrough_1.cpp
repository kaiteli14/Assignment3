//#include "my_api.h"
//#include "my_file_system.h"
//#include "my_disk.h"
//
//int main(){
//
//    auto disk_name = (char*)"my_disk";
////    Createfs(disk_name, 250000);
//
//    FILE_NAME fnt[50];
//    for(int i = 0; i < 50; i++){
//        fnt[i].i_node = (unsigned int)i;
//    }
//
//    FILE_NAME fnt2[50];
//    for(int i = 0; i < 50; i++){
//        fnt2[i].i_node = (unsigned int)i+50;
//    }
//
////
//    ofstream output_file;
//    output_file.open(disk_name,ios::binary|ios::in|ios::out);
//    output_file.write((char*)&fnt,sizeof(fnt));
//    output_file.write((char*)&fnt2,sizeof(fnt2));
//    output_file.close();
//
//    ifstream input_file(disk_name, ios::binary);
//    FILE_NAME fnt_read[100];
//    input_file.seekg(0, ios::beg);
//    input_file.read((char*)&fnt_read, sizeof(fnt_read));
//
//
//    for(int i = 0; i < 100; i++)
//        cout << fnt_read[i].i_node << endl;
//
//    return 0;
//}
