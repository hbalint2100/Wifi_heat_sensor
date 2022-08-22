#pragma once
#include <Arduino.h>

class Message
{
    private:
    Message *next = nullptr;
    unsigned senderMessengerTaskId = 0;
    unsigned receiverMessengerTaskId = 0;
    String key;
    public:
    unsigned getSenderMessengerTaskId();
    void setReceiverMessengerTaskId(unsigned receiverMessengerTaskId);
    friend class Messenger;
    friend class MessengerInterface;
};