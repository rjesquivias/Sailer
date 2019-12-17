#ifndef WINDOWS_FILE_SYSTEM_RECEIVER_H
#define WINDOWS_FILE_SYSTEM_RECEIVER_H

#include "FileSystemReceiver.h"

class WindowsFileSystemReceiver : public FileSystemReceiver
{
public:
    explicit WindowsFileSystemReceiver(std::shared_ptr<IFileSystem> fileSystem, std::shared_ptr<ICommunicator> communication) 
                             {
                                 this->fileSystem = fileSystem;
                                 this->communication = communication;
                             }

    ~WindowsFileSystemReceiver() { }

	ReturnTypes listDirectory() { return ReturnTypes::SUCCESS; }
    ReturnTypes changeDirectory(std::string);
    ReturnTypes execute(std::string);
    ReturnTypes getFile(std::string fileName) const;
    ReturnTypes putFile() const { return ReturnTypes::SUCCESS; }

};

#endif