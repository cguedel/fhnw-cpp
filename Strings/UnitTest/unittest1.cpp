#include "stdafx.h"
#include "CppUnitTest.h"
#include "MyString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(Construction)
		{
			String s0;
			String s1("");
			String s2("abc");
			String s00(s0);
			String s11(s1);
			String s22(s2);
		}

		TEST_METHOD(Length) 
		{
			Assert::IsTrue(String().length() == 0);
			Assert::IsTrue(String("").length() == 0);
			Assert::IsTrue(String("abc").length() == 3);
		}

		TEST_METHOD(CompareTo)
		{
			Assert::IsTrue(String().compareTo("") == 0);
			Assert::IsTrue(String().compareTo("a") == -1);
			Assert::IsTrue(String("aaa").compareTo("aa") == 1);
			Assert::IsTrue(String("aba").compareTo("aa") == 1);
			Assert::IsTrue(String("aa").compareTo("ab") == -1);
		}

		TEST_METHOD(Equals)
		{
			Assert::IsTrue(String() == String());
			Assert::IsTrue(String("abc") == "abc");
		}

		TEST_METHOD(CharAt)
		{
			String s("Test");

			Assert::IsTrue(s.charAt(0) == 'T');
			Assert::IsTrue(s.charAt(1) == 'e');
			Assert::IsTrue(s.charAt(2) == 's');
			Assert::IsTrue(s.charAt(3) == 't');
		}

		TEST_METHOD(CharAtThrowsWhenIndexIsInvalid)
		{
			String s("a");

			try {
				s.charAt(5);

				Assert::Fail();
			}
			catch (exception*)
			{
			}

			try {
				s.charAt(1);

				Assert::Fail();
			}
			catch (exception*)
			{
			}
		}

		TEST_METHOD(Concat)
		{
			String s1("a");
			String s2("b");

			Assert::IsTrue(s1.concat(s2) == "ab");
			Assert::IsTrue(s1.concat('b') == "ab");
		}

		TEST_METHOD(ToCString)
		{
			String s("abc");
			char* cString = "abc";

			Assert::IsTrue(strcmp(s.toCString().get(), cString) == 0);
		}

		TEST_METHOD(ValueOf)
		{
			Assert::IsTrue(String::valueOf(-1) == "-1");
			Assert::IsTrue(String::valueOf(0) == "0");
			Assert::IsTrue(String::valueOf(1) == "1");
			Assert::IsTrue(String::valueOf(100) == "100");
		}

		TEST_METHOD(Substring)
		{
			Assert::IsTrue(String("12345").substring(0, 5) == "12345");
			Assert::IsTrue(String("12345").substring(5, 5) == "");
			Assert::IsTrue(String("12345").substring(10, 15) == "");
			Assert::IsTrue(String("12345").substring(15, 3) == "");
		}
	};
}