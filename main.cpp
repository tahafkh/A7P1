#include"Utrip.hpp"
#include<iostream>
using namespace std;
#define FILE_PATH_INDEX 1
int main(int argc,char* argv[]){
    Utrip utrip;
    utrip.save_hotels_informations(argv[FILE_PATH_INDEX]);
    string command;
    while(getline(cin,command)){
        utrip.check_commands(command);
    }
    return 0;
}