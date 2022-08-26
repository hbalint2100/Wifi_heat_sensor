#include "Message.h"

unsigned Message::getSenderMessengerTaskId()
{
    return senderMessengerTaskId;
}

void Message::setReceiverMessengerTaskId(unsigned i_receiverMessageTaskId)
{
    receiverMessengerTaskId = i_receiverMessageTaskId;
}

void Message::setMessageText(const String& _message)
{
    this->message = _message;
}

const String& Message::getMessageText()
{
    return this->message;
}

void Message::setKey(const String& _key)
{
    this->key = _key;
}

long Message::getTime()
{
    return time;
}