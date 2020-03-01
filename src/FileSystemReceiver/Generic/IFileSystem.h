#pragma once

class IFileSystem
{
public:
    virtual bool isDirectory(std::string) = 0;

    virtual bool isAbsolutePath(std::string) = 0;
};