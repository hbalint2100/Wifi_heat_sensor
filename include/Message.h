#pragma once
#include <Arduino.h>

class Message
{
    private:
    Message *next = nullptr;
    unsigned senderMessengerTaskId = 0;
    unsigned receiverMessengerTaskId = 0;
    String key;
    protected:
    friend class Messenger;
    friend class MessengerInterface;
};