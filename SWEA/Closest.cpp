#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
 
using namespace std;
 
pair<int, int> pos[100000];
pair<int, int> temp[100000];
int N;
 
long long dist(pair<int, int> p1, pair<int, int> p2) {
    return pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2);
}
 
long long get_dist(int l, int r) {
    if (l + 1 == r) return dist(pos[l], pos[r]);
 
    long long m = dist(pos[l + 1], pos[l + 2]);
    m = min(m, dist(pos[l], pos[l + 1]));
    m = min(m, dist(pos[l], pos[l + 2]));
    return m;
}
 
long long divide_and_conquer(int s, int e) {
    long long dl, dr, d;
 
    if (e - s <= 2) {
        return get_dist(s, e); // 2개, 3개
    }
 
    int m = (s + e) / 2;
    dl = divide_and_conquer(s, m);
    dr = divide_and_conquer(m + 1, e);
 
    d = min(dl, dr);
 
    // conquer
    double x_mid = (pos[m].first + pos[m + 1].first) >> 1;
    double xl = x_mid - d;
    double xr = x_mid + d;
 
    vector<pair<int, int>> list; // x boundary 안에 있는 것들
 
    // merge sort
    int l = s;
    int r = m + 1;
 
    int idx = 0; // temp array
    while ((l <= m) & (r <= e)) {
 
        if (pos[l].second < pos[r].second) {
            temp[idx] = pos[l];
            l++;
        }
        else {
            temp[idx] = pos[r];
            r++;
        }
        if (pow(temp[idx].first - x_mid, 2) <= d) {
            list.emplace_back(temp[idx]);
        }
        idx++;
    }
 
    while (l <= m) {
        temp[idx] = pos[l];
        l++;
        if ((xl <= temp[idx].first) & (temp[idx].first <= xr)) {
            list.emplace_back(temp[idx]);
        }
        idx++;
    }
 
    while (r <= e) {
        temp[idx] = pos[r];
        r++;
        if ((xl <= temp[idx].first) & (temp[idx].first <= xr)) {
            list.emplace_back(temp[idx]);
        }
        idx++;
    }
 
    for (int i = 0; i < list.size(); i++) {
        int cnt = 1;
        while ((cnt <= 5) & (i + cnt < list.size())) {
            if (pow(list[cnt + i].second - list[i].second, 2) < d) {
                d = min(d, dist(list[i], list[i+cnt]));
            }
            cnt++;
        }
    }
    //cout << "\nd는 " << d << "\n";
 
    return d;
}
 
int main(int argc, char** argv)
{
    cin.tie(0);
    ios::sync_with_stdio(0);
 
    int test_case;
    int T;
    cin >> T;
 
    int i;
    int x, y;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
         
        for (i = 0; i < N; i++) {
            cin >> x >> y;
            pos[i].first = x;
            pos[i].second = y;
        }
        sort(pos, pos + N); // x 기준 오름차순 정렬
         
        cout << '#' << test_case << ' ' << divide_and_conquer(0, N - 1) << '\n';
    }
 
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}