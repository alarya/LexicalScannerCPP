//////////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream					    //
// ver 3.2                                                              //
// Language:         C++, Visual Studio 2015                            //
// Application:      Parser component, CSE687 - Object Oriented Design  //
// Author:		     Alok Arya (alarya@syr.edu)						    //
// Original Author:  Jim Fawcett, Syracuse University, CST 4-187        //
//                   jfawcett@twcny.rr.com                              //
//////////////////////////////////////////////////////////////////////////

#include "Tokenizer.h"
#include <iostream>
#include <cctype>
#include <string>

namespace Scanner
{
  class ConsumeState
  {
  public:
    ConsumeState();
    virtual ~ConsumeState();
    void attach(std::istream* pIn) { _pIn = pIn; }
    virtual void eatChars() = 0;
    void consumeChars() {
      _pState->eatChars();
      _pState = nextState();
    }
    bool canRead() { return _pIn->good(); }
    std::string getTok() { return token; }
    bool hasTok() { return token.size() > 0; }
    ConsumeState* nextState();
  protected:
    static std::string token;
    static std::istream* _pIn;
    static int prevChar;
    static int currChar;
    static ConsumeState* _pState;
    static ConsumeState* _pEatCppComment;
    static ConsumeState* _pEatCComment;
    static ConsumeState* _pEatWhitespace;
    static ConsumeState* _pEatPunctuator;
    static ConsumeState* _pEatAlphanum;
    static ConsumeState* _pEatNewline;
	static ConsumeState* _pEatSpecialSingleChars;
	static ConsumeState* _pEatSpecialCharPairs;
	static ConsumeState* _pEatQuotedStrings;
	static ConsumeState* _pEatQuotedChars;
  };
}

using namespace Scanner;


//<-----------Intializations ------------------------------>

std::string ConsumeState::token;
std::istream* ConsumeState::_pIn;
int ConsumeState::prevChar;
int ConsumeState::currChar;
ConsumeState* ConsumeState::_pState = nullptr;
ConsumeState* ConsumeState::_pEatCppComment = nullptr;
ConsumeState* ConsumeState::_pEatCComment = nullptr;
ConsumeState* ConsumeState::_pEatWhitespace = nullptr;
ConsumeState* ConsumeState::_pEatPunctuator = nullptr;
ConsumeState* ConsumeState::_pEatAlphanum = nullptr;
ConsumeState* ConsumeState::_pEatSpecialCharPairs = nullptr;
ConsumeState* ConsumeState::_pEatSpecialSingleChars = nullptr;
ConsumeState* ConsumeState::_pEatQuotedStrings = nullptr;
ConsumeState* ConsumeState::_pEatQuotedChars = nullptr;
ConsumeState* ConsumeState::_pEatNewline;

void testLog(const std::string& msg);

//<-----------End of Global Declarations ---------------------->



void testLog(const std::string& msg)
{
#ifdef TEST_LOG
	std::cout << "\n  " << msg;
#endif
}

//<-------------ConsumeState Implementation ------------>

ConsumeState* ConsumeState::nextState()
{
  if (!(_pIn->good()))
    return nullptr;

  int chNext = _pIn->peek();

  if (chNext == EOF)
  {
	  _pIn->clear();
	  // if peek() reads end of file character, EOF, then eofbit is set and
	  // _pIn->good() will return false.  clear() restores state to good
  }

  if (std::isspace(currChar) && currChar != '\n')
  {
    testLog("state: eatWhitespace");
    return _pEatWhitespace;
  }
  if (currChar == '/' && chNext == '/')
  {
    testLog("state: eatCppComment");
    return _pEatCppComment;
  }
  if (currChar == '/' && chNext == '*')
  {
    testLog("state: eatCComment");
    return _pEatCComment;
  }
  if (currChar == '\n')
  {
    testLog("state: eatNewLine");
    return _pEatNewline;
  }
  if (std::isalnum(currChar) || currChar == '_')
  {
    testLog("state: eatAlphanum");
    return _pEatAlphanum;
  }
  if (currChar == '\'')
  {
	testLog("state: eatQuotedChars");
	return _pEatQuotedChars;
  }
  if ((currChar == '<' && chNext == '<') ||
	  (currChar == '>' && chNext == '>') ||
	  (currChar == ':' && chNext == ':') ||
	  (currChar == '=' && chNext == '=') ||
	  (currChar == '!' && chNext == '=') 
	  )
  {
	  testLog("state: eatSpecialCharPair");
	  return _pEatSpecialCharPairs;
  }
  if (currChar == '<'  ||
	  currChar == '>'  ||
	  currChar == '['  ||
	  currChar == ']'  ||
	  currChar == '('  ||
	  currChar == ')'  ||
	  currChar == ':'  ||
	  currChar == '!'  ||
	  currChar == '#'
	 )	  
  {
	  testLog("state: eatSpecialCharPair");
	  return _pEatSpecialSingleChars;
  }
  if (currChar == '"')
  {
	  testLog("state: eatQuotedString");
	  return _pEatQuotedStrings;
  }
  if (ispunct(currChar))
  {
    testLog("state: eatPunctuator");
    return _pEatPunctuator;
  }
  if (!_pIn->good())
    return _pEatWhitespace;
  throw(std::logic_error("invalid type"));
}


//----------------Class EatWhitespace Impelementation (Derived: ConsumeState)--->
class EatWhitespace : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating whitespace";
    do {
      if (!_pIn->good())  // end of stream
        return;
      currChar = _pIn->get();
    } while (std::isspace(currChar) && currChar != '\n');
  }
};

//--------------Class EatCppComment Impelementation (Derived: ConsumeState)--->

