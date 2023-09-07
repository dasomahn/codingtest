#include<iostream>
#include<cstring>
#include<queue>
 
using namespace std;
 
int main(int argc, char** argv) {
    int test_case;
    int T = 10;
 
    int v, e;
    int in[1001];
    queue<int> out[1001];
    queue<int> q;
    int i;
    int cur, temp, chk;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        memset(in, 0, sizeof(int) * 1001);
 
        cin >> v >> e;
 
        for (i = 0; i < e; i++) {
            cin >> temp >> chk;
            out[temp].push(chk);
            in[chk]++;
        }
 
 
        for (i = 1; i <= v; i++) {
            if (in[i] == 0) {
                q.push(i);
            }
        }
 
        cout << "#" << test_case << " ";
        while (!q.empty()) {
            cur = q.front();
            q.pop();
            cout << cur << " ";
 
            temp = out[cur].size();
            for (i = 0; i < temp; i++) {
                chk = out[cur].front();
                in[chk]--;
                if (in[chk] == 0)
                    q.push(chk);
                out[cur].pop();
            }
        }
        cout << "\n";
    }
    return 0;
}