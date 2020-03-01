#include "ICommunicator.h"

class NetworkCommunicator : public ICommunicator
{
public:
    NetworkCommunicator() {} 

    virtual ReturnTypes send(char* data, int size) override { return ReturnTypes::SUCCESS; }

    virtual ReturnTypes receive() override { return ReturnTypes::SUCCESS; }
};