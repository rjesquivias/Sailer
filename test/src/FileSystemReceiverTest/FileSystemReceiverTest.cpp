#include "../../../src/FileSystemReceiver/Windows/WindowsFileSystemReceiver.h"
#include "MockFileSystemReceiver.h"
#include "MockFileSystem.h"
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

// Windows Specific Tests
TEST(WindowsFileSystemReceiverTest, TestChangeDirectory)
{
    std::shared_ptr<IFileSystem> fileSystem = std::make_shared<MockFileSystem>();
    WindowsFileSystemReceiver fsr(fileSystem);

	// Absolute filepath testing
    fsr.changeDirectory("C:\\");
    ASSERT_EQ(fsr.getDirectory(), "C:\\");

	fsr.changeDirectory("C:\\Users\\");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\");

	fsr.changeDirectory("C:\\Users\\user\\");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\");

	fsr.changeDirectory("C:\\Users\\user\\source\\");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\source\\");

	fsr.changeDirectory("C:\\Users\\user\\Desktop\\");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\Desktop\\");

	fsr.changeDirectory("C:\\Users\\user\\Documents\\Visual Studio 2019\\Code Snippets\\Visual C++\\My Code Snippets\\");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\Documents\\Visual Studio 2019\\Code Snippets\\Visual C++\\My Code Snippets\\");

	// Relative filepath testing
	fsr.changeDirectory("../");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\Documents\\Visual Studio 2019\\Code Snippets\\Visual C++\\");

	fsr.changeDirectory("../../../Visual Studio 2019");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\Documents\\Visual Studio 2019\\");

	fsr.changeDirectory("../../Desktop/");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\Desktop\\");

    fsr.changeDirectory("../../../../../../../");
	ASSERT_EQ(fsr.getDirectory(), "C:\\");

    fsr.changeDirectory("Users/user\\source");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\source\\");

    fsr.changeDirectory("tmp");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\source\\");

    fsr.changeDirectory("../Desktop/proj");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\source\\");

    fsr.changeDirectory("../Desktop/projects");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\Desktop\\projects\\");

    fsr.changeDirectory("abcdiejf");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\Desktop\\projects\\");

    fsr.changeDirectory(".");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\Desktop\\projects\\");

	fsr.changeDirectory("../../helloWorldIdontExist");
    ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\Desktop\\projects\\");

	fsr.changeDirectory("");
	ASSERT_EQ(fsr.getDirectory(), "C:\\Users\\user\\Desktop\\projects\\");
}
