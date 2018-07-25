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
    static int N, L1, R1, A, B, C1, C2, M;
    static Interval[] intervals;

    public static void main(String[] args) throws Exception {

        long start = System.currentTimeMillis();

        String path = "/Users/xushaopeng/Desktop/codejam/apac/2017/Round-B/";
        File file = new File(path + "C-large-practice.in");

        Scanner in = new Scanner(file);
        PrintWriter out = new PrintWriter(new FileWriter(path + "C-large-practice.out"));

//        in = new Scanner(System.in);
//        out = new PrintWriter(System.out);

        int T = in.nextInt(), line = 1;
        while (--T >= 0) {
            N = in.nextInt();
            L1 = in.nextInt();
            R1 = in.nextInt();
            A = in.nextInt();
            B = in.nextInt();
            C1 = in.nextInt();
            C2 = in.nextInt();
            M = in.nextInt();

            intervals = new Interval[N];

            long x = L1, y = R1;
            if (line == 19) {
//                System.out.println(1);
            }

            intervals[0] = new Interval(L1, R1);

            for (int i = 1; i < N; i++) {
                long tmpx = (A * x + B * y + C1) % M;
                long tmpy = (A * y + B * x + C2) % M;
                x = tmpx;
                y = tmpy;

                /*
                 * 注意题中的要求
                 * Li = min(xi, yi) and Ri = max(xi, yi),
                 * */
                intervals[i] = new Interval(min(x, y), max(x, y));
            }

            Arrays.sort(intervals);

            System.err.println("Case #" + (line));
            out.println("Case #" + (line++) + ": " + (Main.calcTotal() - Main.maxCovered()) );
        }

        in.close();
        out.close();

        System.err.println(String.format("Time used: %.3fs", (System.currentTimeMillis() - start) / 1000.0));
    }

    /*
    * 计算所有区间的并
    * 一开始想的是for循环两边遍。。。
    * 参考，排序后其实一遍就可以。。。
    *
    * 计算区间和的 模板代码，注意记忆。
    *
    * */
    static long calcTotal() {
        long ret = 0, start = 0, end = -1;
        for (Interval interval : intervals) {
            if (interval.start > end) {
                ret += end - start + 1;
                start = interval.start;
                end = interval.end;
            }
            else {
                end = max(interval.end, end);
            }
        }

        ret += end - start + 1;
        return ret;
    }

    /*
    * 计算每个区间单独覆盖的最大值。
    *
    * */
    static long maxCovered() {
        long last = -1;

        Interval pre = intervals[0];
        pre.weight = pre.end - pre.start + 1;

/*
last值为pre区间已经被减掉的部分点的最大值
如 pre = [1,5], cur = [2,3]
那么cur区间相当于完全被覆盖，被完全减掉。即cur.weight = 0;
pre 区间减掉 cur 后，剩下 [1,1]和[4,5], 被减掉的部分的最大值是 last = 3;

*/
        for (int i = 1; i < N; i++) {
            Interval cur = intervals[i];
//            注意分析，排序后，关于区间的三种关系。
//            相离
            if (cur.start > pre.end) {
                cur.weight = cur.end - cur.start + 1;
                pre = cur;

                last = cur.start - 1;
            }
//            覆盖
            else if (cur.end <= pre.end) {
                cur.weight = 0;
                /*
                cur.start <= cur.end是肯定的。
                那么如果 last + 1 > cur.end , 说明cur区间覆盖的点在pre中已经都减过了，不用再减了。
                */
                pre.weight -= max(cur.end - max(last + 1, cur.start) + 1, 0);

                last = max(cur.end, last);
            }
//            相交
            else {
                pre.weight -= pre.end - max(last + 1, cur.start) + 1;
                cur.weight = cur.end - pre.end;
                last = pre.end;

                pre = cur;
            }
        }

        long ret = 0;
        for (Interval interval : intervals) ret = max(interval.weight, ret);
        return ret;
    }
}
