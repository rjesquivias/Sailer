#include "WindowsFileSystemReceiver.h"

ReturnTypes WindowsFileSystemReceiver::changeDirectory(std::string dir) 
{
    if(dir.empty())
    {
        return ReturnTypes::INVALID_INPUT; 
    }

	// Format dir...Change all forward to backward slashes
	for (int i = 0; i < dir.size(); i++)
	{
		if (dir[i] == '/')
			dir[i] = '\\';
	}

    if(fileSystem->isAbsolutePath(dir))
    {
        if(fileSystem->isDirectory(dir))
        {
            setDirectory(dir);
            return ReturnTypes::SUCCESS;
        }
        else
            return ReturnTypes::INVALID_INPUT;
    }
    else
    {
        // get the current directory and modify it by walking the input dir and changing it as necessary
        std::string newDirectory = getDirectory();
		//std::cout << "newDirectory: " << newDirectory << std::endl;

        while(!dir.empty())
        {
            // 1) grab substrings until next \ (keep trailing '\')
            int endPos = dir.find('\\');
            std::string nextLocation = endPos == std::string::npos ? dir : dir.substr(0, endPos + 1);
            if(nextLocation.back() != '\\') nextLocation.push_back('\\');
            //std::cout << "nextLocation: " << nextLocation << std::endl;
            dir = endPos == std::string::npos ? "" : dir.substr(endPos + 1);

            // 2) check if we need to remove the top directory
            if(nextLocation == "..\\")
            {
                // Walk backwards until we hit the next '\'
                endPos = 0;
                for(int i = newDirectory.size() - 2; i >= 0; i--) // start here to skip initial '\'
                {
                    if(newDirectory[i] == '\\')
                    {
                        endPos = i;
                        break;
                    }
                }

				//std::cout << "position where we found \\: " << endPos << std::endl;
                // Safely ignore if we are at the root drive
                if(endPos == 0) continue;

                // Trim top directory while keeping the trailing '\'
                newDirectory = newDirectory.substr(0, endPos + 1); 
				//std::cout << "NewDirectory after trim: " << newDirectory << std::endl;
            }
			else
			{
				// 3) otherwise add the next location
				newDirectory += nextLocation;
				//std::cout << "NewDirectory after default add: " << newDirectory << std::endl;
			}
        }

        // 4) finally check if it is a valid directory
        if(fileSystem->isDirectory(newDirectory))
        {
            setDirectory(newDirectory);
            return ReturnTypes::SUCCESS;
        }

        return ReturnTypes::INVALID_DIRECTORY;
    } 
}

ReturnTypes WindowsFileSystemReceiver::execute(std::string file)
{
    if(file.empty()) return ReturnTypes::INVALID_INPUT;

    bool status = fileSystem->isAbsolutePath(file) ? fileSystem->execute(file) : fileSystem->execute(getDirectory() + file);
    return status ? ReturnTypes::SUCCESS : ReturnTypes::FAILURE;
}