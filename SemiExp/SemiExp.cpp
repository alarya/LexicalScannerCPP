////////////////////////////////////////////////////////////////////////////
// SemiExpression.cpp - collect tokens for analysis                       //
// ver 3.1                                                                //
// Language:         C++, Visual Studio 2015                              //
// Application:      Parser component, CSE687 - Object Oriented Design    //
// Author:           Alok Arya (alarya@syr.edu)							  //
// Original Author:  Jim Fawcett, Syracuse University, CST 4-187          //
//                   jfawcett@twcny.rr.com                                //
////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include "SemiExp.h"
#include "../Tokenizer/Tokenizer.h"

using namespace Scanner;

//-------------------class SemiExp Implementation -------------------------

//using Token = std::string;

//----Constructor -----
SemiExp::SemiExp(Toker* pToker) : _pToker(pToker) {}

//----Destructor-------
SemiExp::~SemiExp()
{

}

//--- collect a semiExpression-----
bool SemiExp::get(bool clear)
{
  _tokens.clear();
  while (true)
  {
	  std::string token = _pToker->getTok();
    if (token == "")
      break;
    _tokens.push_back(token);
    
    if (token == "{")
      return true;
  }
  return false;
}

//---no of tokens in the Semi Exp-----
size_t SemiExp::length()
{
	return _tokens.size();
}

//----index operator -----------------
//Token SemiExp::operator[](size_t n)
//{
//	if (n < 0 || n >= _tokens.size())
//		throw(std::invalid_argument("index out of range"));
//	return _tokens[n];
//}
std::string& SemiExp::operator[](int n)
{
	if (n < 0 || n >= _tokens.size())
		throw(std::invalid_argument("index out of range"));
	return _tokens[n];
}


//----is token present in the Semi Expression ----------
size_t SemiExp::find(const std::string& tok)
{

	return 10;
}

//----- ??----------------------------------------------
void SemiExp::push_back(const std::string& tok)
{
	_tokens.push_back(tok);
}

//-----merge from firstTok to secondTok-----------------
bool SemiExp::merge(const std::string& firstTok, const std::string& secondTok)
{

	return false;
}

//-----remove tok if found in semi Expression ----------
bool SemiExp::remove(const std::string& tok)
{
	return false;
}

//-----remove tok at specified index--------------------
bool SemiExp::remove(size_t i)
{
	return false;
}

//-----merge tokens lowercase -------------------------
void SemiExp::toLower()
{
	return;
}

//-----remove leading newlines -----------------------
void SemiExp::trimFront()
{
	return;
}

//-----clear all tokens------------------------------
void SemiExp::clear()
{
	_tokens.clear();
}

//-----collect semi expressions as space sperated strings --------
std::string SemiExp::show(bool showNewLines)
{

	return "";
}


//void SemiExp::show()
//{
//  std::cout << "\n  ";
//  for (auto token : _tokens)
//    if(token != "\n")
//      std::cout << token << " ";
//  std::cout << "\n";
//}

//-------------------End of class SemiExp Implementation -------------------------

int main()
{
  Toker toker;//abc
  std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
 
  std::fstream in(fileSpec);
  if (!in.good())
  {
    std::cout << "\n  can't open file " << fileSpec << "\n\n";
    return 1;
  }
  toker.attach(&in);

  SemiExp semi(&toker);
  while(semi.get())
  {
    std::cout << "\n  -- semiExpression --";
    semi.show();
  }
  /*
     May have collected tokens, but reached end of stream
     before finding SemiExp terminator.
   */
  if (semi.length() > 0)
  {
    std::cout << "\n  -- semiExpression --";
    semi.show();
    std::cout << "\n\n";
  }
  return 0;
}