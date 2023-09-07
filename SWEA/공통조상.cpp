#include<iostream>
#include<vector>
 
using namespace std;
 
vector<int> graph[10001];
int height[10001];
int parent[10001];
 
void get_info(int v, int h) {
    height[v] = h;
    for (int i = 0; i < graph[v].size(); i++) {
        parent[graph[v][i]] = v;
        get_info(graph[v][i], h + 1);
    }
}
 
int get_sub(int v) {
    int x = 1;
    for (int i = 0; i < graph[v].size(); i++) {
        x += get_sub(graph[v][i]);
    }
 
    return x;
}
 
int main(int argc, char** argv) {
    int test_case;
    int T;
    cin >> T;
 
    int V, E, v1, v2;
    V = 1;
 
    int in, out, i;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        // 초기화
        for (i = 1; i <= V; i++) {
            graph[i].clear();
        }
 
        cin >> V >> E >> v1 >> v2;
 
        for (i = 0; i < E; i++) {
            cin >> in >> out;
            graph[in].push_back(out);
        }
 
        // 높이 및 부모 저장
        get_info(1, 1);
 
        int h1, h2;
        h1 = height[v1];
        h2 = height[v2];
 
        int p1, p2;
        p1 = parent[v1];
        p2 = parent[v2];
 
        if (h1 > h2) {
            while (h1-- != h2) {
                p1 = parent[p1];
            }
        }
        else if (h1 < h2) {
            while (h1 != h2--) {
                p2 = parent[p2];
            }
        }
 
        while (p1 != p2) {
            p1 = parent[p1];
            p2 = parent[p2];
        }
 
        cout << "#" << test_case << " " << p1 << " " << get_sub(p1) << endl;
    }
    return 0;
}