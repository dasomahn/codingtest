#include<iostream>
#include<algorithm>
#include<stack>
 
using namespace std;
 
int N;
pair<int, int> pos[100000];
 
long long ccw(pair<int, int> a, pair<int, int> b) {
    return (long long)a.first * b.second - (long long)b.first * a.second;
}
 
long long ccw(pair<int, int> p, pair<int, int> q, pair<int, int> r) {
    return ccw({ p.first - q.first, p.second - q.second },
               { p.first - r.first, p.second - r.second });
}
 
bool compare(pair<int, int> a, pair<int, int> b) {
    long long ans = ccw(pos[0], a, b);
 
    if (ans != 0) return (ans > 0);
 
    if (a.first != b.first) {
        return (abs(a.first) < abs(b.first)); // x좌표 작은 순으로
    }
    return (abs(a.second) < abs(b.second));
}
 
int main(int argc, char** argv)
{
    cin.tie(0);
    ios::sync_with_stdio(0);
     
    int test_case;
    int T;
    cin >> T;
 
    int i, temp_i;
    int x, y;
    int cnt;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
 
        temp_i = 0;
 
        for (i = 0; i < N; i++) {
            cin >> x >> y;
            pos[i].first = x;
            pos[i].second = y;
 
            if (pos[temp_i].second == y) {
                if (pos[temp_i].first > x)
                    temp_i = i;
            }
            else if (pos[temp_i].second > y) {
                temp_i = i;
            }
        }
        swap(pos[0], pos[temp_i]);
        sort(pos + 1, pos + N, compare);
 
         
        stack<pair<int, int>> q;
 
        for (i = 0; i < 2; i++) {
            q.push(pos[i]);
        }
 
        pair<int, int> start;
        pair<int, int> mid;
        pair<int, int> end;
        long long cal;
         
        temp_i = 2;
        while (temp_i < N) {
            if (q.size() == 1) {
                q.push(end);
                temp_i++;
            }
            mid = q.top();
            q.pop();
            start = q.top();
            end = pos[temp_i];
 
            cal = ccw(start, mid, end);
 
            if (cal <= 0) { 
                 
            }
            else { // cal > 0, 좌회전일때
                q.push(mid);
                q.push(end);
                temp_i++;
            }
        }
 
        cout << '#' << test_case << ' ' << q.size() << '\n';
    }
 
 
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}