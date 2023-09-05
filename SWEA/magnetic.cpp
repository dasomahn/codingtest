#include<iostream>

using namespace std;

int main(int argc, char** argv) {
    int test_case;
    int T = 10;
 
    char arr[100][201];
    int ans, n;
    int flag, i, j;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        ans = 0;
 
        cin >> n;
        cin.ignore();
 
        // 입력 받기
        for (i = 0; i < n; i++) cin.getline(arr[i], 2*n+1);
 
        j = 0;
        // 세로줄 보기
        while (j < 2 * n) {
            flag = 0;
 
            for (i = 0; i < n; i++) {
                if (arr[i][j] == '2') {
                    if (flag) {
                        ans++;
                        flag ^= 1;
                    }
                } else if (arr[i][j] == '1') {
                    flag = 1;
                }
            }
 
            j += 2;
        }
 
        // 출력
        cout << "#" << test_case << " " << ans << endl;
    }
    return 0;
}