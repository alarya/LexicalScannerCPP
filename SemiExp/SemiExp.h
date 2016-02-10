#ifndef SEMIEXPRESSION_H
#define SEMIEXPRESSION_H
///////////////////////////////////////////////////////////////////////
// SemiExpression.h - collect tokens for analysis                    //
// ver 3.1                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CSE687 - Object Oriented Design    //
// Author:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides a public SemiExp class that collects and makes
* available sequences of tokens.  SemiExp uses the services of a Toker
* class to acquire tokens.  Each call to SemiExp::get() returns a 
* sequence of tokens that ends in {.  This will be extended to use the
* full set of terminators: {, }, ;, and '\n' if the line begins with #.
*
* This is a new version for students in CSE687 - OOD, Spring 2016 to use
* for Project #1.
*
* public Interface
* ----------------
* SemiExp s(pToker);		   //Creates a new instance of SemiExp
* s.get();                     //Gets the next available semi-expression
* s[n];                        //returns the nth token in semi-expression if available
* s.length();				   //returns the number of tokens in the current sem-exp
* s.find("token");             //return the index of the "token" in semi-exp
* s.push_back("token");        //push token into the end of current semi-exp 
* s.remove("token");		   //remove "token" from the current semi-exp 
* s.remove(i);				   //remove a token from i'th index of current semi-exp
* s.merge("token1", "token2"); //currently not used
* s.toLower();                 //turns all the alphabets in the semi-exp to lower case
* s.trimFront();               //remove any new line token from the front of the semi-exp	
* s.clear();				   //clear all tokens from the current semi-exp
* s.show();                    //show the current semi-exp
*
* Build Process:
* --------------
* Required Files: 
*   SemiExpression.h, SemiExpression.cpp, Tokenizer.h, Tokenizer.cpp
* 
* Build Command: devenv Project1.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 3.1 : 30 Jan 2016
* - changed namespace to Scanner
* - fixed bug in termination due to continually trying to read
*   past end of stream if last tokens didn't have a semiExp termination
*   character
* ver 3.0 : 29 Jan 2016
* - built in help session, Friday afternoon
*
* Planned Additions and Changes:
* ------------------------------
* - add public :, protected :, private : as terminators
* - move creation of tokenizer into semiExp constructor so
*   client doesn't have to write that code.
*/

#include <vector>
#include "../Tokenizer/Tokenizer.h"
#include "itokcollection.h"
#include <string>

namespace Scanner
{
  using Token = std::string;

  class SemiExp : public ITokCollection
  {
  public:
    SemiExp(Toker* pToker);
	~SemiExp();
    bool get(bool clear=true);
	std::string& operator[](int n);
    size_t length();
	size_t find(const std::string& tok);
	void push_back(const std::string& tok);
	bool remove(const std::string& tok);
	bool remove(size_t i);
	bool merge(const std::string& firstTok, const std::string& secondTok);
	void toLower();
	void trimFront();
	void clear();
	std::string show(bool showNewLines = false);
  private:
    std::vector<Token> _tokens;
    Toker* _pToker;
	bool isTerminatingTok(const std::string& token);
	bool isAccessModifier();
	bool isPreProcessorDir();
	bool isCppComment();
	bool isCComment();	
  };
}
#endif
