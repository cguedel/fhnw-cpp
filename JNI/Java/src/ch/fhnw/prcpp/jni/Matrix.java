// Created by Christian Guedel on 07.04.2014

package ch.fhnw.prcpp.jni;

import java.util.Random;

public class Matrix {
	private final int columns;
	private final int rows;
	private double[] m;

	static {
		System.loadLibrary("NativeFunctions");
	}

	private native void multiplyC(double[] a, double[] b, double[] r, int i,
			int j, int k);
	private native void powerC(double[] a, int i, int k, int power);

	private Matrix(int rows, int columns, boolean initialise, double d,
			boolean random) {
		this.rows = rows;
		this.columns = columns;
		this.m = new double[rows * columns];

		if (initialise) {
			Random r = random ? new Random() : null;

			for (int i = 0; i < this.m.length; i++) {
				this.m[i] = random ? r.nextDouble() : d;
			}
		}
	}

	public Matrix(int rows, int columns) {
		this(rows, columns, true, 0, true);
	}

	public Matrix(int rows, int columns, double d) {
		this(rows, columns, true, d, false);
	}

	public Matrix(Matrix m) {
		this(m.rows, m.columns, false, 0, false);

		for (int i = 0; i < m.m.length; ++i) {
			this.m[i] = m.m[i];
		}
	}

	public int getRows() {
		return this.rows;
	}

	public int getColumns() {
		return this.columns;
	}

	public void setRow(int row, double[] values) {
		if (values.length != this.columns)
			throw new IllegalStateException();

		for (int i = 0; i < values.length; i++) {
			this.setValueAt(row, i, values[i]);
		}
	}

	public void setValueAt(int row, int column, double value) {
		this.m[row * this.columns + column] = value;
	}

	public double getValueAt(int row, int column) {
		return this.m[row * this.columns + column];
	}

	private Matrix transpose() {
		Matrix t = new Matrix(this.columns, this.rows, false, 0, false);

		for (int i = 0; i < this.m.length; i++) {
			int col = i % this.columns;
			int row = i / this.columns;

			t.setValueAt(col, row, this.m[i]);
		}

		return t;
	}

	public Matrix multiply(Matrix m) {
		if (this.columns != m.rows)
			throw new IllegalStateException();

		Matrix r = new Matrix(this.rows, m.columns, false, 0, false);

		// transpose the second matrix here to avoid cache misses when
		// multiplying. this improves performance to about 10x of the normal
		// version and justifies for the additional memory that is used to store
		// the transposed matrix.
		Matrix t = m.transpose();

		this.multiply(t, r);

		return r;
	}

	private void multiply(Matrix m, Matrix r) {
		for (int i = 0; i < r.m.length; i++) {
			int col = i % r.columns;
			int row = i / r.columns;
			double value = 0;

			for (int k = 0; k < this.columns; k++) {
				value += this.getValueAt(row, k) * m.getValueAt(col, k);
			}

			r.setValueAt(row, col, value);
		}
	}

	public Matrix multiplyNative(Matrix m) {
		if (this.columns != m.rows)
			throw new IllegalStateException();

		Matrix r = new Matrix(this.rows, m.columns, false, 0, false);
		Matrix t = m.transpose();

		this.multiplyNative(t, r);

		return r;
	}

	private void multiplyNative(Matrix m, Matrix r) {
		multiplyC(this.m, m.m, r.m, r.rows, r.columns, this.columns);
	}

	public Matrix power(int k) {
		Matrix r1 = new Matrix(this);
		Matrix r2 = new Matrix(this);
		Matrix t = this.transpose();

		for (int i = 0; i < k - 1; ++i) {
			if (i % 2 == 0) {
				r1.multiply(t, r2);
			} else {
				r2.multiply(t, r1);
			}
		}

		// swap result for odd exponents
		if ((k - 1) % 2 == 0)
			r2 = r1;

		return r2;		
	}

	public Matrix powerNative(int k) {
		Matrix r = new Matrix(this);
		powerC(r.m, r.rows, r.columns, k);
		return r;
	}

	@Override
	public boolean equals(Object m) {
		if (!(m instanceof Matrix))
			return false;

		Matrix t = (Matrix) m;

		if (t.rows != this.rows || t.columns != this.columns)
			return false;

		for (int i = 0; i < this.m.length; i++) {
			if (this.m[i] != t.m[i])
				return false;
		}

		return true;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();

		for (int i = 0; i < this.m.length; i++) {
			if (i % this.columns == 0)
				sb.append('\n');
			sb.append(String.format("%f ", this.m[i]));
		}

		return sb.toString().trim();
	}
}
