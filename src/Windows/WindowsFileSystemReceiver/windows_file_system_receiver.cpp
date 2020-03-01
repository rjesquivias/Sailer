#include "windows_file_system_receiver.h"
#include <iostream> 

namespace fs = std::filesystem;

void WindowsFileSystemReceiver::ListDirectory()
{
    std::string filesInDirectory = "C:\\" + '\n';

	for (auto& entry : fs::directory_iterator("C:\\Users\\RJ\\source\\repos\\Sailer"))
	{
		if (entry.is_directory()) 
		    filesInDirectory += "<DIR>  ";
		else 
		    filesInDirectory += "<FILE> ";
			
		filesInDirectory += entry.path().generic_string();
		filesInDirectory += '\n';
	}

    std::cout << filesInDirectory << std::endl;
}