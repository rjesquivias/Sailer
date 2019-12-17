#pragma once

#include "../../../src/Communicator/ICommunicator.h"

class MockCommunicator : public ICommunicator
{
public:
    MockCommunicator() { historyIndex = 0; }

    ReturnTypes send(char* data, int size);

    ReturnTypes receive();

    char* getHistory() { return communicationHistory; }
private:

    char communicationHistory[1232]; // This will hold 308 integer values
    int historyIndex;
};