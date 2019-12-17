#include "ICommunicator.h"

class NetworkCommunicator : public ICommunicator
{
public:
    NetworkCommunicator() {} 

    virtual ReturnTypes send(char* data, int size){ return ReturnTypes::SUCCESS; }

    virtual ReturnTypes receive(){ return ReturnTypes::SUCCESS; }
};