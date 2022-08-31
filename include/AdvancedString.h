#pragma once
#include <Arduino.h>

class AdvancedString
{
    public:
    static bool findSubString(const String& text,String match,int& startPos);
    static bool findSubString(const String& text,String startSymbol,String endSymbol,String& foundBetween,bool caseSensitive = true);
};