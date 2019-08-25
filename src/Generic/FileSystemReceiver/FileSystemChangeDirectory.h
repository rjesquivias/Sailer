#ifndef FILE_SYSTEM_CHANGE_DIRECTORY_H
#define FILE_SYSTEM_CHANGE_DIRECTORY_H

#include <string>

class FileSystemChangeDirectory {
public:
    virtual ~FileSystemChangeDirectory() {}

    virtual void changeDirectory(std::string) = 0;
};

#endif