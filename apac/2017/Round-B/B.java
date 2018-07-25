/**
 1. calcPower 函数中是对K取模。。一开始搞错成对MOD取模了。。

 写起来有些麻烦。。。

 难点：
 1. N -> K的优化
 2. K^2 -> K的优化
 */

import java.util.*;
import java.io.*;

public class Main {

    static int A, B, K, MOD = 1000000007;
    static long N;

    public static void main(String[] args) throws Exception {

        long start = System.currentTimeMillis();

        String path = "/Users/xushaopeng/Desktop/codejam/apac/2017/Round-B/";
        File file = new File(path + "B-small-practice.in");

        Scanner in = new Scanner(file);
        PrintWriter out = new PrintWriter(new FileWriter(path + "B-small-practice.out"));

//        in = new Scanner(System.in);
//        out = new PrintWriter(System.out);

        int T = in.nextInt(), line = 1;
        while (--T >= 0) {
            A = in.nextInt();
            B = in.nextInt();
            N = in.nextLong();
            K = in.nextInt();

            if (line == 18) {
                System.err.println("Case #" + (line));
            }
            System.err.println("Case #" + (line));
            out.println("Case #" + (line++) + ": " + Main.gymSecrets());
        }

        in.close();
        out.close();

        System.err.println(String.format("Time used: %.3fs", (System.currentTimeMillis() - start) / 1000.0));
    }

    // 计算幂次 (a ^ b) % mod，递归，分治
    private static int power(long a, long b, int mod) {
        if (b == 0) return 1 % mod;
        long half = power(a, b / 2, mod);
        long ret = (half * half) % mod;

        if (b % 2 == 0) return (int)ret;
        return (int)(ret * a % mod);
    }

    // 迭代，跟下面的一样。。。
    private static int power_itor(long a, long b, int mod) {
        if (b == 0) return 1 % mod;
        long ret = 1;
        for (; b != 0; b /= 2) {
            if (b % 2 == 1) ret = (ret * a) % mod;
            a = (a * a) % mod;
        }

        return (int)(ret % mod);
    }

    //    比如求x的21次方，21的二进制为10101,由于x21=x^16*x^4*x^1，可以看出根据二进制表示(10101)，每当遇到1时，则乘以x，从右向左前进一位则将x自乘。
    private static int quickPower(long a, long b, long mod) {
        long ret = 1;
        while (b > 0) {
            if ((b & 1) != 0) {
                ret = (ret * a) % mod;
            }
            a = a * a % mod;
            b >>= 1;
        }
        return (int)(ret % mod);
    }

    private static long gymSecrets() {
        long ret;
        // iArr, jArr 保存取模后的值
        int[] iArr = new int[K + 1], jArr = new int[K + 1];

        // 保存对应取模的值的个数
        long[] iCnt = new long[K + 1], jCnt = new long[K + 1];

        for (int i = 1; i <= K; i++) {
            iArr[i] = power_itor(i, A, K);
            jArr[i] = power_itor(i, B, K);
        }

        long times = N / K, remain = N % K;
        for (int i = 1; i <= K; i++) {
            iCnt[iArr[i]] = (iCnt[iArr[i]] + times + (i <= remain ? 1 : 0)) % MOD;
            jCnt[jArr[i]] = (jCnt[jArr[i]] + times + (i <= remain ? 1 : 0)) % MOD;
        }

//       先计算 i^A 和 j^B都能刚好被整除的情况。iCnt[0] 和 jCnt[0]
        ret = iCnt[0] * jCnt[0] % MOD;
//        这里的for循环表示 i^A % K 的范围 [1, K - 1]，即但是i^A无法被整除的情况。
        for (int i = 1; i < K; i++) {
            ret = (ret + iCnt[i] * jCnt[K - i]) % MOD;
        }

        // 但是上面的计算包含重复，以下这里去重。
        long invalid = 0;
        for (int i = 1; i <= K; i++) {
            int j = i;
            if ((iArr[i] + jArr[j]) % K == 0) {
                invalid = (invalid + times + (i <= remain ? 1 : 0)) % MOD;
            }
        }
        ret -= invalid;
        if (ret < 0) ret += MOD;
        return ret;
    }
}
