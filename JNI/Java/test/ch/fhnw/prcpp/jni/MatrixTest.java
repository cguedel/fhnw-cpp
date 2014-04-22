package ch.fhnw.prcpp.jni;

import static org.junit.Assert.*;

import java.util.concurrent.TimeUnit;

import org.junit.Test;

public class MatrixTest {

	@Test
	public void testMultiplication() {

		Matrix m1 = new Matrix(2, 3);
		m1.setRow(0, new double[] { 1, 2, -1 });
		m1.setRow(1, new double[] { 0, -3, 4 });

		Matrix m2 = new Matrix(3, 3);
		m2.setRow(0, new double[] { 2, 1, -3 });
		m2.setRow(1, new double[] { 0, 1, 0 });
		m2.setRow(2, new double[] { -2, -4, 5 });

		Matrix expected = new Matrix(2, 3);
		expected.setRow(0, new double[] { 4, 7, -8 });
		expected.setRow(1, new double[] { -8, -19, 20 });

		assertEquals(expected, m1.multiply(m2));
	}

	@Test
	public void testMultiplicationNative() {

		Matrix m1 = new Matrix(2, 3);
		m1.setRow(0, new double[] { 1, 2, -1 });
		m1.setRow(1, new double[] { 0, -3, 4 });

		Matrix m2 = new Matrix(3, 3);
		m2.setRow(0, new double[] { 2, 1, -3 });
		m2.setRow(1, new double[] { 0, 1, 0 });
		m2.setRow(2, new double[] { -2, -4, 5 });

		Matrix expected = new Matrix(2, 3);
		expected.setRow(0, new double[] { 4, 7, -8 });
		expected.setRow(1, new double[] { -8, -19, 20 });

		assertEquals(expected, m1.multiplyNative(m2));
	}

	@Test
	public void testLargeMultiplicationUsingJava() {
		Matrix m1 = new Matrix(400, 6000);
		Matrix m2 = new Matrix(6000, 300);

		long start = System.nanoTime();

		m1.multiply(m2);

		System.out.println(String.format("Pure java took %d milliseconds",
				TimeUnit.MILLISECONDS.convert(System.nanoTime() - start,
						TimeUnit.NANOSECONDS)));
		assertTrue(true);
	}

	@Test
	public void testLargeMultiplicationUsingNative() {
		Matrix m1 = new Matrix(400, 6000);
		Matrix m2 = new Matrix(6000, 300);

		long start = System.nanoTime();

		m1.multiplyNative(m2);

		System.out.println(String.format("Native took %d milliseconds",
				TimeUnit.MILLISECONDS.convert(System.nanoTime() - start,
						TimeUnit.NANOSECONDS)));
		assertTrue(true);
	}

	@Test
	public void testLargeMultiplicationSpeed() {
		Matrix m1 = new Matrix(400, 6000);
		Matrix m2 = new Matrix(6000, 300);
		Matrix javaRes;
		Matrix cppRes;

		long[] timesJava = new long[10];
		long[] timesCpp = new long[10];

		javaRes = m1.multiply(m2);
		cppRes = m1.multiplyNative(m2);

		for (int i = 0; i < 10; ++i) {
			long start = System.nanoTime();
			m1.multiply(m2);
			timesJava[i] = TimeUnit.MILLISECONDS.convert(System.nanoTime()
					- start, TimeUnit.NANOSECONDS);
		}

		System.out.println(String.format(
				"Multiply: Java took %f milliseconds at average",
				this.calculateAverage(timesJava)));

		for (int i = 0; i < 10; ++i) {
			long start = System.nanoTime();
			m1.multiplyNative(m2);
			timesCpp[i] = TimeUnit.MILLISECONDS.convert(System.nanoTime()
					- start, TimeUnit.NANOSECONDS);
		}

		System.out.println(String.format(
				"Multiply: Cpp took %f milliseconds at average",
				this.calculateAverage(timesCpp)));

		assertEquals(javaRes, cppRes);
	}

