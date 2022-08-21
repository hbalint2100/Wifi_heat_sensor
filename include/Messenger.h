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
    void registerTask(MessengerInterface& task);
};