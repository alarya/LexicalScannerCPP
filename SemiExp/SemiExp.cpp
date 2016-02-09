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

//----Constructor -----------------
SemiExp::SemiExp(Toker* pToker) : _pToker(pToker) {}

//----Destructor-------------------
SemiExp::~SemiExp()
{

}

//--- collect a semiExpression-----
bool SemiExp::get(bool clear)
{
	_tokens.clear();
  
  std::string token;
  do
  {
	  trimFront();

	  if (isPreProcessorDir())
		  return true;

	  if (isCppComment())
		  return true;

	  if (isCComment())
		  return true;

	  if (isAccessModifier())
		  return true;

	  token = _pToker->getTok();
  
	  if (token == "")
		return false;

	  //if (token != "\n" || )
	  //{
		   _tokens.push_back(token);
	  //}
 
  } while (!isTerminatingTok(token));

  trimFront();

  return true;
}

//---no of tokens in the Semi Exp-----
size_t SemiExp::length()
{
	return _tokens.size();
}

//----index operator -----------------
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
	if (i<0 || _tokens.size() <= i)
		return false;
	std::vector<std::string>::iterator it = _tokens.begin();
	_tokens.erase(it + i);
	return true;
}

//-----merge tokens lowercase -------------------------
void SemiExp::toLower()
{
	return;
}

//-----remove leading newlines -----------------------
void SemiExp::trimFront()
{
	while (_tokens.size() > 0 && (_tokens[0] == "\n" || _tokens[0] == ""))
		remove(0);
}

//-----clear all tokens------------------------------
void SemiExp::clear()
{
	_tokens.clear();
}

//-----collect semi expressions as space sperated strings --------
std::string SemiExp::show(bool showNewLines)
{
	std::cout << "\n  ";
	for (auto token : _tokens)
	    if(token != "\n" || showNewLines)
	      std::cout << token << " ";
    std::cout << "\n";
	
	return "";
}

//<--------------------HELPER FUNCTIONS------------------------------------>

//----is the token returned by toker a semiexpression boundary ----
bool SemiExp::isTerminatingTok(const std::string& token)
{
	
	if (token == "{" || token == "}")
		return true;

	//exception for semiexp with for-loop
	if (_tokens.size() >= 1)
	{
		if (token == ";" && _tokens[0] == "for")
			return false;
	}

	if (token == ";" )
		return true;

	return false;
}

//-----do the tokens form an access modifier-------------//
bool SemiExp::isAccessModifier()
{
	size_t noOfTokens = _tokens.size();

	if (noOfTokens == 2)
	{
			if ((_tokens[0] == "public" || _tokens[0] == "protected" || _tokens[0] == "private") && _tokens[1] == ":")
	     		return true;
	}

	return false;
}

//-----do the tokens form a preprocessor directive---------//
bool SemiExp::isPreProcessorDir()
{
	size_t noOfTokens = _tokens.size();

	if (noOfTokens >= 1)
	{
		if (_tokens[0] == "#" && _tokens[noOfTokens - 1] == "\n")
			return true;
	}

	return false;
}

//-----does the token represent a C++ style comment--------//
bool SemiExp::isCppComment()
{
	size_t noOfTokens = _tokens.size();

	if (noOfTokens == 1)
	{
		std::string token = _tokens[0];
		if (token.size() >= 2)
			if (token[0] == '/' && token[1] == '/')
				return true;
	}

	return false;
}

//----does the token represent a C Comment-----------------//
bool SemiExp::isCComment()
{
	size_t noOfTokens = _tokens.size();

	if (noOfTokens == 1)
	{
		std::string token = _tokens[0];
		if (token.size() >= 2)
			if (token[0] == '/' && token[1] == '*')
				return true;
	}

	return false;
}

//-------------------END OF CLASS SEMIEXP IMPLEMENTATION -------------------------//

int main()
{
  Toker toker;
  //std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
  std::string fileSpec = "../../Tokenizer/test.txt";
  //std::string fileSpec = "../../SemiExp/SemiExp.h";
  
  std::fstream in(fileSpec);
  if (!in.good())
  {
    std::cout << "\n  can't open file " << fileSpec << "\n\n";
    return 1;
  }

  std::cout << "\n File: " << fileSpec << "\n\n";
  toker.attach(&in);

  SemiExp semi(&toker);
  while(semi.get())
  {
    std::cout << "\n  -- semiExpression --";
    semi.show(true);
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