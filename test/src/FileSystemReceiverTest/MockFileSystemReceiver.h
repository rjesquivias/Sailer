#ifndef MOCK_FILE_SYSTEM_RECEIVER_H
#define MOCK_FILE_SYSTEM_RECEIVER_H

#include "../../../src/FileSystemReceiver/FileSystemReceiver.h"
#include "gmock/gmock.h"

class MockFileSystemReceiver : public FileSystemReceiver
{
public:
    MOCK_METHOD(ReturnTypes, listDirectory, (), (override));
    MOCK_METHOD(ReturnTypes, changeDirectory, (std::string), (override));
    MOCK_METHOD(ReturnTypes, execute, (std::string), (override));
    MOCK_METHOD(bool, getFile, (), (override));
    MOCK_METHOD(bool, putFile, (std::string), (override));
};

#endif