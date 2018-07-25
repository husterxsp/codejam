import java.util.*;
import java.io.*;

import static java.lang.Math.sqrt;

public class Main {

    static int M, N, maxLevel, curLevel;
    static int[][] attack, upgrade;
    public static void main(String[] args) throws Exception {

        String path = "/Users/xushaopeng/Desktop/codejam/apac/2017/Round-A/";
        File file = new File(path + "D-small-practice.in");

        Scanner in = new Scanner(file);
        PrintWriter out = new PrintWriter(new FileWriter(path + "D-small-practice.out"));
//        Scanner in = new Scanner(System.in);
//        PrintWriter out = new PrintWriter(System.out);

        int T = in.nextInt(), line = 1;
        while (--T >= 0) {
            // M coins, N cards
            M = in.nextInt();
            N = in.nextInt();

            for (int i = 0; i < N; i++) {
                maxLevel = in.nextInt();
                curLevel = in.nextInt();


                for (int j = 1; j <= maxLevel; j++) {
                    attack[i][j] = in.nextInt();
                }
                for (int j = 0; j <= maxLevel - 1; j++) {
                    upgrade[i][j] = in.nextInt();
                }
            }

            // 静态方法不能调用非静态方法，所以需要实例化 Main
            out.println("Case #" + (line++) + ": " + (new Main()).clashRoyale());
        }

        in.close(); //关闭流并释放，这个很重要，否则是没有输出的
        out.close(); //关闭流并释放
    }

    private double clashRoyale() {
        double ret;

        double a = -C[0], b = (-2*C[0] + C[1]), c = C[1] + C[2] - C[0];

        ret = (-b + sqrt(b * b - 4 * a * c)) / (2*a);
        if (ret < -1 || ret > 1) ret = (-b - sqrt(b * b - 4 * a * c)) / (2*a);
        return ret;
    }

    private double flowerShop() {
        return 0;
    }

}
