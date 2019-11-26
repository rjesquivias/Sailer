#pragma once

#include <string>

class FileSystemGet {
public:
    virtual ~FileSystemGet() {}

    virtual bool getFile() const = 0;
};
