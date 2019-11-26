#ifndef FILE_SYSTEM_RECEIVER_H
#define FILE_SYSTEM_RECEIVER_H

#include "FileSystemChangeDirectory.h"
#include "FileSystemExecuteFile.h"
#include "FileSystemGet.h"
#include "FileSystemPut.h"
#include "FileSystemListDirectory.h"
#include "IFileSystem.h"
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
    virtual bool getFile() const = 0;
    virtual bool putFile(std::string) = 0;

    inline void setDirectory(std::string d) { directory = d; }
    inline std::string getDirectory() const { return directory; }

protected:

    std::shared_ptr<IFileSystem> fileSystem;

private:
    std::string directory;
};

#endif