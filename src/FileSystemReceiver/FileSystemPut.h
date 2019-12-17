#pragma once

#include "ReturnTypes.h"
#include <string>

class FileSystemPut {
public:
    virtual ~FileSystemPut() {}

    virtual ReturnTypes putFile() const = 0;
};
