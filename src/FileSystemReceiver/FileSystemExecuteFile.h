#ifndef FILE_SYSTEM_EXECUTE_FILE_H
#define FILE_SYSTEM_EXECUTE_FILE_H

#include <string>

class FileSystemExecuteFile {
public:
    virtual ~FileSystemExecuteFile() {}

    virtual void execute(std::string) = 0;
};

#endif