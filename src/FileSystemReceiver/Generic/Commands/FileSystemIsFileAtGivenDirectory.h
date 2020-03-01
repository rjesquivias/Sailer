#ifndef FILE_SYSTEM_IS_FILE_AT_GIVEN_DIRECTORY_H
#define FILE_SYSTEM_IS_FILE_AT_GIVEN_DIRECTORY_H

#include <string>

class FileSystemIsFileAtGivenDirectory {
public:
    virtual ~FileSystemIsFileAtGivenDirectory() {}

    virtual bool isFileAtGivenDirectory(std::string) = 0;
};

#endif