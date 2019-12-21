#pragma once

#include <string>

class IFileSystem
{
public:
    virtual bool isDirectory(std::string) = 0;

    virtual bool isAbsolutePath(std::string) = 0;

    virtual bool execute(std::string file) = 0;

    virtual int readIntoBuffer(char* buffer, int bufSize, int readPosition, std::string fileName) = 0;
};