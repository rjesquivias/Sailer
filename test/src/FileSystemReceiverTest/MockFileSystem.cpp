#include "MockFileSystem.h"

int MockFileSystem::readIntoBuffer(char* buffer, int bufSize, int readPosition, std::string fileName)
{
    bool fileFound = false;
    for(auto validExecutable : executableMap)
    {
        if(fileName == validExecutable)
            fileFound = true;
    }

    if(!fileFound) return -1; // TODO: throw file not found error

    if(readPosition >= 1232) // Some hardcoded value denoting EOF
    {
        return 0;
    }

    // Write the integers from readPosition to readPosition + bufSize into the buffer 
    for(int i = 0; i < bufSize; i++)
    {
        if(readPosition + i >= 1232) // hit EOF, end early
        {
            return i; // We only read i values, not the entire bufSize
        }

        int integerValue = (readPosition + i) / 4 ; // read into buffer 8 bits at a time

        buffer[i++] = (integerValue & 0xFF);
        buffer[i++] = ((integerValue >> 8) & 0xFF);
        buffer[i++] = ((integerValue >> 16) & 0xFF);
        buffer[i] = ((integerValue >> 24) & 0xFF); // Let the loop do the last increment
    }

    return bufSize;
}