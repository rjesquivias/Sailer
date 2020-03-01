#ifndef FILE_SYSTEM_LIST_DIRECTORY_H
#define FILE_SYSTEM_LIST_DIRECTORY_H

#include "../../../Types/ReturnTypes.h"

class FileSystemListDirectory {
public:
    virtual ~FileSystemListDirectory() {}

    virtual ReturnTypes listDirectory() = 0;
};

#endif