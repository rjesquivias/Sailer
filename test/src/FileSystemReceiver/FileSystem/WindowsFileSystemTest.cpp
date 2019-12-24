#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MockWindowsFileSystem.h"
#include <string>

TEST(WindowsFileSystemTest, TestIsDirectory)
{
    MockWindowsFileSystem fileSystem;

    // The following are all valid directories and should pass
    std::string testDirectory1 = "C:\\Users\\user\\";
    ASSERT_EQ(fileSystem.isDirectory(testDirectory1), true);
    std::string testDirectory2 = "C:\\Users\\user\\source\\";
    ASSERT_EQ(fileSystem.isDirectory(testDirectory2), true);
    std::string testDirectory3 = "C:\\Users\\user\\Desktop\\";
    ASSERT_EQ(fileSystem.isDirectory(testDirectory3), true);
    std::string testDirectory4 = "C:\\Users\\user\\Desktop\\projects\\";
    ASSERT_EQ(fileSystem.isDirectory(testDirectory4), true);
    std::string testDirectory5 = "C:\\Users\\user\\Desktop\\projects\\commando\\";
    ASSERT_EQ(fileSystem.isDirectory(testDirectory5), true);
    std::string testDirectory6 = "C:\\Users\\user\\Documents\\";
    ASSERT_EQ(fileSystem.isDirectory(testDirectory6), true);
    std::string testDirectory7 = "C:\\Users\\user\\Documents\\Visual Studio 2019\\";
    ASSERT_EQ(fileSystem.isDirectory(testDirectory7), true);
    

    // The following are executable files in the filesystem
    // Since an executable is not a directory, these should fail
    std::string testExecutable1 = "C:\\Windows\\system32\\Notepad.exe";
    ASSERT_EQ(fileSystem.isDirectory(testExecutable1), false);
    std::string testExecutable2 = "C:\\Users\\user\\Desktop\\prefabs.txt";
    ASSERT_EQ(fileSystem.isDirectory(testExecutable2), false);
    std::string testExecutable3 = "C:\\Users\\user\\Desktop\\netvar.html";
    ASSERT_EQ(fileSystem.isDirectory(testExecutable3), false);

    // Here are some edge case inputs
    std::string emptyString;
    ASSERT_EQ(fileSystem.isDirectory(emptyString), false);
    std::string badInput1 = "bvpoaisdfr";
    ASSERT_EQ(fileSystem.isDirectory(badInput1), false);
    std::string badInput2 = "C:\\illformed\\ ";
    ASSERT_EQ(fileSystem.isDirectory(badInput2), false);
    std::string badInput3 = " C:\\illformed\\";
    ASSERT_EQ(fileSystem.isDirectory(badInput3), false);
    std::string badInput4 = " C:\\illformed\\---=";
    ASSERT_EQ(fileSystem.isDirectory(badInput4), false);
    std::string badInput5 = " ----==-==-0986 C://users//";
    ASSERT_EQ(fileSystem.isDirectory(badInput5), false);
    std::string badInput6 = "C:/Users/user/";
    ASSERT_EQ(fileSystem.isDirectory(badInput6), false);
}

TEST(WindowsFileSystemTest, TestIsAbsolutePath)
{
    MockWindowsFileSystem fileSystem;

    // https://docs.microsoft.com/en-us/dotnet/standard/io/file-path-formats
    std::string absolute1 = "C:\\Documents\\Newsletters\\Summer2018.pdf";               // An absolute file path from the root of drive C:
    std::string absolute2 = "\\Program Files\\Custom Utilities\\StringFinder.exe";      // An absolute path from the root of the current drive.
    std::string relative1 = "2018\\January.xlsx";                                       // A relative path to a file in a subdirectory of the current directory.
    std::string relative2 = "..\\Publications\\TravelBrochure.pdf";                     // A relative path to file in a directory that is a peer of the current directory.
    std::string absolute3 = "C:\\Projects\\apilibrary\\apilibrary.sln";                 // An absolute path to a file from the root of drive C:
    std::string relative3 = "C:Projects\\apilibrary\\apilibrary.sln";                   // A relative path from the current directory of the C: drive.

    ASSERT_EQ(fileSystem.isAbsolutePath(absolute1), true);
    ASSERT_EQ(fileSystem.isAbsolutePath(absolute2), true);
    ASSERT_EQ(fileSystem.isAbsolutePath(relative1), false);
    ASSERT_EQ(fileSystem.isAbsolutePath(relative2), false);
    ASSERT_EQ(fileSystem.isAbsolutePath(absolute3), true);
    ASSERT_EQ(fileSystem.isAbsolutePath(relative3), false);
}

TEST(WindowsFileSystemTest, TestExecute)
{
    MockWindowsFileSystem fileSystem;

    // The following are executable files in the filesystem
    // We should be able to execute all of these
    std::string testExecutable1 = "C:\\Windows\\system32\\Notepad.exe";
    ASSERT_EQ(fileSystem.execute(testExecutable1), true);
    std::string testExecutable2 = "C:\\Users\\user\\Desktop\\prefabs.txt";
    ASSERT_EQ(fileSystem.execute(testExecutable2), true);
    std::string testExecutable3 = "C:\\Users\\user\\Desktop\\netvar.html";
    ASSERT_EQ(fileSystem.execute(testExecutable3), true);

    // Directories, which you can't execute
    std::string testDirectory1 = "C:\\Users\\user\\";
    ASSERT_EQ(fileSystem.execute(testDirectory1), false);
    std::string testDirectory2 = "C:\\Users\\user\\source\\";
    ASSERT_EQ(fileSystem.execute(testDirectory2), false);
    std::string testDirectory3 = "C:\\Users\\user\\Desktop\\";
    ASSERT_EQ(fileSystem.execute(testDirectory3), false);
    std::string testDirectory4 = "C:\\Users\\user\\Desktop\\projects\\";
    ASSERT_EQ(fileSystem.execute(testDirectory4), false);

    // Fail on invalid input
    std::string invalid;
    ASSERT_EQ(fileSystem.execute(invalid), false);
    invalid = "something";
    ASSERT_EQ(fileSystem.execute(invalid), false);
    invalid = "breaksomething.exe";
    ASSERT_EQ(fileSystem.execute(invalid), false);
    invalid = "C:\\Users\\user\\Desktop\\";
    ASSERT_EQ(fileSystem.execute(invalid), false);
    invalid = "a;lsdfkjpgoiuasd90f";
    ASSERT_EQ(fileSystem.execute(invalid), false);
}

