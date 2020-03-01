#include <iostream>
<<<<<<< HEAD
#include "FileSystemReceiver/Windows/WindowsFileSystemReceiver.h"
=======
#include "FileSystemReceiver/WindowsFileSystemReceiver.h"
#include "FileSystemReceiver/FileSystem/WindowsFileSystem.h"
#include "Communicator/NetworkCommunicator.h"
>>>>>>> 91749ce1dc94d6865f43a83757ebf95f0478a42c
using namespace std;

int main()
{
    std::shared_ptr<IFileSystem> fileSystem = std::make_shared<FileSystem>();
    std::shared_ptr<ICommunicator> communicator = std::make_shared<NetworkCommunicator>();
    WindowsFileSystemReceiver fsr(fileSystem, communicator);

    cout << "Hello World" << endl;

    return 0;
}