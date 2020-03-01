#pragma once

#include "../../../../src/FileSystemReceiver/FileSystem/IFileSystem.h"
#include "gmock/gmock.h"
#include <string>
#include <ctype.h>

class MockWindowsFileSystem : public IFileSystem
{
    public:
        MockWindowsFileSystem() {}
        ~MockWindowsFileSystem() {}

        bool isDirectory(std::string directory);

        bool isAbsolutePath(std::string dir);

        bool execute(std::string file);

        int readIntoBuffer(char* buffer, int bufSize, int readPosition, std::string fileName);

    private:
            // Here are some directories that exist in our fake fileSystem
            // These are valid with or without the ending backslash
            std::vector<std::string> fileSystemMap = 
            { 
                "C:\\",
                "C:\\Users\\",
                "C:\\Users\\user\\",
                "C:\\Users\\user\\source\\",
                "C:\\Users\\user\\Desktop\\",
                "C:\\Users\\user\\Desktop\\projects\\",
                "C:\\Users\\user\\Desktop\\projects\\commando\\",
                "C:\\Users\\user\\Documents\\",
                "C:\\Users\\user\\Documents\\Visual Studio 2019\\",
                "C:\\Users\\user\\Documents\\Visual Studio 2019\\Code Snippets\\",
                "C:\\Users\\user\\Documents\\Visual Studio 2019\\Code Snippets\\Visual C++\\",
                "C:\\Users\\user\\Documents\\Visual Studio 2019\\Code Snippets\\Visual C++\\My Code Snippets\\",
                "C:\\Windows\\system32\\"
            };

            std::vector<std::string> executableMap = 
            { 
                "C:\\Windows\\system32\\Notepad.exe",
                "C:\\Users\\user\\Desktop\\prefabs.txt",
                "C:\\Users\\user\\Desktop\\netvar.html"
            };
};