TEST(WindowsFileSystemTest, TestReadIntoBuffer)
{
    MockWindowsFileSystem fileSystem;
    const int bufferSize = 128;
    char buffer[bufferSize];
    int bytesRead = 0;
    int readPosition = 0;
    memset(buffer, 0, bufferSize);

    // The following file does not exist so bytesRead should be -1 & the buffer should be unmodified
    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "file.txt");
    ASSERT_EQ(bytesRead, -1);
    for(int i = 0; i < bytesRead; i++)
    {
        ASSERT_EQ(buffer[i], 0);
    }

    // We know the filesize of every executable in our mock file system is 1232
    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "C:\\Windows\\system32\\Notepad.exe");
    
    ASSERT_EQ(bytesRead, bufferSize); // 128
    // Check the actual bits that were written into the buffer
    for(int i = 0; i < bytesRead; i++)
    {
        int* value = (int*)(buffer + i);
        ASSERT_EQ(*value, (readPosition + i) / 4);
        i += 3;
    }
    readPosition += bytesRead;

    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "C:\\Windows\\system32\\Notepad.exe");
    ASSERT_EQ(bytesRead, 128); // 256
    // Check the actual bits that were written into the buffer
    for(int i = 0; i < bytesRead; i++)
    {
        int* value = (int*)(buffer + i);
        ASSERT_EQ(*value, (readPosition + i) / 4);
        i += 3;
    }
    readPosition += bytesRead;

    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "C:\\Windows\\system32\\Notepad.exe");
    ASSERT_EQ(bytesRead, 128); // 384
    // Check the actual bits that were written into the buffer
    for(int i = 0; i < bytesRead; i++)
    {
        int* value = (int*)(buffer + i);
        ASSERT_EQ(*value, (readPosition + i) / 4);
        i += 3;
    }
    readPosition += bytesRead;

    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "C:\\Windows\\system32\\Notepad.exe");
    ASSERT_EQ(bytesRead, 128); // 512
    // Check the actual bits that were written into the buffer
    for(int i = 0; i < bytesRead; i++)
    {
        int* value = (int*)(buffer + i);
        ASSERT_EQ(*value, (readPosition + i) / 4);
        i += 3;
    }
    readPosition += bytesRead;

    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "C:\\Windows\\system32\\Notepad.exe");
    ASSERT_EQ(bytesRead, 128); // 640
    // Check the actual bits that were written into the buffer
    for(int i = 0; i < bytesRead; i++)
    {
        int* value = (int*)(buffer + i);
        ASSERT_EQ(*value, (readPosition + i) / 4);
        i += 3;
    }
    readPosition += bytesRead;

    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "C:\\Windows\\system32\\Notepad.exe");
    ASSERT_EQ(bytesRead, 128); // 768
    // Check the actual bits that were written into the buffer
    for(int i = 0; i < bytesRead; i++)
    {
        int* value = (int*)(buffer + i);
        ASSERT_EQ(*value, (readPosition + i) / 4);
        i += 3;
    }
    readPosition += bytesRead;

    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "C:\\Windows\\system32\\Notepad.exe");
    ASSERT_EQ(bytesRead, 128); // 896
    // Check the actual bits that were written into the buffer
    for(int i = 0; i < bytesRead; i++)
    {
        int* value = (int*)(buffer + i);
        ASSERT_EQ(*value, (readPosition + i) / 4);
        i += 3;
    }
    readPosition += bytesRead;

    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "C:\\Windows\\system32\\Notepad.exe");
    ASSERT_EQ(bytesRead, 128); // 1024
    // Check the actual bits that were written into the buffer
    for(int i = 0; i < bytesRead; i++)
    {
        int* value = (int*)(buffer + i);
        ASSERT_EQ(*value, (readPosition + i) / 4);
        i += 3;
    }
    readPosition += bytesRead;

    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "C:\\Windows\\system32\\Notepad.exe");
    ASSERT_EQ(bytesRead, 128); // 1152
    // Check the actual bits that were written into the buffer
    for(int i = 0; i < bytesRead; i++)
    {
        int* value = (int*)(buffer + i);
        ASSERT_EQ(*value, (readPosition + i) / 4);
        i += 3;
    }
    readPosition += bytesRead;

    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "C:\\Windows\\system32\\Notepad.exe");
    ASSERT_EQ(bytesRead, 80);  // 1232
    // Check the actual bits that were written into the buffer
    for(int i = 0; i < bytesRead; i++)
    {
        int* value = (int*)(buffer + i);
        ASSERT_EQ(*value, (readPosition + i) / 4);
        i += 3;
    }
    readPosition += bytesRead;

    bytesRead = fileSystem.readIntoBuffer(buffer, bufferSize, readPosition, "C:\\Windows\\system32\\Notepad.exe");
    readPosition += bytesRead;
    ASSERT_EQ(bytesRead, 0);  // 1232
}