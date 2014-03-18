#include "stdafx.h"
#include "CppUnitTest.h"
#include "MyString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(MyString) {
public:
	TEST_METHOD(Construction) {
		String s0;
		String s1("");
		String s2("abc");
		String s00(s0);
		String s11(s1);
		String s22(s2);
	}
	TEST_METHOD(Length) {
		Assert::IsTrue(String().length() == 0);
		Assert::IsTrue(String("").length() == 0);
		Assert::IsTrue(String("abc").length() == 3);
	}
	TEST_METHOD(ToCString) {
		Assert::AreEqual(String().toCString().get(), "");
		Assert::AreEqual(String("abc").toCString().get(), "abc");
	}
	TEST_METHOD(Equals) {
		String s("abc");
		Assert::IsTrue(String() == String(""));
		Assert::IsTrue(String("") == String());
		Assert::IsTrue(s == s);
		Assert::IsFalse(s == String("ab"));
	}
	TEST_METHOD(Compare) {
		String s("abc");
		Assert::AreEqual(String().compareTo(""), 0);
		Assert::IsTrue(s.compareTo("bcd") < 0);
		Assert::IsTrue(s.compareTo("abde") < 0);
		Assert::IsTrue(s.compareTo("abcd") < 0);
		Assert::IsTrue(s.compareTo("abbb") > 0);
		Assert::IsTrue(s.compareTo("ABC") > 0);
		Assert::IsTrue(s.compareTo("") > 0);
		Assert::IsTrue(String().compareTo(s) < 0);
	}
	TEST_METHOD(CharAt) {
		String s("abc");
		Assert::AreEqual(s.charAt(0), 'a');
		Assert::AreEqual(s.charAt(1), 'b');
		Assert::AreEqual(s.charAt(2), 'c');
		bool catched = false;
		try {
			s.charAt(-1);
		}
		catch (std::exception&) {
			catched = true;
		}
		Assert::IsTrue(catched);
		catched = false;
		try {
			String("abc").charAt(3);
		}
		catch (std::exception&) {
			catched = true;
		}
		Assert::IsTrue(catched);
	}
	TEST_METHOD(Concat) {
		String s;
		Assert::IsTrue(s.concat("") == "");
		Assert::IsTrue(s.concat('a') == "a");
		Assert::IsTrue(String("a").concat("") == "a");
		Assert::IsTrue(String("ab").concat('c') == "abc");
		Assert::IsTrue(String("ab").concat("cde") == "abcde");
		Assert::IsTrue(s.concat("abc").concat(s).concat("") == "abc");

	}
	TEST_METHOD(Substring) {
		String s("abcd");
		Assert::IsTrue(s.substring(0, 2) == "ab");
		Assert::IsTrue(s.substring(1, 3) == "bc");
		//Assert::IsTrue(s.substring(2, 4) == "cd");
		//Assert::IsTrue(s.substring(3, 5) == "d");
		//Assert::IsTrue(s.substring(0, -1) == s);

		//Assert::IsTrue(s.substring(2, 2) == "");
		//Assert::IsTrue(s.substring(5, 7) == "");
		//Assert::IsTrue(s.substring(3, 0) == "");
		//Assert::IsTrue(String().substring(0, 1) == "");

		//String s2 = s.substring(2, 4);
		//Assert::IsTrue(s2.charAt(0) == 'c');
	}
	TEST_METHOD(valueOf) {
		Assert::IsTrue(String::valueOf(0) == "0");
		Assert::IsTrue(String::valueOf(10) == "10");
		Assert::IsTrue(String::valueOf(999) == "999");
		Assert::IsTrue(String::valueOf(-0) == "0");
		Assert::IsTrue(String::valueOf(-10) == "-10");
		Assert::IsTrue(String::valueOf(-999) == "-999");
	}
	TEST_METHOD(toInt) {
		Assert::IsTrue(String("123").toInt() == 123);
		Assert::IsTrue(String("   123").toInt() == 123);
		Assert::IsTrue(String("123   ").toInt() == 123);
		Assert::IsTrue(String("  123 ").toInt() == 123);
		Assert::IsTrue(String("  123 456").toInt() == 123);
		Assert::IsTrue(String("  123 abc").toInt() == 123);
		Assert::IsTrue(String("-987").toInt() == -987);
		Assert::IsTrue(String("  -987").toInt() == -987);
		Assert::IsTrue(String("-987  ").toInt() == -987);
		Assert::IsTrue(String(" -987 ").toInt() == -987);
		Assert::IsTrue(String(" -987 654").toInt() == -987);
		Assert::IsTrue(String(" -987 abc").toInt() == -987);
		bool catched = false;
		try {
			String("abc123").toInt();
		}
		catch (std::exception&) {
			catched = true;
		}
		Assert::IsTrue(catched);
		catched = false;
		try {
			String("123abc").toInt();
		}
		catch (std::exception&) {
			catched = true;
		}
		Assert::IsTrue(catched);
		catched = false;
		try {
			String("--123").toInt();
		}
		catch (std::exception&) {
			catched = true;
		}
		Assert::IsTrue(catched);
		catched = false;
		try {
			String("123-").toInt();
		}
		catch (std::exception&) {
			catched = true;
		}
		Assert::IsTrue(catched);
		catched = false;
		try {
			String("123-45").toInt();
		}
		catch (std::exception&) {
			catched = true;
		}
		Assert::IsTrue(catched);
	}
	};
}