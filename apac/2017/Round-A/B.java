/**
 木桶、积水

 参看 leetcode 407
 http://www.cnblogs.com/grandyang/p/5928987.html

 参考 https://www.byvoid.com/zhs/blog/poi-1999-wod

 思路
 一开始只把边界点加入队列。 从边界开始bfs

 有点不是很懂。待再看
 */


import java.util.*;
import java.io.*;

class Comp implements Comparator<Point> {
    @Override
    public int compare(Point a, Point b) {
        return a.h > b.h ? 1 : -1;
    }
}

class Point {
    int x, y, h;
    public Point(int x, int y, int h) {
        super();
        this.x = x;
        this.y = y;
        this.h = h;
    }
}
public class Main {
    public static int r, c;
    public static int[][] height;
    private static int[][] vis;
    private static int[][] dir = {{-1, 0},{1, 0},{0, -1},{0, 1}};

    private static PriorityQueue<Point> que;

    public static void main(String[] args) throws Exception {

        String path = "/Users/xushaopeng/Desktop/codejam/apac/2017/Round-A/";
        File file = new File(path + "B-large-practice.in");

        Scanner in = new Scanner(file);
        PrintWriter out = new PrintWriter(new FileWriter(path + "B-large-practice.out"));
//        Scanner in = new Scanner(System.in);
//        PrintWriter out = new PrintWriter(System.out);
//
        int T = in.nextInt(), line = 1;

        while (--T >= 0) {
            r = in.nextInt();
            c = in.nextInt();

            height = new int[r][c];
            vis = new int[r][c];

//            PriorityQueue<Node> pq = new PriorityQueue<Node>(initCapacity, new Comparator<Node>() {
//                public int compare(Node n1, Node n2) {
//                }
//            });
            que = new PriorityQueue<Point>(new Comp());

            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    height[i][j] = in.nextInt();
                }
            }
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (!(i == 0 || i == r - 1 || j == 0 || j == c - 1)) continue;

                    Point point = new Point(i, j, height[i][j]);
                    que.add(point);
                    vis[i][j] = 1;
                }
            }

            // 静态方法不能调用非静态方法，所以需要实例化 Main
            out.println("Case #" + (line++) + ": " + (new Main()).rain());
        }

        in.close(); //关闭流并释放，这个很重要，否则是没有输出的
        out.close(); //关闭流并释放
    }
    // 非递归解
    public int rain1() {
        int ret = 0, h = 0;

        while (!que.isEmpty()) {

            Point point = que.poll();
            h = Math.max(h, point.h);

            for (int i = 0; i < 4; i++) {
                int x = point.x + dir[i][0];
                int y = point.y + dir[i][1];
                if (x < 0 || y < 0 || x > r - 1 || y > c - 1 || vis[x][y] == 1) continue;
                vis[x][y] = 1;

                if (height[x][y] < h) ret += h - height[x][y];

                que.add(new Point(x, y, height[x][y]));
            }
        }
        return ret;
    }

    // 递归解
    public int rain() {
        int ret = 0, h = 0;

        while (!que.isEmpty()) {
            Point point = que.poll();

            h = point.h;
            for (int i = 0; i < 4; i++) {
                int x = point.x + dir[i][0];
                int y = point.y + dir[i][1];
                if (x < 0 || y < 0 || x > r - 1 || y > c - 1 || vis[x][y] == 1) continue;

                ret += floodfill(x, y, h);
            }
        }
        return ret;
    }
    public int floodfill(int x, int y, int h) {
        vis[x][y] = 1;

        int ret = 0;
        if (height[x][y] >= h)  {
            que.add(new Point(x, y, height[x][y]));
        }
        else {
            ret += h - height[x][y];
            for (int i = 0; i < 4; i++) {
                int tmpx = x + dir[i][0];
                int tmpy = y + dir[i][1];
                if (tmpx < 0 || tmpy < 0 || tmpx > r - 1 || tmpy > c - 1 || vis[tmpx][tmpy] == 1) continue;

                ret += floodfill(tmpx, tmpy, h);
            }
        }
        return ret;
    }
}
