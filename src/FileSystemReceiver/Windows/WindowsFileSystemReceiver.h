#ifndef WINDOWS_FILE_SYSTEM_RECEIVER_H
#define WINDOWS_FILE_SYSTEM_RECEIVER_H

#include "../Generic/FileSystemReceiver.h"

class WindowsFileSystemReceiver : public FileSystemReceiver
{
public:
    WindowsFileSystemReceiver(std::shared_ptr<IFileSystem> fileSystem) { this->fileSystem = fileSystem; }
    ~WindowsFileSystemReceiver() { }

	ReturnTypes listDirectory() { return ReturnTypes::SUCCESS;  }
    ReturnTypes changeDirectory(std::string);
    ReturnTypes execute(std::string) { return ReturnTypes::SUCCESS; }
    bool isFileAtCurrentDirectory() { return true; }
    bool isFileAtGivenDirectory(std::string) { return true; }

};

#endif