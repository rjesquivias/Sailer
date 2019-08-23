#ifndef WINDOWS_FILE_SYSTEM_RECEIVER_H
#define WINDOWS_FILE_SYSTEM_RECEIVER_H

#include "FileSystemReceiver.h"

#include <filesystem>
#include <string>

class WindowsFileSystemReceiver : public FileSystemReceiver
{
public:
    WindowsFileSystemReceiver() {}
    ~WindowsFileSystemReceiver() {}

    void listDirectory();
    void changeDirectory(std::string) {}
    void execute(std::string) {}
    bool isFileAtCurrentDirectory(std::string) { return true; }
    bool isFileAtGivenDirectory(std::string) { return true; }
};

#endif