class EatCppComment : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating C++ comment";
    do {
      if (!_pIn->good())  // end of stream
        return;
	  token += currChar;
      currChar = _pIn->get();
    } while (currChar != '\n');
  }
};

//----------------Class EatCComment Impelementation (Derived: ConsumeState)--->

class EatCComment : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating C comment";
    do {
      if (!_pIn->good())  // end of stream
        return;
	  token += currChar;
      currChar = _pIn->get();
    } while (currChar != '*' || _pIn->peek() != '/');
	token += currChar;
    token += _pIn->get();
    currChar = _pIn->get();
  }
};

//----------------Class EatPunctuator Impelementation (Derived: ConsumeState)--->

class EatPunctuator : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating punctuator";
    do {
      token += currChar;
      if (!_pIn->good())  // end of stream
        return;
      currChar = _pIn->get();
    } while (ispunct(currChar));
  }
};

//----------------Class EatAlphanum Impelementation (Derived: ConsumeState)--->

class EatAlphanum : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating alphanum";
    do {
      token += currChar;
      if (!_pIn->good())  // end of stream
        return;
      currChar = _pIn->get();
    } while (isalnum(currChar) || currChar == '_');
  }
};

//----------------Class EatNewlinee Impelementation (Derived: ConsumeState)--->

class EatNewline : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating alphanum";
    token += currChar;
    if (!_pIn->good())  // end of stream
      return;
    currChar = _pIn->get();
  }
};

//----------------Class EatSpecialSingleChars Impelementation (Derived: ConsumeState)--->

class EatSpecialSingleChars : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		//std::cout << "\n  eating SpecialSingleChars";
		token += currChar;
		if (!_pIn->good())  // end of stream
			return;
		currChar = _pIn->get();
	}
};

//----------------Class EatSpecialCHarPairs Impelementation (Derived: ConsumeState)--->

class EatSpecialCharPairs : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		//std::cout << "\n  eating SpecialCharPairs";
		token += currChar;
		if (!_pIn->good())  // end of stream
			return;
		currChar = _pIn->get();
		token += currChar;
		currChar = _pIn->get();
	}
};

//----------------Class EatQuotedStrings Implementation-----------------------//
class EatQuotedStrings : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		//std::cout << "\n eating QuotedStrings";
		do
		{
			token += currChar;
			if (!_pIn->good())  // end of stream
				return;
			prevChar = currChar;
			currChar = _pIn->get();
			if (currChar == '"' && prevChar == '/')  // eat escaped quotes
			{
				token += currChar;
				currChar = _pIn->get();
			}
		} while (currChar != '"');
		token += currChar;
		currChar = _pIn->get();
	}
};
//-------------Class EatQuotedChars Implementation ----------------------//
class EatQuotedChars : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		do
		{
			token += currChar;
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (currChar != '\'');
		token += currChar;
		currChar = _pIn->get();
	}
};

//----------------Class ConsumeState Impelementation--------->

ConsumeState::ConsumeState()
{
  static bool first = true;
  if (first)
  {
    first = false;
    _pEatAlphanum = new EatAlphanum();
    _pEatCComment = new EatCComment();
    _pEatCppComment = new EatCppComment();
    _pEatPunctuator = new EatPunctuator();
    _pEatWhitespace = new EatWhitespace();
    _pEatNewline = new EatNewline();
	_pEatSpecialSingleChars = new EatSpecialSingleChars();
	_pEatSpecialCharPairs = new EatSpecialCharPairs();
	_pEatQuotedStrings = new EatQuotedStrings();
	_pEatQuotedChars = new EatQuotedChars();
    _pState = _pEatWhitespace;
  }
}

ConsumeState::~ConsumeState()
{
  static bool first = true;
  if (first)
  {
    first = false;
    delete _pEatAlphanum;
    delete _pEatCComment;
    delete _pEatCppComment;
    delete _pEatPunctuator;
    delete _pEatWhitespace;
    delete _pEatNewline;
	delete _pEatSpecialSingleChars;
	delete _pEatSpecialCharPairs;
	delete _pEatQuotedStrings;
	delete _pEatQuotedChars;
  }
}

//----------------End of Class Consume Impelementation--------->

//<------Toker Implementation --------------------------------->

Toker::Toker() : pConsumer(new EatWhitespace()) {}

Toker::~Toker() { delete pConsumer; }

bool Toker::attach(std::istream* pIn)
{
	if (pIn != nullptr && pIn->good())
	{
		pConsumer->attach(pIn);
		return true;
	}
	return false;
}

std::string Toker::getTok()
{
	while (true)
	{
		if (!pConsumer->canRead())
			return "";
		pConsumer->consumeChars();
		if (pConsumer->hasTok())
			break;
	}
	return pConsumer->getTok();
}

bool Toker::canRead() { return pConsumer->canRead(); }

//<------End of Toker Implementation ------------------------->


//----< test stub >--------------------------------------------------

#ifdef TEST_TOKENIZER

#include <fstream>

int main()
{
  //std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
  //std::string fileSpec = "../Tokenizer/Tokenizer.h";
  std::string fileSpec = "../Tokenizer/Test.txt";

  std::ifstream in(fileSpec);
  if (!in.good())
  {
    std::cout << "\n  can't open " << fileSpec << "\n\n";
    return 1;
  }
  Toker toker;
  toker.attach(&in);
  while (in.good())
  {
    std::string tok = toker.getTok();
    if (tok == "\n")
      tok = "newline";
    std::cout << "\n -- " << tok;
  }
  std::cout << "\n\n";
  return 0;
}
#endif
