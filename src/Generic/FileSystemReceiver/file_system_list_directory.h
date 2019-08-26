#pragma once

class FileSystemListDirectory 
{
public:
    virtual ~FileSystemListDirectory() {}

    virtual void ListDirectory() = 0;
};