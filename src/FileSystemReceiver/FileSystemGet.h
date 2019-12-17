#pragma once

#include "ReturnTypes.h"
#include <string>

class FileSystemGet {
public:
    virtual ~FileSystemGet() {}

    virtual ReturnTypes getFile(std::string fileName) const = 0;
};
