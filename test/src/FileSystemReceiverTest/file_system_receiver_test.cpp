#include "../../../src/FileSystemReceiver/file_system_receiver.h"
#include "mock_file_system_receiver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;

TEST(FileSystemReceiverTest, ShouldBeConstructed)
{
    FileSystemReceiver* fsr = nullptr;
    EXPECT_EQ(fsr, nullptr);

    fsr = new MockFileSystemReceiver;
    ASSERT_NE(fsr, nullptr);
    delete fsr;
}

TEST(FileSystemReceiverTest, ShouldListDirectory)
{
    MockFileSystemReceiver fsr;
    EXPECT_CALL(fsr, ListDirectory())
        .Times(AtLeast(1));

    fsr.ListDirectory();
}
