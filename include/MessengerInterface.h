#pragma once
#include "Message.h"

class MessengerInterface
{
    private:
    unsigned messengerTaskId;
    Message* queue = nullptr;
    protected:
    template <typename T>
    bool sendMessage(const T& message, String key = emptyString);
    template <typename T>
    bool receiveMessage(T* buffer = nullptr,int size = 0,String key = emptyString);
    friend class Messenger;
};

template <typename T>
bool MessengerInterface::sendMessage(const T& i_message,String key)
{
    if(!queue)
    {
        return false;
    }
    Message *message = static_cast<Message*>(new T(i_message));
    if(!message)
    {
        return false;
    }
    if(key!=emptyString)
    {
        message->setKey(key);
    }
    message->time = millis();
    message->next = queue->next;
    message->senderMessengerTaskId = messengerTaskId;
    queue->next = message;
    return true;
}

template <typename T>
bool MessengerInterface::receiveMessage(T *buffer,int size,String key)
{
    if(!queue)
    {
        return false;
    }
    if(!buffer)
    {
        for(Message *current = queue->next;current!=nullptr;current = current->next)
        {
            if(messengerTaskId==current->receiverMessengerTaskId||(key!=emptyString&&key==current->key))
            {
                return true;
            }
        }
    }
    else
    {
        bool success = false;
        int i = 0;
        Message *prev = queue;
        for(Message *current = queue->next;current!=nullptr&&i<size;current = current->next)
        {
            if(messengerTaskId==current->receiverMessengerTaskId||(key!=emptyString&&key==current->key))
            {
                buffer[i] = *(static_cast<T*>(current));
                prev->next = current->next;
                success=true;
                i++;
            }
        }
        return success;
    }
    return false;
}