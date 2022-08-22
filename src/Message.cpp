#include "Message.h"

unsigned Message::getSenderMessengerTaskId()
{
    return senderMessengerTaskId;
}

void Message::setReceiverMessengerTaskId(unsigned i_receiverMessageTaskId)
{
    receiverMessengerTaskId = i_receiverMessageTaskId;
}