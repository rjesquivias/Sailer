#ifndef MOCK_FILE_SYSTEM_RECEIVER_H
#define MOCK_FILE_SYSTEM_RECEIVER_H

#include "../../../src/FileSystemReceiver/FileSystemReceiver.h"
#include "gmock/gmock.h"

class MockFileSystemReceiver : public FileSystemReceiver
{
public:
    MOCK_METHOD(void, listDirectory, (), (override));
    MOCK_METHOD(void, changeDirectory, (std::string), (override));
    MOCK_METHOD(void, execute, (std::string), (override));
    MOCK_METHOD(bool, isFileAtCurrentDirectory, (std::string), (override));
    MOCK_METHOD(bool, isFileAtGivenDirectory, (std::string), (override));
};

#endif