#pragma once

#include <string>

class FileSystemChangeDirectory 
{
public:
    virtual ~FileSystemChangeDirectory() {}

    virtual void ChangeDirectory(std::string) = 0;
};