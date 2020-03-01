#pragma once

#include <filesystem>
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
};