#pragma once

#include "../../Types/ReturnTypes.h"
#include <string>

class FileSystemGet {
public:
    virtual ~FileSystemGet() {}

    virtual ReturnTypes getFile(std::string fileName) const = 0;

    const int bufSize = 1024;
};
