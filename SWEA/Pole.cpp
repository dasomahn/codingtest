#include<iostream>
 
using namespace std;
 
long long arr[21][21][21] = { 0 };
int N, L, R;
 
int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int test_case;
    int T;
    cin >> T;
 
    arr[1][1][1] = 1;
 
    int i, j, k;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> L >> R;
        for (i = 2; i <= N; i++) {
            for (j = 1; j <= L; j++) {
                for (k = 1; k <= R; k++) {
                    if (arr[i][j][k] == 0) {
                        arr[i][j][k] = arr[i - 1][j - 1][k]
                                     + arr[i - 1][j][k - 1]
                                     + arr[i - 1][j][k] * (i - 2);
                    }
                }
            }
        }
 
        cout << '#' << test_case << ' ' << arr[N][L][R] << '\n';
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}