// Created by Christian Guedel on 07.04.2014

package ch.fhnw.prcpp.tutorial;

public class Test {

    public static native void display();

    public static native int increment(int value);

    static {
        System.loadLibrary("NativeFunctions");
    }

    public static void main(String[] args) {
        System.out.println(System.getProperty("java.library.path"));
        display();
        System.out.println(increment(4));
    }

}
