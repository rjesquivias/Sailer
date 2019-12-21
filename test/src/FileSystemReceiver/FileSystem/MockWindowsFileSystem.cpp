#include "MockWindowsFileSystem.h"

bool MockWindowsFileSystem::isDirectory(std::string directory) 
{ 
    if(directory.empty()) return false;

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
bool MockWindowsFileSystem::isAbsolutePath(std::string dir)
{
    if(dir.empty()) return false;

    // The directory separator character MUST be backslash (\) NOT forwardslash (/)
    if(!isalpha(dir[0]) && dir[0] != '\\')
    {
        return false;
    } 

    if(isalpha(dir[0]))
    {
        if(dir.size() >= 2)
        {
            if(dir[1] != ':') return false; // Must start with "C:" or "D:" etc...

            if(dir.size() >= 3) // Strange edge case of form: C:Projects\apilibrary\apilibrary.sln (Relative)
                if(dir[2] != '\\') return false;
        }
        else // "C" or "D" as input... these are not absolute
        {
            return false;
        }
    }
    else if(dir[0] != '\\')
    {
        return true; // Absolute path from the current directory
    }
    
    return true;
}

bool MockWindowsFileSystem::execute(std::string file)
{
    for(auto validExecutable : executableMap)
    {
        if(file == validExecutable)
            return true;
    }

    return false;
}

int MockWindowsFileSystem::readIntoBuffer(char* buffer, int bufSize, int readPosition, std::string fileName)
{
    memset(buffer, 0, bufSize);
    const int endOfFile = 1232;

    bool fileFound = false;
    for(auto validExecutable : executableMap)
    {
        if(fileName == validExecutable)
            fileFound = true;
    }

    if(!fileFound) return -1; // TODO: throw file not found error

    if(readPosition >= endOfFile) // Some hardcoded value denoting EOF
    {
        return 0;
    }

    // Write the integers from readPosition to readPosition + bufSize into the buffer 
    for(int i = 0; i < bufSize; i++)
    {
        if(readPosition + i >= endOfFile) // hit EOF, end early
        {
            return i; // We only read i values, not the entire bufSize
        }

        int integerValue = (readPosition + i) / 4 ; // read into buffer 8 bits at a time
        int mask = 0xFF;
                                                     // The values we are reading are below
        buffer[i++] = (integerValue & mask);         // 00000000.00000000.00000000.11111111
        buffer[i++] = ((integerValue >> 8) & mask);  // 00000000.00000000.11111111.00000000
        buffer[i++] = ((integerValue >> 16) & mask); // 00000000.11111111.00000000.00000000
        buffer[i] = ((integerValue >> 24) & mask);   // 11111111.00000000.00000000.00000000
        // Let the loop do the last increment
    }

    return bufSize;
}