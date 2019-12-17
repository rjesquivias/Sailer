#include "MockCommunicator.h"

ReturnTypes MockCommunicator::send(char* data, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(historyIndex >= 1232) historyIndex = 0; // Loop back around and start rerecording data

        communicationHistory[historyIndex] = data[i];
        historyIndex++;
    }

    return ReturnTypes::SUCCESS;
}

ReturnTypes MockCommunicator::receive()
{
    return ReturnTypes::SUCCESS;
}