import java.util.*;
import java.io.*;

public class Main {

    public static void main(String[] args) throws Exception {

        String path = "/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round/";
        File file = new File(path + "A-large-practice.in");

        System.out.print(file.exists());
        Scanner in = new Scanner(file);
        //Scanner in = new Scanner(System.in);

        PrintWriter out = new PrintWriter(new FileWriter(path + "A-large-practice.out"));
        // PrintWriter out = new PrintWriter(System.out);

        int T = in.nextInt(), line = 1;

        while (--T >= 0) {
            int N = in.nextInt();
            String[] persons = new String[N];

            in.skip("\n");

            while (--N >= 0) {
                persons[N] = in.nextLine();
            }
            // 静态方法不能调用非静态方法，所以需要实例化 Main
            String ret = (new Main()).countryLeader(persons);

            out.println("Case #" + (line++) + ": " + ret);
        }

        in.close(); //关闭流并释放，这个很重要，否则是没有输出的
        out.close(); //关闭流并释放
    }
    private String countryLeader(String[] persons) {
        Map<String, Integer> myMap = new TreeMap();
        for (String s : persons) {
            Set<Character> tmp = new HashSet<Character>();
            for (char c : s.toCharArray()) {
                if (c != ' ') {
                    tmp.add(c);
                }
            }

            myMap.put(s, tmp.size());
        }
        String ret = "";
        int letters = 0;

        for (Map.Entry<String, Integer> entry : myMap.entrySet()) {
            if (entry.getValue() > letters) {
                letters = entry.getValue();
                ret = entry.getKey();
            }
        }
        return ret;
    }
}
