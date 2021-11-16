//#include <iostream>
//using namespace std;
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}

#include "Studio.h"
#include <iostream>





int main(int argc, char** argv){
   if(argc!=2){
       std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    Studio* backup = nullptr;
    std::string configurationFile = argv[1];
    Studio studio(configurationFile);
    studio.start();
    if(backup!=nullptr){
        delete backup;
        backup = nullptr;
    }
    return 0;
}

