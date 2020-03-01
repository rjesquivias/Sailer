#ifndef FILE_SYSTEM_EXECUTE_FILE_H
#define FILE_SYSTEM_EXECUTE_FILE_H

#include "../../../Types/ReturnTypes.h"
#include <string>

class FileSystemExecuteFile {
public:
    virtual ~FileSystemExecuteFile() {}

    virtual ReturnTypes execute(std::string) = 0;
};

#endif