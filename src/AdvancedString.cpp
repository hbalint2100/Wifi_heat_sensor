#include "AdvancedString.h"

bool AdvancedString::findSubString(const String& text,String match,int& startPos)
{
  for(unsigned int i = 0; i < text.length()-match.length();i++)
  {
    if(match.compareTo(text.substring(i,i+match.length()))==0)
    {
      startPos = i;
      return true;
    }
  }
  return false;
}