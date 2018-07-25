/**
    又是区间问题。第一反应，排序，贪心。

 https://blog.csdn.net/ihsin/article/details/54838071
 https://blog.csdn.net/jacketinsysu/article/details/52367965

 总体思路：
 1. 计算所有区间总共覆盖的点 calcTotal(), 模板代码
 2. 计算所有区间分别单独覆盖的点。取其最大 maxCovered。
 3. total - maxCovered

 参考：https://stlighter.github.io/2016/09/15/Round-B-APAC-Test-2017-%E9%A2%98%E8%A7%A3/

 关键：区间计算那部分，将两层for循环转换为一层for循环。

 */

import javafx.util.Pair;
import org.omg.CORBA.INTERNAL;

import java.lang.reflect.Array;
import java.util.*;
import java.io.*;

import static java.lang.Math.max;
import static java.lang.Math.min;

class Interval implements Comparable<Interval> {
    long start, end, weight = 0;
    public Interval(long start, long end) {
        this.start = start;
        this.end = end;
    }
    @Override
    public int compareTo(Interval a) {
        if (this.start - a.start == 0) return (int)(this.end - a.end);
        return (int)(this.start - a.start);
    }
}

public class Main {
    static int N, M;

    public static void main(String[] args) throws Exception {

        long start = System.currentTimeMillis();

        String path = "/Users/xushaopeng/Desktop/codejam/apac/2017/Round-B/";
        File file = new File(path + "D-small-practice.in");

        Scanner in = new Scanner(file);
        PrintWriter out = new PrintWriter(new FileWriter(path + "D-small-practice.out"));

//        in = new Scanner(System.in);
//        out = new PrintWriter(System.out);

        int T = in.nextInt(), line = 1;
        while (--T >= 0) {
            N = in.nextInt();
            M = in.nextInt();
            System.err.println("Case #" + (line));
            out.println("Case #" + (line++) + ": " + (Main.calcTotal() - Main.maxCovered()) );
        }

        in.close();
        out.close();

        System.err.println(String.format("Time used: %.3fs", (System.currentTimeMillis() - start) / 1000.0));
    }

}
