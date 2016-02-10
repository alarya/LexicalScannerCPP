////////////////////////////////////////////////////////////////////////////
// Executive.cpp -   Executive to test Semi-Expr operations               //
// ver 1.0                                                                //
// Language:         C++, Visual Studio 2015                              //
// Application:      Parser component, CSE687 - Object Oriented Design    //
// Author:           Alok Arya (alarya@syr.edu)							  //
//											                              //
////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include "../SemiExp/SemiExp.h"


using namespace Scanner;

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

