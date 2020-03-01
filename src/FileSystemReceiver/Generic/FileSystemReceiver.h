#ifndef FILE_SYSTEM_RECEIVER_H
#define FILE_SYSTEM_RECEIVER_H

#include "Commands/FileSystemChangeDirectory.h"
#include "Commands/FileSystemExecuteFile.h"
#include "Commands/FileSystemIsFileAtCurrentDirectory.h"
#include "Commands/FileSystemIsFileAtGivenDirectory.h"
#include "Commands/FileSystemListDirectory.h"
#include "IFileSystem.h"
#include <string>
#include <memory>

class FileSystemReceiver : public FileSystemChangeDirectory, 
                           public FileSystemExecuteFile, 
                           public FileSystemIsFileAtCurrentDirectory, 
                           public FileSystemIsFileAtGivenDirectory, 
                           public FileSystemListDirectory
{
public:
    virtual ~FileSystemReceiver() {}
    
    virtual ReturnTypes listDirectory() = 0;
    virtual ReturnTypes changeDirectory(std::string) = 0;
    virtual ReturnTypes execute(std::string) = 0;
    virtual bool isFileAtCurrentDirectory() = 0;
    virtual bool isFileAtGivenDirectory(std::string) = 0;

    inline void setDirectory(std::string d) { directory = d; }
    inline std::string getDirectory() { return directory; }

protected:

    std::shared_ptr<IFileSystem> fileSystem;

private:
    std::string directory;
};

#endif