	@Test
	public void testPower() {
		Matrix m = new Matrix(2, 2);
		m.setRow(0, new double[] { 1, 1 });
		m.setRow(1, new double[] { 1, 1 });

		Matrix expected = new Matrix(2, 2);
		expected.setRow(0, new double[] { 128, 128 });
		expected.setRow(1, new double[] { 128, 128 });

		assertEquals(expected, m.power(8));

		expected.setRow(0, new double[] { 64, 64 });
		expected.setRow(1, new double[] { 64, 64 });

		assertEquals(expected, m.power(7));

		m.setRow(0, new double[] { 1, 2 });
		m.setRow(1, new double[] { 3, 4 });

		expected.setRow(0, new double[] { 199, 290 });
		expected.setRow(1, new double[] { 435, 634 });

		assertEquals(expected, m.power(4));

		expected.setRow(0, new double[] { 37, 54 });
		expected.setRow(1, new double[] { 81, 118 });

		assertEquals(expected, m.power(3));
	}

	@Test
	public void testPowerNative() {
		Matrix m = new Matrix(2, 2);
		m.setRow(0, new double[] { 1, 1 });
		m.setRow(1, new double[] { 1, 1 });

		Matrix expected = new Matrix(2, 2);
		expected.setRow(0, new double[] { 128, 128 });
		expected.setRow(1, new double[] { 128, 128 });

		assertEquals(expected, m.powerNative(8));

		expected.setRow(0, new double[] { 64, 64 });
		expected.setRow(1, new double[] { 64, 64 });

		assertEquals(expected, m.powerNative(7));

		m.setRow(0, new double[] { 1, 2 });
		m.setRow(1, new double[] { 3, 4 });

		expected.setRow(0, new double[] { 199, 290 });
		expected.setRow(1, new double[] { 435, 634 });

		Matrix result = new Matrix(m);
		for (int i = 0; i < 3; i++) {
			result = result.multiplyNative(m);
		}

		assertEquals(expected, result);
		assertEquals(expected, m.powerNative(4));

		expected.setRow(0, new double[] { 37, 54 });
		expected.setRow(1, new double[] { 81, 118 });

		assertEquals(expected, m.powerNative(3));
	}

	@Test
	public void testLargePower() {
		Matrix m = new Matrix(200, 200);

		Matrix resultJava = m.power(51);
		Matrix resultCpp = m.powerNative(51);

		assertEquals(resultJava, resultCpp);

		long[] timesJava = new long[10];
		long[] timesCpp = new long[10];

		for (int i = 0; i < 10; ++i) {
			long start = System.nanoTime();
			m.power(51);
			timesJava[i] = TimeUnit.MILLISECONDS.convert(System.nanoTime()
					- start, TimeUnit.NANOSECONDS);

			start = System.nanoTime();
			m.powerNative(51);
			timesCpp[i] = TimeUnit.MILLISECONDS.convert(System.nanoTime()
					- start, TimeUnit.NANOSECONDS);
		}

		System.out.println(String.format(
				"Power (51): Java took %f milliseconds at average",
				this.calculateAverage(timesJava)));

		System.out.println(String.format(
				"Power (51): Cpp took %f milliseconds at average",
				this.calculateAverage(timesCpp)));
	}

	private double calculateAverage(long[] values) {
		long all = 0;
		for (int i = 0; i < values.length; ++i) {
			all += values[i];
		}

		return (double) all / values.length;
	}
}

// sample output
// Multiply: Java took 776.900000 milliseconds at average
// Multiply: Cpp took 771.200000 milliseconds at average
// Pure java took 767 milliseconds
// Native took 960 milliseconds
// Power (51): Java took 367.500000 milliseconds at average
// Power (51): Cpp took 384.200000 milliseconds at average

// sample output after improvment to native power function (22.04.2014)
// Multiply: Java took 706.900000 milliseconds at average
// Multiply: Cpp took 707.500000 milliseconds at average
// Pure java took 695 milliseconds
// Native took 709 milliseconds
// Power (51): Java took 363.800000 milliseconds at average
// Power (51): Cpp took 356.400000 milliseconds at average