#ifndef FILE_SYSTEM_RECEIVER_H
#define FILE_SYSTEM_RECEIVER_H

#include "FileSystemChangeDirectory.h"
#include "FileSystemExecuteFile.h"
#include "FileSystemIsFileAtCurrentDirectory.h"
#include "FileSystemIsFileAtGivenDirectory.h"
#include "FileSystemListDirectory.h"

#include <string>

class FileSystemReceiver : public FileSystemChangeDirectory, 
                           public FileSystemExecuteFile, 
                           public FileSystemIsFileAtCurrentDirectory, 
                           public FileSystemIsFileAtGivenDirectory, 
                           public FileSystemListDirectory
{
public:
    virtual ~FileSystemReceiver() {}
    
    virtual void listDirectory() = 0;
    virtual void changeDirectory(std::string) = 0;
    virtual void execute(std::string) = 0;
    virtual bool isFileAtCurrentDirectory(std::string) = 0;
    virtual bool isFileAtGivenDirectory(std::string) = 0;
};

#endif