#include <iostream>
#include "FileSystemReceiver/WindowsFileSystemReceiver.h"
#include "FileSystemReceiver/FileSystem.h"
#include "Communicator/NetworkCommunicator.h"
using namespace std;

int main()
{
    std::shared_ptr<IFileSystem> fileSystem = std::make_shared<FileSystem>();
	std::shared_ptr<ICommunicator> communicator = std::make_shared<NetworkCommunicator>();
    WindowsFileSystemReceiver fsr(fileSystem, communicator);

    cout << "Hello World" << endl;

    return 0;
}