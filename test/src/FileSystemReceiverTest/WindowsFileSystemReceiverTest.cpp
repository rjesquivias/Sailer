#include "gtest/gtest.h"
#include "../../../src/FileSystemReceiver/WindowsFileSystemReceiver.h"

TEST(WindowsFileSystemReceiverTest, WindowsFileSystemReceiverShouldBeConstructed)
{
    WindowsFileSystemReceiver* fsr = nullptr;
    EXPECT_EQ(fsr, nullptr);

    fsr = new WindowsFileSystemReceiver;
    ASSERT_NE(fsr, nullptr);
    delete fsr;
}
