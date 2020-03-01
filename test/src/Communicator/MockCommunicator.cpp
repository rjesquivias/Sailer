#include "MockCommunicator.h"

ReturnTypes MockCommunicator::send(char* data, int size)
{
    for(int i = 0; i < size; i++)
    {
        // Loop back around and start rerecording data
        if (historyIndex >= getBufferSize())
        {
            historyIndex = 0; 
        }

        communicationHistory[historyIndex] = data[i];
        historyIndex++;
    }

    return ReturnTypes::SUCCESS;
}

ReturnTypes MockCommunicator::receive()
{
    return ReturnTypes::SUCCESS;
}