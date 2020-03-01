#include "WindowsFileSystem.h"

#ifdef windows

bool FileSystem::execute(std::string file)
{
    if (!system(NULL))
    {
        return false;
    }
    else
    {
        std::stringstream ss;
        ss << "\"";                                   // command opening quote
        ss << "\"" << file << "\"";                   // Quoted input (could have spaces)
        ss << "\"";                                   // command closing quote
        int returnCode = system( ss.str().c_str() );  // Execute the command
        
        return returnCode == 0;
           
    }
}

int FileSystem::readIntoBuffer(char* buffer, int bufSize, int readPosition, std::string fileName)
{
    std::ifstream is(fileName, std::ifstream::binary);
    
    if (!is.is_open())
    {
        // TODO: Throw Error
        return -1;
    }

    is.seekg(readPosition, is.beg);
    is.read(buffer, bufSize);
    is.close();

    return is.gcount();
}

#endif
