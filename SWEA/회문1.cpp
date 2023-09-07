#include<iostream>
#include<string>
 
using namespace std;
 
const int n = 8;
char board[n+1][n+1];
int len;
 
int check_hor(int r, int c) {
    for (int i = 0; i < len / 2; i++) {
        if (board[r][c + i] != board[r][c + len - i - 1])
            return 0;
    }
    return 1;
}
 
int check_ver(int r, int c) {
    for (int i = 0; i < len / 2; i++) {
        if (board[r + i][c] != board[r + len - i - 1][c])
            return 0;
    }
    return 1;
}
 
int main(int argc, char** argv) {
    int test_case;
    int T = 10;
 
    int ans;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> len;
        cin.ignore();
 
        // 입력받기
        for (int i = 0; i < n; i++) {
            cin.getline(board[i], n+1);
        }
 
        ans = 0;
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < n + 1 - len; c++) {
                ans += check_hor(i, c);
                ans += check_ver(c, i);
            }
        }
 
        // 출력
        cout << "#" << test_case << " " << ans << endl;
    }
    return 0;
}