#include<iostream>
#include<algorithm>
#include<cstring>
 
#define MAX 1000
 
using namespace std;
 
int N, M;
char map[MAX][MAX];
int dp[MAX][MAX];
 
int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
     
    int test_case;
    int T;
    int i, j;
     
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
        M = 0;
 
        for (i = 0; i < N; i++) {
            cin >> map[i];
        }
 
        memset(dp, 0, sizeof(dp));
 
        for (i = 0; i < N; i++) {
            if (map[i][0] == '0') dp[i][0] = 1;
            if (map[0][i] == '0') dp[0][i] = 1;
        }
 
        for (i = 1; i < N; i++) {
            for (j = 1; j < N; j++) {
                if (map[i][j] == '0') {
                    dp[i][j] = min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] }) + 1;
                    M = max(M, dp[i][j]);
                }
            }
        }
 
        cout << "#" << test_case << " " << M << "\n";
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}