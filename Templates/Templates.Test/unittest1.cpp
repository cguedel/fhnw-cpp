#include "stdafx.h"
#include "CppUnitTest.h"
#include "Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TemplatesTest
{		
	TEST_CLASS(TemplateTests)
	{
	public:
		
		TEST_METHOD(TestAddition)
		{
			double a_data[] { 1.3, 4.7, 9.1, 0 };
			double b_data[] { -1.3, 5.3, 0.9, 0.00001 };
			double r_data[4];

			Array<double> a(a_data, 4);
			Array<double> b(b_data, 4);
			Array<double> r(r_data, 4);

			r = a + b;
			Assert::AreEqual(0.0, r[0]);
			Assert::AreEqual(10.0, r[1]);
			Assert::AreEqual(10.0, r[2]);
			Assert::AreEqual(0.00001, r[3]);
		}

		TEST_METHOD(TestSubtraction)
		{
			double a_data[] { 1.3, 4.7, 9.1, 0 };
			double b_data[] { 1.3, -5.3, -0.9, 0.00001 };
			double r_data[4];

			Array<double> a(a_data, 4);
			Array<double> b(b_data, 4);
			Array<double> r(r_data, 4);

			r = a - b;
			Assert::AreEqual(0.0, r[0]);
			Assert::AreEqual(10.0, r[1]);
			Assert::AreEqual(10.0, r[2]);
			Assert::AreEqual(-0.00001, r[3]);
		}

		TEST_METHOD(TestMixedAdditionSubtraction)
		{
			double a_data[] { 1.3, 4.7, 9.1, 0 };
			double b_data[] { 1.3, -5.3, -0.9, 0.00001 };
			double r_data[4];

			Array<double> a(a_data, 4);
			Array<double> b(b_data, 4);
			Array<double> r(r_data, 4);

			r = a - b + b + a;
			Assert::AreEqual(a[0] * 2, r[0]);
			Assert::AreEqual(a[1] * 2, r[1]);
			Assert::AreEqual(a[2] * 2, r[2]);
			Assert::AreEqual(a[3] * 2, r[3]);
		}

		TEST_METHOD(TestScalarMultiplication)
		{
			double a_data[] { 1.3, 4.7, 9.1, 0 };
			double r_data[4];

			Array<double> a(a_data, 4);
			Array<double> r(r_data, 4);

			r = 10.0 * a;
			Assert::AreEqual(13.0, r[0]);
			Assert::AreEqual(47.0, r[1]);
			Assert::AreEqual(91.0, r[2]);
			Assert::AreEqual(0.0, r[3]);
		}

		TEST_METHOD(TestScalarproduct)
		{
			double a_data[] { 5, 10, 20, 35 };
			double b_data[] { 1, 7, 9, 15 };

			Array<double> a(a_data, 4);
			Array<double> b(b_data, 4);

			double r = a**b;
			Assert::AreEqual(780.0, r);
		}

		TEST_METHOD(TestScalarMultiplicationWithAddition)
		{
			int k = 5;
			double l = 3.14;
			double a_data[] = { 2, 3, 5, 9 };
			double b_data[] = { 1, 0, 0, 1 };
			double c_data[] = { 3, 0, 2, 5 };
			double d_data[4];
			Array<double> A(a_data, 4);
			Array<double> B(b_data, 4);
			Array<double> C(c_data, 4);
			Array<double> D(d_data, 4);
			D = k*A + B + l*C;
			
			Assert::AreEqual(20.42, D[0]);
			Assert::AreEqual(15.00, D[1]);
			Assert::AreEqual(31.28, D[2]);
			Assert::AreEqual(61.70, D[3]);
		}
	};
}