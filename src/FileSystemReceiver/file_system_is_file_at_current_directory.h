#pragma once

#include <string>

class FileSystemIsFileAtCurrentDirectory {
public:
    virtual ~FileSystemIsFileAtCurrentDirectory() {}

    virtual bool IsFileAtCurrentDirectory() = 0;
};