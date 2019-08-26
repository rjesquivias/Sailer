#pragma once

#include "file_system_change_directory.h"
#include "file_system_execute_file.h"
#include "file_system_is_file_at_current_directory.h"
#include "file_system_is_file_at_given_directory.h"
#include "file_system_list_directory.h"

#include <string>

class FileSystemReceiver : public FileSystemChangeDirectory, 
                           public FileSystemExecuteFile, 
                           public FileSystemIsFileAtCurrentDirectory, 
                           public FileSystemIsFileAtGivenDirectory, 
                           public FileSystemListDirectory
{
public:
    virtual ~FileSystemReceiver() {}
    
    virtual void ListDirectory() = 0;
    virtual void ChangeDirectory(std::string) = 0;
    virtual void Execute(std::string) = 0;
    virtual bool IsFileAtCurrentDirectory(std::string) = 0;
    virtual bool IsFileAtGivenDirectory(std::string) = 0;
};