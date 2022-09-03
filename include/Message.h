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
    long time = 0;
    void setKey(const String& key);
    public:
    long getTime();
    void setMessageText(const String& message);
    const String& getMessageText();
    unsigned getSenderMessengerTaskId();
    void setReceiverMessengerTaskId(unsigned receiverMessengerTaskId);
    friend class Messenger;
    friend class MessengerInterface;
};