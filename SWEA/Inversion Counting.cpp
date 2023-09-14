#include<iostream>
 
using namespace std;
 
int arr[100000];
int temp[100000];
long long cnt;
 
void divide(int left, int right) {
    if (left >= right) {
        return;
    }
 
    int mid = (left + right) >> 1;
    divide(left, mid);
    divide(mid + 1, right);
 
    // 합병
    int i = 0;
    int j = 0;
    while ((i <= mid - left) & (j < right - mid)) {
        if (arr[left + i] > arr[mid + 1 + j]) {
            temp[i + j] = arr[mid + 1 + j];
            j++;
        }
        else {
            temp[i + j] = arr[left + i];
            i++;
            cnt += j;
        }
    }
 
    while (i <= mid - left) {
        temp[i + j] = arr[left + i];
        i++;
        cnt += j;
    }
    while (j < right - mid) {
        temp[i + j] = arr[mid + 1 + j];
        j++;
    }
 
    for (int idx = 0; idx <= right - left; idx++) {
        arr[left + idx] = temp[idx];
    }
}
 
int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int test_case;
    int T;
 
    cin >> T;
 
    int N;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cnt = 0;
 
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }
 
        divide(0, N - 1);
 
        cout << '#' << test_case << ' ' << cnt << '\n';
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}