#include "AdvancedString.h"

bool AdvancedString::findSubString(const String& text,String match,int& startPos)
{
  for(unsigned int i = 0; i < text.length()-match.length()+1;i++)
  {
    if(match.compareTo(text.substring(i,i+match.length()))==0)
    {
      startPos = i;
      return true;
    }
  }
  return false;
}

bool AdvancedString::findSubString(const String& _text,String startSymbol,String endSymbol,String& foundBetween,bool caseSensitive)
{
  String text = _text;
  if(!caseSensitive)
  {
    startSymbol.toLowerCase();
    endSymbol.toLowerCase();
    text.toLowerCase();
  }
  unsigned endSymbolpos = 0;
  unsigned startSymbolpos = 0;
  bool foundOnce = false;
  int matched = 2;
  for(unsigned i = 0; i < text.length()-endSymbol.length()+1;i++)
  {
    if(endSymbol.compareTo(text.substring(i,i+endSymbol.length()))==0)
    {
      endSymbolpos = i;
      if(startSymbol!=endSymbol||foundOnce)
      {
        matched--;
        break;
      }
      foundOnce = true;
    }
  }
  for(unsigned i = 0; i+startSymbol.length() < endSymbolpos&&i<text.length()-startSymbol.length()+1;i++)
  {
    if(startSymbol.compareTo(text.substring(i,i+startSymbol.length()))==0)
    {
      startSymbolpos = i+startSymbol.length();
      matched--;
      break;
    }
  }
  if(matched==0&&endSymbolpos>startSymbolpos)
  {
    foundBetween = _text.substring(startSymbolpos,endSymbolpos);
    return true;
  }
  return false;
}