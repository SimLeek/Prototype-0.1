#include "util.h"

#include <fstream>

using namespace std;

char* util::fileToStr(char* fileName){

    ifstream theFile;

    theFile.open(fileName);

    theFile.seekg(0, ios::end);
    int length = theFile.tellg();
    theFile.seekg(0, ios::beg);

    char* buffer= new char[length +1];

    theFile.read (buffer,length);
    theFile.close();
    buffer[length] = '\0'; //just in case

    return buffer;
}
