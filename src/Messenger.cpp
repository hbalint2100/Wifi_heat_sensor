#include "Messenger.h"

unsigned Messenger::nextID = 1;

Messenger::Messenger() : messageQueueHeader(new Message()) {}

void Messenger::registerTask(MessengerInterface& task)
{
    task.queue = messageQueueHeader;
    task.messengerTaskId = nextID;
    nextID++;
}

Messenger::~Messenger()
{
    Message *prev;
    for(Message *current = messageQueueHeader;current!=nullptr;)
    {
        prev = current;
        current = current->next;
        delete prev;
    }
}

bool Messenger::isEmpty()
{
    return messageQueueHeader->next == nullptr;
}