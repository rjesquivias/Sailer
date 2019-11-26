#pragma once

#include <filesystem>
#include <cstdlib>
#include <string>
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

        inline bool execute(std::string file)
        {
            if(!system(NULL)) return false;
            else
            {
                std::stringstream ss;
                ss << "\"";                                   // command opening quote
                ss << "\"" << file << "\"";                   // Quoted input (could have spaces)
                ss << "\"";                                   // command closing quote
                int returnCode = system( ss.str().c_str() );  // Execute the command
                if(returnCode != 0) return false;
            }
            
            return true;
        }
};