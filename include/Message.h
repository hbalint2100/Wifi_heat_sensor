#pragma once
#include <Arduino.h>

class Message
{
    private:
    Message *next = nullptr;
    unsigned senderMessengerTaskId = 0;
    unsigned receiverMessengerTaskId = 0;
    String key;
    String message;
    void setKey(const String& key);
    public:
    void setMessageText(const String& message);
    const String& getMessageText();
    unsigned getSenderMessengerTaskId();
    void setReceiverMessengerTaskId(unsigned receiverMessengerTaskId);
    friend class Messenger;
    friend class MessengerInterface;
};