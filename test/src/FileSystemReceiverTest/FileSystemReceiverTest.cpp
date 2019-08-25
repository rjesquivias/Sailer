#include "../../../src/Generic/FileSystemReceiver/FileSystemReceiver.h"
#include "MockFileSystemReceiver.h"
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
    EXPECT_CALL(fsr, listDirectory())
        .Times(AtLeast(1));

    // Directory format depends on operating system
    fsr.listDirectory();
}

TEST(FileSystemReceiverTest, ShouldCallChangeDirectory)
{
    MockFileSystemReceiver fsr;
    EXPECT_CALL(fsr, changeDirectory(_))
        .Times(AtLeast(1));

    // Directory format depends on operating system
    fsr.changeDirectory("/Users/RJ/Desktop/videos/");
}

TEST(FileSystemReceiverTest, ShouldCallExecute)
{
    MockFileSystemReceiver fsr;
    EXPECT_CALL(fsr, execute(_))
        .Times(AtLeast(1));

    // Directory format depends on operating system
    fsr.execute("/Users/RJ/Documents/bin/otherProg.exe");
    // Use the file name alone to search from the working directory
    fsr.execute("AwesomeProg.exe");
}

TEST(FileSystemReceiverTest, ShouldCallIsFileAtCurrentDirectory)
{
    MockFileSystemReceiver fsr;
    EXPECT_CALL(fsr, isFileAtCurrentDirectory(_))
        .Times(AtLeast(1))
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    EXPECT_TRUE(fsr.isFileAtCurrentDirectory("Avengers: Endgame.mp4"));
    EXPECT_FALSE(fsr.isFileAtCurrentDirectory("Hulk: The Best Avenger.mp4"));
}

TEST(FileSystemReceiverTest, ShouldCallIsFileAtGivenDirectory)
{
    MockFileSystemReceiver fsr;
    EXPECT_CALL(fsr, isFileAtGivenDirectory(_))
        .Times(AtLeast(1))
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    // Directory format depends on operating system
    EXPECT_TRUE(fsr.isFileAtGivenDirectory("/Users/RJ/Desktop/videos/Avengers: Endgame.mp4"));
    EXPECT_FALSE(fsr.isFileAtGivenDirectory("/Users/RJ/Desktop/videos/Hulk: The Best Avenger.mp4"));
}