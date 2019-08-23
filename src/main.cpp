#include <iostream>
#include "FileSystemReceiver/WindowsFileSystemReceiver.h"
using namespace std;


int main()
{
    WindowsFileSystemReceiver fsr;
    fsr.listDirectory();
    
    return 0;
}