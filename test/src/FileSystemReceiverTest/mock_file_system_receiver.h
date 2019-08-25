#ifndef MOCK_FILE_SYSTEM_RECEIVER_H
#define MOCK_FILE_SYSTEM_RECEIVER_H

#include "../../../src/FileSystemReceiver/file_system_receiver.h"
#include "gmock/gmock.h"

class MockFileSystemReceiver : public FileSystemReceiver
{
public:
    MOCK_METHOD(void, ListDirectory, (), (override));
    MOCK_METHOD(void, ChangeDirectory, (std::string), (override));
    MOCK_METHOD(void, Execute, (std::string), (override));
    MOCK_METHOD(bool, IsFileAtCurrentDirectory, (), (override));
    MOCK_METHOD(bool, IsFileAtGivenDirectory, (std::string), (override));
};

#endif