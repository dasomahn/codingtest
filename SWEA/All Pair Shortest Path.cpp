#include<iostream>
#include<algorithm>
#include<cstring>
 
#define DIST 5000000
#define MAX 501
 
using namespace std;
 
int graph[MAX][MAX];
 
int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int test_case, T;
    int N, M;
    int a, b, c, i;
 
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> M;
        fill_n(&graph[0][0], MAX*MAX, DIST);
 
 
        for (i = 0; i < M; i++) {
            cin >> a >> b >> c;
 
            graph[a][b] = min(graph[a][b], c);
        }
 
        for (c = 1; c <= N; c++) {
            for (a = 1; a <= N; a++) {
                for (b = 1; b <= N; b++) {
                    graph[a][b] = min(graph[a][b], graph[a][c] + graph[c][b]);
                }
            }
        }
 
        cout << "#" << test_case << " ";
        for (a = 1; a <= N; a++) {
            for (b = 1; b <= N; b++) {
                if (a == b) {
                    cout << 0 << " ";
 
                }
                else if (graph[a][b] == DIST) {
                    cout << -1 << " ";
                }
                else {
                    cout << graph[a][b] << " ";
                }
            }
        }
        cout << "\n";
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}