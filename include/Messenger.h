#pragma once
#include "Message.h"
#include "MessengerInterface.h"

class Messenger
{
    private:
    static unsigned nextID;
    Message* const messageQueueHeader;  
    public:
    Messenger();
    ~Messenger();
    bool isEmpty();
    void registerTask(MessengerInterface& task);
};