#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
 
using namespace std;
 
bool visited[11];
vector<int> graph[11];
int N=0, K;
int M_dist;
 
void dfs(int root, int d) {
    M_dist = max(M_dist, d);
 
    for (int next : graph[root]) {
        if (!visited[next]) {
            visited[next] = 1;
            dfs(next, d + 1);
            visited[next] = 0;
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
 
    int i, j, M;
    int s, e;
    int flag;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cout << "#" << test_case << " ";
        for (i = 0; i <= N; i++) {
            graph[i].clear();
        }
        M_dist = 0;
         
        cin >> N >> K;
 
        for (i = 0; i < K; i++) {
            cin >> M;
            flag = 1;
            for (j = 0; j < M; j++) {
                if (flag) {
                    flag = 0;
                    cin >> s;
                }
                else {
                    cin >> e;
                    vector<int> v = graph[s];
                    if (find(v.begin(), v.end(), e) == v.end()) {
                        graph[s].emplace_back(e);
                    }
                    s = e;
                }
            }
        }
 
        // dfs
        for (i = 1; i <= N; i++) {
            memset(visited, 0, 11);
            visited[i] = 1;
            dfs(i, 1);
            cout << graph[i].size() << " ";
        }
 
        cout << M_dist << "\n";
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}