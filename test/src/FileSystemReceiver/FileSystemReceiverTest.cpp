#include "gtest/gtest.h"
#include "../../../src/FileSystemReceiver/FileSystemReceiver.h"

TEST(FileSystemReceiverTest, FSRConstructed)
{
    FileSystemReceiver* fsr = nullptr;
    EXPECT_EQ(fsr, nullptr);

    fsr = new FileSystemReceiver;
    ASSERT_NE(fsr, nullptr);
    delete fsr;
}
