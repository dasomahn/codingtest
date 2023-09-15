#include<iostream>
#include<algorithm>
#include<queue>
#include<tuple>
 
using namespace std;
 
int parent[50001];
int N, M;
 
int getParent(int x) {
    if (parent[x] == x) {
        return x;
    }
    return parent[x] = getParent(parent[x]);
}
 
void unionFind(int a, int b) {
    a = getParent(a);
    b = getParent(b);
 
    parent[max(a, b)] = min(a, b);
}
 
int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int test_case;
    int T;
    cin >> T;
 
    int i, res, cnt;
    int v1, v2, w;
 
    long long ans;
    vector<tuple<int, int, int>> vec;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        ans = cnt = 0;
        vec.clear();
 
        cin >> N >> M;
        for (i = 1; i <= N; i++) {
            parent[i] = i;
        }
 
        for (i = 0; i < M; i++) {
            cin >> v1 >> v2 >> w;
            vec.emplace_back(w, v1, v2);
        }
        sort(vec.begin(), vec.end());
 
        for (tuple<int, int, int> temp : vec) {
            v1 = get<1>(temp);
            v2 = get<2>(temp);
            w = get<0>(temp);
 
            if (getParent(v1) != getParent(v2)) {
                unionFind(v1, v2);
                ans += w;
                cnt++;
 
                if (cnt == N - 1) break;
            }
        }
 
        cout << '#' << test_case << ' ' << ans << '\n';
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}