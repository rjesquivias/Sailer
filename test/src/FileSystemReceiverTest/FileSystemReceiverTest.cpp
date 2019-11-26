#include "../../../src/FileSystemReceiver/WindowsFileSystemReceiver.h"
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
TEST(WindowsFileSystemReceiverTest, TestChangeDirectoryCommand)
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

TEST(WindowsFileSystemReceiverTest, TestExecuteCommand)
{
    std::shared_ptr<IFileSystem> fileSystem = std::make_shared<MockFileSystem>();
    WindowsFileSystemReceiver fsr(fileSystem);

	// We can you execute to run a handful of things
	// 1) .exe
	// 2) .txt
	// 3) .html
	// 4) .bat
	// ... Anything that can be executed will be executed by this command

	// Execution using absolute filepath
	ReturnTypes r = fsr.execute("C:\\Windows\\system32\\Notepad.exe");
	ASSERT_EQ(r, ReturnTypes::SUCCESS);

	r = fsr.execute("dir");
	ASSERT_EQ(r, ReturnTypes::FAILURE);

	r = fsr.execute("C:\\Users\\user\\Desktop\\prefabs.txt");
	ASSERT_EQ(r, ReturnTypes::SUCCESS);

	r = fsr.execute("C:\\Users\\user\\Desktop\\netvar.html");
	ASSERT_EQ(r, ReturnTypes::SUCCESS);

    // Execution using relative filepath
	if(fsr.changeDirectory("C:\\Users\\user\\Desktop\\") == ReturnTypes::SUCCESS)
	{
		r = fsr.execute("netvar.html");
		ASSERT_EQ(r, ReturnTypes::SUCCESS); 
	}
	else
	{
		FAIL();
	}
	
	r = fsr.execute("prefabs.txt");
	ASSERT_EQ(r, ReturnTypes::SUCCESS);    

	if(fsr.changeDirectory("C:\\Windows\\system32\\") == ReturnTypes::SUCCESS)
	{
		r = fsr.execute("Notepad.exe");
		ASSERT_EQ(r, ReturnTypes::SUCCESS); 
	}  
	else
	{
		FAIL();
	}

	r = fsr.execute("pwned.exe");
	ASSERT_EQ(r, ReturnTypes::FAILURE);     
}
