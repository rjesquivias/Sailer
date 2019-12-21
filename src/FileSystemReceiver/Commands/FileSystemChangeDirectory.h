#ifndef FILE_SYSTEM_CHANGE_DIRECTORY_H
#define FILE_SYSTEM_CHANGE_DIRECTORY_H

#include "../../ReturnTypes.h"
#include <string>

class FileSystemChangeDirectory {
public:
    virtual ~FileSystemChangeDirectory() {}

    virtual ReturnTypes changeDirectory(std::string) = 0;
};

#endif