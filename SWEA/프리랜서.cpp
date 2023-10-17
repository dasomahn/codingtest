#include <iostream>
#include <algorithm>
#include <cstring>
#include <tuple>
 
#define MAX 10001
#define t tuple<int, int, int>
 
using namespace std;
 
int N, M, maxPrice;
 
t plan[MAX]; // i 시작 날짜, { 끝나는 날짜, 가격 }
int dp[MAX];
 
bool cmp(t plan1, t plan2) {
    if (get<1>(plan1) == get<1>(plan2)) // 끝나는 날짜 같다면
        return get<0>(plan1) < get<0>(plan2);
    return get<1>(plan1) < get<1>(plan2);
}
 
int getJob(int target) {
    int idx = -1;
 
    for (int i = 0; i < target; i++) {
        if (get<0>(plan[target]) <= get<1>(plan[i])) {
            break;
        }
        idx = i;
    }
    if (idx == -1) {
        return 0;
    }
    return dp[idx];
}
 
int main(void)
{
    int test_case;
    int T, i;
    int s, e, c;
 
    scanf("%d", &T);
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> M;
        memset(dp, 0, sizeof(dp));
 
        for (i = 0; i < N; i++) {
            cin >> s >> e >> c;
            plan[i] = { s, e, c };
        }
 
        sort(plan, plan + N, cmp);
 
        dp[0] = get<2>(plan[0]);
 
        for (i = 1; i < N; i++) {
            dp[i] = max(dp[i - 1], get<2>(plan[i]) + getJob(i));
        }
 
        printf("#%d %d\n", test_case, dp[N - 1]);
 
    }
    return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}