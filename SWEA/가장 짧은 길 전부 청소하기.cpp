#include<iostream>
#include<vector>
#include<queue>
 
#define MAX 200001
#define MAX_DIST 1000000000
 
using namespace std;
 
long long dijkstra[MAX];
int score[MAX];
vector<pair<int, int>> graph[MAX];
 
int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int test_case;
    int T;
    cin >> T;
 
    int N = 0, M;
    int i, cur;
    int a, b;
    long long dist, ans;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        for (i = 0; i <= N; i++) {
            graph[i].clear();
        }
 
        cin >> N >> M;
        fill(dijkstra, dijkstra + N + 1, (long long)MAX * MAX_DIST);
 
        for (i = 0; i < M; i++) {
            cin >> a >> b >> dist;
            graph[a].emplace_back(b, dist);
            graph[b].emplace_back(a, dist);
        }
 
        // dijkstra
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.emplace(0, 1); // 거리, 노드
        dijkstra[1] = 0;
        score[1] = 0;
 
        while (!pq.empty()) {
            dist = pq.top().first;
            cur = pq.top().second;
            pq.pop();
 
            if (dist > dijkstra[cur]) {
                continue;
            }
 
            for (pair<int, int> v : graph[cur]) {
                if (dijkstra[v.first]  >  v.second + dist) {
                    dijkstra[v.first] = v.second + dist;
                    score[v.first] = v.second;
                    pq.emplace(v.second+dist, v.first);
                }
                else if (dijkstra[v.first] == v.second + dist) {
                    score[v.first] = min(v.second, score[v.first]);
                }
            }
        }
 
        ans = 0;
        for (i = 1; i <= N; i++) {
            ans += score[i];
        }
        cout << "#" << test_case << " " << ans << "\n";
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}