#ifndef FILE_SYSTEM_LIST_DIRECTORY_H
#define FILE_SYSTEM_LIST_DIRECTORY_H

class FileSystemListDirectory {
public:
    virtual ~FileSystemListDirectory() {}

    virtual void listDirectory() = 0;
};

#endif