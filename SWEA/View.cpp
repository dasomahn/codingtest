#include<iostream>
 
using namespace std;
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
     
    //freopen("input.txt", "r", stdin);
    cin>>T;

    int num;
    int arr[1001];
     
    int ans;
    int lmax, rmax;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        ans = 0;
 
        cin >> num;
        for (int j = 0; j < num; j++) {
            cin >> arr[j]; // input
        }
 
        for (int j = 2; j < num-1; j++) {
            lmax = max(arr[j - 2], arr[j - 1]);
            rmax = max(arr[j + 2], arr[j + 1]);
 
            if ((max(lmax, arr[j]) == arr[j]) &&
                max(rmax, arr[j]) == arr[j]) {
                ans += arr[j] - max(lmax, rmax);
            }
        }
 
        cout << "#" << test_case << " " << ans << endl;
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}