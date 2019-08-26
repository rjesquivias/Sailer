#pragma once

#include "../../Generic/FileSystemReceiver/file_system_receiver.h"

class WindowsFileSystemReceiver : public FileSystemReceiver
{
public:
    WindowsFileSystemReceiver() {}
    ~WindowsFileSystemReceiver() override {}

    void ListDirectory() override {}
    void ChangeDirectory(std::string) override {}
    void Execute(std::string) override {}
    bool IsFileAtCurrentDirectory(std::string) override  { return true; }
    bool IsFileAtGivenDirectory(std::string) override { return true; }
};