#include<iostream>
#include<algorithm>
 
using namespace std;
 
int arr[200001];
int cum[200001];
int i, N;
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
 
    //freopen("input_최대 부분 배열.txt", "r", stdin);
    cin >> T;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
 
        for (i = 0; i < N; i++) {
            cin >> arr[i];
        }
         
        int M = arr[0];
        cum[0] = arr[0];
        for (i = 1; i < N; i++) {
            cum[i] = max(arr[i], cum[i-1] + arr[i]);
            M = max(M, cum[i]);
        }
         
        cout << "#" << test_case << " " << M << endl;
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}