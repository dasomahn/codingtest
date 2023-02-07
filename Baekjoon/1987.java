import java.util.Stack;
import java.util.Scanner;

public class main
{
    public static int answer = 1;
    public static char[][] map;
    public static boolean[] visited = new boolean[26];
    public static int[][] direction = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    public static int row, col;

    public static void main(String args[]) throws Exception
    {
        Scanner sc = new Scanner(System.in);

        row = sc.nextInt();
        col = sc.nextInt();
        sc.nextLine(); // 버퍼 비우기

        map = saveMap(sc);
        trip(0, 0, 0);

        System.out.println(answer);
        sc.close();
    }

    public static char[][] saveMap(java.util.Scanner sc) {
        map = new char[row][col];
        for (int i=0; i<row; i++) {
            map[i] = sc.nextLine().toCharArray();
        }
        return map;
    }

    public static void trip(int r, int c, int cnt) {
        if (visited[map[r][c] - 'A']) {
            answer = Math.max(answer, cnt);
        }
        else {
            visited[map[r][c] - 'A'] = true;

            for (int[] dir : direction) {
                int nextR = r + dir[0];
                int nextC = c + dir[1];

                if (nextR >= 0 && nextC >= 0 && nextR < row && nextC < col) {
                    trip(nextR, nextC,cnt + 1);
                }
            }

            visited[map[r][c] - 'A'] = false;
        }
    }
}