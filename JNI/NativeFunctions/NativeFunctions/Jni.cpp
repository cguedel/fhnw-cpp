#include <iostream>
#include "Test.h"
#include "Matrix.h"

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

	for (int pos = 0; pos < i * j; ++pos)
	{
		int col = pos % j;
		int row = pos / j;
		double value = 0;
		
		for (int u = 0; u < k; ++u)
		{
			value += aPtr[k * row + u] * bPtr[col * k + u];
		}

		rPtr[pos] = value;
	}

	env->ReleaseDoubleArrayElements(a, aPtr, 0);
	env->ReleaseDoubleArrayElements(b, bPtr, 0);
	env->ReleaseDoubleArrayElements(r, rPtr, 0);
}