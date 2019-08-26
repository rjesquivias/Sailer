#include "../../../src/Generic/FileSystemReceiver/file_system_receiver.h"
#include "mock_file_system_receiver.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

TEST(FileSystemReceiverTest, ShouldBeConstructed)
{
    FileSystemReceiver* fsr = nullptr;
    EXPECT_EQ(fsr, nullptr);

    fsr = new MockFileSystemReceiver;
    ASSERT_NE(fsr, nullptr);
    delete fsr;
}

TEST(FileSystemReceiverTest, ShouldCallListDirectory)
{
    MockFileSystemReceiver fsr;
    EXPECT_CALL(fsr, ListDirectory())
        .Times(AtLeast(1));

    // Directory format depends on operating system
    fsr.ListDirectory();
}

TEST(FileSystemReceiverTest, ShouldCallChangeDirectory)
{
    MockFileSystemReceiver fsr;
    EXPECT_CALL(fsr, ChangeDirectory(_))
        .Times(AtLeast(1));

    // Directory format depends on operating system
    fsr.ChangeDirectory("/Users/RJ/Desktop/videos/");
}

TEST(FileSystemReceiverTest, ShouldCallExecute)
{
    MockFileSystemReceiver fsr;
    EXPECT_CALL(fsr, Execute(_))
        .Times(AtLeast(1));

    // Directory format depends on operating system
    fsr.Execute("/Users/RJ/Documents/bin/otherProg.exe");
    // Use the file name alone to search from the working directory
    fsr.Execute("AwesomeProg.exe");
}

TEST(FileSystemReceiverTest, ShouldCallIsFileAtCurrentDirectory)
{
    MockFileSystemReceiver fsr;
    EXPECT_CALL(fsr, IsFileAtCurrentDirectory(_))
        .Times(AtLeast(1))
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    EXPECT_TRUE(fsr.IsFileAtCurrentDirectory("Avengers: Endgame.mp4"));
    EXPECT_FALSE(fsr.IsFileAtCurrentDirectory("Hulk: The Best Avenger.mp4"));
}

TEST(FileSystemReceiverTest, ShouldCallIsFileAtGivenDirectory)
{
    MockFileSystemReceiver fsr;
    EXPECT_CALL(fsr, IsFileAtGivenDirectory(_))
        .Times(AtLeast(1))
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    // Directory format depends on operating system
    EXPECT_TRUE(fsr.IsFileAtGivenDirectory("/Users/RJ/Desktop/videos/Avengers: Endgame.mp4"));
    EXPECT_FALSE(fsr.IsFileAtGivenDirectory("/Users/RJ/Desktop/videos/Hulk: The Best Avenger.mp4"));
}