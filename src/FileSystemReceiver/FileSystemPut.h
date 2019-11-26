#pragma once

#include <string>

class FileSystemPut {
public:
    virtual ~FileSystemPut() {}

    virtual bool putFile(std::string) = 0;
};
