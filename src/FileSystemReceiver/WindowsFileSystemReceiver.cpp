#include "WindowsFileSystemReceiver.h"

ReturnTypes WindowsFileSystemReceiver::changeDirectory(std::string dir) 
{
    if(dir.empty())
        return ReturnTypes::INVALID_INPUT; 

    // Format dir...Change all forward to backward slashes
    for (int i = 0; i < dir.size(); i++)
    {
        if (dir[i] == '/')
            dir[i] = '\\';
    }

    if(this->fileSystem->isAbsolutePath(dir))
    {
        if(this->fileSystem->isDirectory(dir))
        {
            setDirectory(dir);
            return ReturnTypes::SUCCESS;
        }
        else
        {
            return ReturnTypes::INVALID_INPUT;
        }
    }
    else
    {
        // get the current directory and modify it by walking the input dir and changing it as necessary
        std::string newDirectory = getDirectory();

        while(!dir.empty())
        {
            // 1) grab substrings until next \ (keep trailing '\')
            int endPos = dir.find('\\');
            std::string nextLocation = (endPos == std::string::npos) ? dir : dir.substr(0, endPos + 1);
            
            if (nextLocation.back() != '\\')
                nextLocation.push_back('\\');

            dir = (endPos == std::string::npos) ? "" : dir.substr(endPos + 1);

            // 2) check if we need to remove the top directory
            if(nextLocation == "..\\")
            {
                // Walk backwards until we hit the next '\'
                endPos = 0;
                // start here to skip initial '\'
                for(int i = newDirectory.size() - 2; i >= 0; i--)
                {
                    if(newDirectory[i] == '\\')
                    {
                        endPos = i;
                        break;
                    }
                }

                // Safely ignore if we are at the root drive
                if (endPos == 0)
                    continue;

                // Trim top directory while keeping the trailing '\'
                newDirectory = newDirectory.substr(0, endPos + 1);
            }
            else
            {
                // 3) otherwise add the next location
                newDirectory += nextLocation;
            }
        }

        // 4) finally check if it is a valid directory
        if(this->fileSystem->isDirectory(newDirectory))
        {
            setDirectory(newDirectory);
            return ReturnTypes::SUCCESS;
        }

        return ReturnTypes::INVALID_DIRECTORY;
    } 
}

ReturnTypes WindowsFileSystemReceiver::execute(std::string file)
{
    if (file.empty())
        return ReturnTypes::INVALID_INPUT;

    bool status = this->fileSystem->isAbsolutePath(file) ? this->fileSystem->execute(file) : this->fileSystem->execute(getDirectory() + file);
    return status ? ReturnTypes::SUCCESS : ReturnTypes::FAILURE;
}

ReturnTypes WindowsFileSystemReceiver::getFile(std::string fileName) const
{
    if (!this->fileSystem->isAbsolutePath(fileName))
        fileName = getDirectory() + fileName;

    char* buffer = new char[bufSize];
    int readPosition = 0;
    int bytesRead = 0;
    
    do
    {
        // use the filesystem interface to read data into our buffer
        bytesRead = this->fileSystem->readIntoBuffer(buffer, bufSize, readPosition, fileName);
        if(bytesRead == -1) return ReturnTypes::INVALID_FILENAME;
        readPosition += bytesRead;

        // use the communicator interface to send that data over the network
        communication->send(buffer, bytesRead);
    }
    while (bytesRead > 0);

    delete[] buffer;
    return ReturnTypes::SUCCESS;
}