#ifndef FILE_SYSTEM_RECEIVER_H
#define FILE_SYSTEM_RECEIVER_H

#include "Commands/FileSystemChangeDirectory.h"
#include "Commands/FileSystemExecuteFile.h"
#include "Commands/FileSystemGet.h"
#include "Commands/FileSystemPut.h"
#include "Commands/FileSystemListDirectory.h"
#include "FileSystem/IFileSystem.h"
#include "../Communicator/ICommunicator.h"
#include <string>
#include <memory>

class FileSystemReceiver : public FileSystemChangeDirectory, 
                           public FileSystemExecuteFile, 
                           public FileSystemGet, 
                           public FileSystemPut, 
                           public FileSystemListDirectory
{
public:
    virtual ~FileSystemReceiver() {}
    
    virtual ReturnTypes listDirectory() = 0;
    virtual ReturnTypes changeDirectory(std::string) = 0;
    virtual ReturnTypes execute(std::string) = 0;
    virtual ReturnTypes getFile(std::string fileName) const = 0;
    virtual ReturnTypes putFile() const = 0;

    inline void setDirectory(std::string d) { directory = d; }
    inline std::string getDirectory() const { return directory; }

protected:

    std::shared_ptr<IFileSystem> fileSystem;
    std::shared_ptr<ICommunicator> communication;

private:
    std::string directory;
};

#endif