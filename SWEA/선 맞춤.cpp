#include<iostream>
#include<algorithm>
#include<vector>
 
using namespace std;
 
int N;
int dp[10001];
pair<int, int> arr[10001];
 
int main(int argc, char** argv)
{
    cin.tie(0);
    ios::sync_with_stdio(0);
 
    int test_case;
    int T;
    cin >> T;
 
    int e, i;
    int x, y;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> e;
        for (i = 0; i < N; i++) {
            cin >> x >> y;
            arr[i] = { x, y };
        }
 
        fill(dp, dp + N, 10001);
        dp[0] = 0;
 
        double low_temp, high_temp, temp;
        double low, high;
        int next;
        int cur = 0;
        while (cur < N - 1) {
            next = cur + 1;
            high = (double)(arr[next].second + e - arr[cur].second) / (arr[next].first - arr[cur].first);
            low = (double)(arr[next].second - e - arr[cur].second) / (arr[next].first - arr[cur].first);
            dp[next] = min(dp[next], dp[cur]+1);
            next++;
 
            while (next < N) {
                high_temp = (double)(arr[next].second + e - arr[cur].second) / (arr[next].first - arr[cur].first);
                low_temp = (double)(arr[next].second - e - arr[cur].second) / (arr[next].first - arr[cur].first);
                if ((low_temp > high) | (low > high_temp)) {
                    // 역전
                    break;
                }
 
                high = min(high, high_temp);
                low = max(low, low_temp);
 
                temp = (double)(arr[next].second - arr[cur].second) / (arr[next].first - arr[cur].first);
                if ((low <= temp) & (temp <= high)) {
                    dp[next] = min(dp[next], dp[cur]+1);
                }
                next++;
            }
            cur++;
        }
 
        cout << '#' << test_case << ' ' << dp[N-1] << '\n';
    }
 
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}