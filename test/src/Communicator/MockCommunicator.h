#pragma once

#include "../../../src/Communicator/ICommunicator.h"

class MockCommunicator : public ICommunicator
{
public:
    MockCommunicator() { historyIndex = 0; }

    ReturnTypes send(char* data, int size);

    ReturnTypes receive();

    char* getHistory() { return communicationHistory; }

    int getBufferSize() { return bufSize; }

private:
    static const int bufSize = 1232;
    char communicationHistory[bufSize]; // This will hold 308 integer values
    int historyIndex;
};