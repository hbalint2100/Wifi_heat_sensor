#pragma once
#include "LeanTask.h"

class SystemControlledTask : public LeanTask
{
    private:
    String systemID;
    SystemControlledTask *next;
    protected:
    SystemControlledTask(String _systemID) : LeanTask(), systemID(_systemID), next(nullptr){}
    friend class SystemClass;
};
