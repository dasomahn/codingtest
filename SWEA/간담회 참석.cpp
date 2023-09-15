#include<iostream>
#include<vector>
#include<queue>
 
#define MAX 50001
 
using namespace std;
 
vector<pair<int, int>> in[MAX];
vector<pair<int, int>> out[MAX];
 
int in_dist[MAX];
int out_dist[MAX];
 
void dijkstra(int start) {
    pair<int, int> cur; // dist, node
    int cur_dist, cur_node, next_dist, next_node;
 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
     
    // 회의실까지 가기
    pq.emplace(0, start);
    out_dist[start] = 0;
    while (!pq.empty()) {
        cur_dist = pq.top().first;
        cur_node = pq.top().second;
 
        pq.pop();
        for (pair<int, int> next : out[cur_node]) {
            next_dist = next.first;
            next_node = next.second;
 
            if (out_dist[next_node] > cur_dist + next_dist) {
                out_dist[next_node] = cur_dist + next_dist;
                pq.emplace(out_dist[next_node], next_node);
            }
        }
    }
 
    // 회의실에서 돌아가기
    pq.emplace(0, start);
    in_dist[start] = 0;
    while (!pq.empty()) {
        cur_dist = pq.top().first;
        cur_node = pq.top().second;
         
        pq.pop();
        for (pair<int, int> next : in[cur_node]) {
            next_dist = next.first;
            next_node = next.second;
 
            if (in_dist[next_node] > cur_dist + next_dist) {
                in_dist[next_node] = cur_dist + next_dist;
                pq.emplace(in_dist[next_node], next_node);
            }
        }
    }
}
 
int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int test_case;
    int T;
    cin >> T;
 
    int N, M, X;
    int i, s, e, t;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> M >> X;
 
        for (i = 0; i <= N; i++) {
            in[i].clear();
            out[i].clear();
        }
 
        for (i = 0; i < M; i++) {
            cin >> s >> e >> t;
            out[s].emplace_back(t, e);
            in[e].emplace_back(t, s);
        }
 
        fill_n(in_dist, N + 1, MAX*N);
        fill_n(out_dist, N + 1, MAX*N);
        dijkstra(X);
 
        int ans = 0;
        for (i = 1; i <= N; i++) {
            ans = max(ans, in_dist[i] + out_dist[i]);
        }
 
        cout << '#' << test_case << ' ' << ans << '\n';
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}