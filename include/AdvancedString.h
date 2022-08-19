#pragma once
#include <Arduino.h>

class AdvancedString
{
    public:
    static bool findSubString(const String& text,String match,int& startPos);
};