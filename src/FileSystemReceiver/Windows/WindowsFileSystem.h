#pragma once

#ifdef windows

#include "../Generic/IFileSystem.h"
#include <filesystem>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
namespace fs = std::filesystem;

class FileSystem : public IFileSystem
{
    public:
        FileSystem() {}
        ~FileSystem() {}

        inline bool isDirectory(std::string dir) { return fs::is_directory(dir); }

        inline bool isAbsolutePath(std::string dir) 
        { 
            fs::path path(dir); // Construct the path from a string.
            return path.is_absolute(); 
        }

        bool execute(std::string file);

        int readIntoBuffer(char* buffer, int bufSize, int readPosition, std::string fileName);
};

#endif