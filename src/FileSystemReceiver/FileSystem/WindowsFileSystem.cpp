#include "WindowsFileSystem.h"

bool FileSystem::execute(std::string file)
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

int FileSystem::readIntoBuffer(char* buffer, int bufSize, int readPosition, std::string fileName)
{
    std::ifstream is(fileName, std::ifstream::binary);
    if(!is.is_open()) return -1; // TODO: Throw Error

    is.seekg(readPosition, is.beg);
    is.read(buffer, bufSize);
    is.close();

    return is.gcount();
}
