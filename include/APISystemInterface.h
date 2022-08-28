#pragma once

class APISystemInterface
{
    public:
    virtual void restart() = 0;
    virtual unsigned long getSystemUpTime() = 0;
};