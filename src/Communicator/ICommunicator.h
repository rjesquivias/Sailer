#pragma once

#include "../Types/ReturnTypes.h"

class ICommunicator
{
public:
    virtual ReturnTypes send(char* data, int size) = 0;

    virtual ReturnTypes receive() = 0;
};