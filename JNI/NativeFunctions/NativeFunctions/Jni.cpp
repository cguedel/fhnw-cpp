#include <iostream>
#include "Test.h"
#include "Matrix.h"

/* prototypes */
void multiply(double* a, double* b, double** r, int i, int j, int k);

JNIEXPORT void JNICALL Java_ch_fhnw_prcpp_tutorial_Test_display(JNIEnv *env, jclass c)
{
	std::cout << "Hello from C++" << std::endl;
}

JNIEXPORT jint JNICALL Java_ch_fhnw_prcpp_tutorial_Test_increment(JNIEnv *env, jclass c, jint i)
{
	return ++i;
}

JNIEXPORT void JNICALL Java_ch_fhnw_prcpp_jni_Matrix_multiplyC
	(JNIEnv *env, 
	 jobject instance, 
	 jdoubleArray a, /* first matrix */
	 jdoubleArray b, /* second matrix */
	 jdoubleArray r, /* result matrix */
	 jint i, /* result matrix rows */
	 jint j, /* result matrix columns */
	 jint k /* first matrix columns */)
{
	jdouble* aPtr = env->GetDoubleArrayElements(a, JNI_FALSE);
	jdouble* bPtr = env->GetDoubleArrayElements(b, JNI_FALSE);
	jdouble* rPtr = env->GetDoubleArrayElements(r, JNI_FALSE);

	multiply(aPtr, bPtr, &rPtr, i, j, k);

	env->ReleaseDoubleArrayElements(a, aPtr, 0);
	env->ReleaseDoubleArrayElements(b, bPtr, 0);
	env->ReleaseDoubleArrayElements(r, rPtr, 0);
}

JNIEXPORT void JNICALL Java_ch_fhnw_prcpp_jni_Matrix_powerC 
	(JNIEnv *env, 
	 jobject instance, 
	 jdoubleArray m, 
	 jint rows, 
	 jint columns, 
	 jint power)
{
	jdouble* mPtr = env->GetDoubleArrayElements(m, JNI_FALSE);

	/* transpose */
	double* t = new double[rows * columns];
	for (int i = 0; i < rows * columns; ++i)
	{
		int row = i / columns;
		int col = i % columns;

		t[col * columns + row] = mPtr[i];
	}

	/* create result matrices */
	double* r1 = new double[rows * columns];
	double* r2 = new double[rows * columns];

	env->GetDoubleArrayRegion(m, 0, rows * columns, r1);
	env->GetDoubleArrayRegion(m, 0, rows * columns, r2);

	for (int i = 0; i < power; ++i)
	{
		if (i % 2 == 0)
		{
			multiply(r1, t, &r2, rows, rows, rows);
		}
		else {
			multiply(r2, t, &r1, rows, rows, rows);
		}
	}

	/* swap result matrices for odd exponents */
	if ((power - 1) % 2 == 0)
	{
		delete[] r2;
		r2 = r1;
	}

	/* copy r2 back */
	env->SetDoubleArrayRegion(m, 0, rows * columns, &r2[0]);
	env->ReleaseDoubleArrayElements(m, mPtr, JNI_ABORT);

	delete[] t;
	delete[] r1;
}

void multiply(double* a, double* b, double** r, int i, int j, int k)
{
	for (int pos = 0; pos < i * j; ++pos)
	{
		int col = pos % j;
		int row = pos / j;
		double value = 0;

		for (int u = 0; u < k; ++u)
		{
			value += a[k * row + u] * b[col * k + u];
		}

		(*r)[pos] = value;
	}
}