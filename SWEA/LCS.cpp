#include<iostream>
#include<cstring>
 
#define MAX 1001
 
using namespace std;
 
char dna1[MAX];
char dna2[MAX];
 
int dp[MAX][MAX]{ 0, };
 
int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int test_case;
    int i, j, T;
    int l1, l2;
 
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> dna1 >> dna2;
 
        l1 = strlen(dna1);
        l2 = strlen(dna2);
         
        for (i = 1; i <= l1; i++) {
            for (j = 1; j <= l2; j++) {
                if (dna1[i - 1] != dna2[j - 1]) {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
                else {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
            }
        }
 
 
        cout << "#" << test_case << " " << dp[l1][l2] << "\n";
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}