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
	for (size_t i = 0; i<length(); ++i)
		if (tok == _tokens[i])
			return i;
	return length();
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
	std::vector<std::string>::iterator it;
	it = std::find(_tokens.begin(), _tokens.end(), tok);
	if (it != _tokens.end())
	{
		_tokens.erase(it);
		return true;
	}
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
	for (int i = 0; i<length(); ++i)
	{
		for (int j = 0; j<(*this)[i].length(); ++j)
		{
			(*this)[i][j] = tolower((*this)[i][j]);
		}
	}
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

namespace Test
{
	static void test0()
	{
		std::cout << "\nSemiExp::show()";
		std::cout << "\n--------------------";
		SemiExp test0(0);
		test0.push_back("semi1");
		test0.push_back("semi2");
		test0.push_back("semi3");
		test0.push_back("semi4");
		std::cout << "\n Showing Semi-Expression: ";
		std::cout << test0.show() << std::endl;
	}

	static void test1()
	{
		std::cout << "\nSemiExp::length()";
		std::cout << "\n--------------------";
		SemiExp test1(0);
		test1.push_back("semi1");
		test1.push_back("semi2");
		test1.push_back("semi3");
		test1.push_back("semi4");
		std::cout << "\n Semi-Expression: ";
		std::cout << test1.show() << std::endl;
		std::cout << "\n Length of Semi-Expression: " << test1.length() << std::endl;
	}

	static void test2()
	{
		std::cout << "\nSemiExp::operator[]()";
		std::cout << "\n--------------------";
		SemiExp test2(0);
		test2.push_back("semi1");
		test2.push_back("semi2");
		test2.push_back("semi3");
		test2.push_back("semi4");
		std::cout << "\n Semi-Expression: ";
		std::cout << test2.show() << std::endl;
		std::cout << "\n Selecting 1st Element: " << test2[0] << std::endl;
		std::cout << "\n Selecting 3rd Element: " << test2[2] << std::endl;
	}

	static void test3()
	{
		std::cout << "\nSemiExp::find()";
		std::cout << "\n--------------------";
		SemiExp test3(0);
		test3.push_back("semi1");
		test3.push_back("semi2");
		test3.push_back("semi3");
		test3.push_back("semi4");
		std::cout << "\n Semi-Expression: ";
		std::cout << test3.show() << std::endl;
		std::cout << "\n Location of \"semi1\": " << test3.find("semi1") << std::endl;
		std::cout << "\n Location of \"semi4\": " << test3.find("semi4") << std::endl;
	}

	static void test4()
	{
		std::cout << "\nSemiExp::remove(\"token\")";
		std::cout << "\n -----------------------------";
		SemiExp test4(0);
		test4.push_back("semi1");
		test4.push_back("semi2");
		test4.push_back("semi3");
		test4.push_back("semi4");
		std::cout << "\n Semi-Expression(Before): ";
		std::cout << test4.show() << std::endl;
		std::cout << "\n  Removing \"semi2\"..." << std::endl;
		test4.remove("semi2");
		std::cout << "\n Semi-Expression(After): ";
		std::cout << test4.show() << std::endl;
	}

	static void test5()
	{
		std::cout << "\nSemiExp::remove(position)";
		std::cout << "\n -----------------------------";
		SemiExp test5(0);
		test5.push_back("semi1");
		test5.push_back("semi2");
		test5.push_back("semi3");
		test5.push_back("semi4");
		std::cout << "\n Semi-Expression(Before): ";
		std::cout << test5.show() << std::endl;
		std::cout << "\n  Removing 3rd element..." << std::endl;
		test5.remove(2);
		std::cout << "\n Semi-Expression(After): ";
		std::cout << test5.show() << std::endl;
	}

	static void test6()
	{
		std::cout << "\nSemiExp::toLower()";
		std::cout << "\n -----------------------------";
		SemiExp test6(0);
		test6.push_back("SEMI1");
		test6.push_back("SEMI2");
		test6.push_back("SEMI3");
		test6.push_back("SEMI4");
		std::cout << "\n Semi-Expression(Before): ";
		std::cout << test6.show() << std::endl;
		test6.toLower();
		std::cout << "\n Semi-Expression(After): ";
		std::cout << test6.show() << std::endl;
	}

	static void test7()
	{
		std::cout << "\nSemiExp::trimFront()";
		std::cout << "\n -----------------------------";
		SemiExp test7(0);
		test7.push_back("\n");
		test7.push_back("\n");
		test7.push_back("semi3");
		test7.push_back("semi4");
		std::cout << "\n Semi-Expression(Before): ";
		std::cout << test7.show(true) << std::endl;
		test7.trimFront();
		std::cout << "\n Semi-Expression(After): ";
		std::cout << test7.show() << std::endl;
	}

	static void test8()
	{
		std::cout << "\nSemiExp::clear()";
		std::cout << "\n -----------------------------";
		SemiExp test8(0);
		test8.push_back("semi1");
		test8.push_back("semi2");
		test8.push_back("semi3");
		test8.push_back("semi4");
		std::cout << "\n Semi-Expression(Before): ";
		std::cout << test8.show(true) << std::endl;
		test8.clear();
		std::cout << "\n Semi-Expression(After): ";
		std::cout << test8.show() << std::endl;
	}
}

#ifdef TEST_SEMIEXP

int main()
{
	{
		Toker toker;
		//std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
		//std::string fileSpec = "../../Tokenizer/test.txt";
		//std::string fileSpec = "../../SemiExp/SemiExp.h";
		std::string fileSpec = "../../Tokenizer/test_cases.txt";

		std::fstream in(fileSpec);
		if (!in.good())
		{
			std::cout << "\n  can't open file " << fileSpec << "\n\n";
			return 1;
		}

		std::cout << "\n File: " << fileSpec << "\n\n";
		toker.attach(&in);

		SemiExp semi(&toker);
		while (semi.get())
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
	}

  std::cout << "\n -----Testing ITokcollection functions -----------\n";
  try {

	  Test::test0();

	  Test::test1();

	  Test::test2();

	  Test::test3();
	  
	  Test::test4();

	  Test::test5();

	  Test::test6();

	  Test::test7();

	  Test::test8();

  }
  catch (std::exception& ex)
  {
	  std::cout << "\n\n  " << ex.what() << "\n\n";
	  return 1;
  }
  return 0;
}

#endif