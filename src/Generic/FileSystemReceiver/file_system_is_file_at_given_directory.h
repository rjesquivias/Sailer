#pragma once

#include <string>

class FileSystemIsFileAtGivenDirectory 
{
public:
    virtual ~FileSystemIsFileAtGivenDirectory() {}

    virtual bool IsFileAtGivenDirectory(std::string) = 0;
};