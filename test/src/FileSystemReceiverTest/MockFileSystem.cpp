#include "MockFileSystem.h"

int MockFileSystem::readIntoBuffer(char* buffer, int bufSize, int readPosition, std::string fileName)
{
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