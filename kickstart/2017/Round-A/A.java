/**
    学习java BigInteger的用法：https://docs.oracle.com/javase/6/docs/api/java/math/BigInteger.html
*/
import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class Main {

    public static final BigInteger MOD = new BigInteger("1000000007");
    public static void main(String[] args) throws Exception {

        String path = "/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-A/";
        File file = new File(path + "A-large-practice.in");

        Scanner in = new Scanner(file);
        PrintWriter out = new PrintWriter(new FileWriter(path + "A-large-practice.out"));

        int T = in.nextInt(), line = 1;
        while (--T >= 0) {
            BigInteger R = new BigInteger(Integer.toString(in.nextInt()));
            BigInteger C = new BigInteger(Integer.toString(in.nextInt()));

            if (R.compareTo(C) == 1) {
            	BigInteger tmp = R;
            	R = C;
            	C = tmp;
            }

// (c - r) * (r * r * r / 6 - r / 6) + (r * r * r * r / 12 - r * r / 12);
            BigInteger ret = C.subtract(R);

            BigInteger tmp1 = R.multiply(R).multiply(R).subtract(R).divide(new BigInteger("6"));
            BigInteger tmp2 = R.multiply(R).multiply(R).multiply(R).subtract(R.multiply(R)).divide(new BigInteger("12"));

            ret = ret.multiply(tmp1).add(tmp2).mod(MOD);

            out.println("Case #" + (line++) + ": " + ret);
        }

        in.close(); //关闭流并释放，这个很重要，否则是没有输出的
        out.close(); //关闭流并释放
    }

}
