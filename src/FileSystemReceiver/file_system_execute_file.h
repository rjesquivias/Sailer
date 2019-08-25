#pragma once

#include <string>

class FileSystemExecuteFile 
{
public:
    virtual ~FileSystemExecuteFile() {}

    virtual void Execute(std::string) = 0;
};