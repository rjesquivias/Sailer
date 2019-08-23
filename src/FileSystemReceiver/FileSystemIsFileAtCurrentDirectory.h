#ifndef FILE_SYSTEM_IS_FILE_AT_CURRENT_DIRECTORY_H
#define FILE_SYSTEM_IS_FILE_AT_CURRENT_DIRECTORY_H

#include <string>

class FileSystemIsFileAtCurrentDirectory {
public:
    virtual ~FileSystemIsFileAtCurrentDirectory() {}

    virtual bool isFileAtCurrentDirectory(std::string) = 0;
};

#endif