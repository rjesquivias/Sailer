#include "../../../src/FileSystemReceiver/FileSystemReceiver.h"
#include "MockFileSystemReceiver.h"
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
    EXPECT_CALL(fsr, listDirectory())
        .Times(AtLeast(1));

    fsr.listDirectory();
}
