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
    delete messageQueueHeader;
}