#include<iostream>
 
#define MAX 1000001
#define ll long long
 
using namespace std;
 
int arr[MAX] = { 0, };
ll euler[MAX] = { 0, };
ll sum[MAX] = { 0, };
int a, b;
 
int main(int argc, char** argv)
{
    int test_case;
    int T, i, j;
 
    for (i = 2; i*i < MAX; i++) {
        if (arr[i] == 0) {
            for (j = 2; i*j < MAX; j++) {
                arr[i*j] = 1;
            }
        }
    }
 
    cin >> T;
 
    for (i = 1; i < MAX; i++) {
        euler[i] = i;
    }
 
    for (i = 2; i < MAX; i++) {
        if (arr[i] == 0) {
            for (j = 1; i*j <= MAX; j++) {
                euler[i*j] = (i - 1) * euler[i*j] / i;
            }
        }
    }
 
    sum[0] = 0;
    sum[1] = 1;
 
    for (i = 2; i < MAX; i++) {
        sum[i] = sum[i - 1] + euler[i];
    }
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> a >> b;
        cout << "#" << test_case << " " << sum[b] - sum[a-1] << "\n";
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}