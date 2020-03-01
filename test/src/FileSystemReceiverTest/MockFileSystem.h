#pragma once

#include "../../../src/FileSystemReceiver/Generic/IFileSystem.h"
#include "gmock/gmock.h"
#include <string>
#include <ctype.h>

class MockFileSystem : public IFileSystem
{
    public:
        MockFileSystem() {}
        ~MockFileSystem() {}

        bool isDirectory(std::string directory) 
        { 
            if(directory.empty()) return false;

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
                "C:\\Users\\user\\Documents\\Visual Studio 2019\\Code Snippets\\Visual C++\\My Code Snippets\\"
            };

            for(auto validDirectory : fileSystemMap)
            {
				//std::cout << "comparing " << validDirectory << " to " << directory << std::endl;
                if(directory == validDirectory || directory == validDirectory.substr(0, validDirectory.size() - 1))
                    return true;
            }

            // Fail if we could not prove we are in a valid directory
            return false;
        }

        /*
        A standard DOS path can consist of three components:

        1) A volume or drive letter followed by the volume separator (:).
        2) A directory name. The directory separator character separates subdirectories within the nested directory hierarchy.
        3) An optional filename. The directory separator character separates the file path and the filename.

        If all three components are present, the path is absolute. If no volume or drive letter is specified and the directory 
        name begins with the directory separator character, the path is relative from the root of the current drive. Otherwise, 
        the path is relative to the current directory.
        */
        bool isAbsolutePath(std::string dir)
        {
            if(dir.empty() || dir.size() < 2) return false;

            if(!isalpha(dir[0])) return false;
            if(dir[1] != ':') return false;
         
            return true;
        }
};