#include <cstring>
#include <vector>
#include <queue>
 
#define rint register int
#define H_MAX 5001
#define B_MAX 50
#define D_MAX 50000
 
using namespace std;
 
int getBrand[H_MAX];
 
vector<pair<int, int>> graph[H_MAX]; // 호텔, 거리
int dist[H_MAX];
 
int n;
int min_a, min_b;
 
int root[B_MAX];
int num[B_MAX];
 
void dijkstra(int start, int brandA, int brandB) {
    int cur, d;
    bool found_a = false;
    bool found_b = false;
 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, start);
 
    while (!pq.empty()) {
        d = pq.top().first;
        cur = pq.top().second;
        pq.pop();
 
        if (dist[cur] < d) continue;
 
        if (cur != start) {
            rint brand = getRoot(getBrand[cur]);
            if (!found_a && brand == brandA) {
                found_a = true;
                min_a = d;
            }
            else if (!found_b && brand == brandB) {
                found_b = true;
                min_b = d;
            }
        }
 
        if (found_a & found_b) break;
 
        for (pair<int, int> g : graph[cur]) {
            if (g.first != start && d + g.second < dist[g.first]) {
                dist[g.first] = d + g.second;
                pq.emplace(d + g.second, g.first);
            }
        }
    }
}
 
void init(int N, int mBrands[])
{
    n = N;
    memset(num, 0, sizeof(num));
 
    rint i;
    for (i = 0; i < N; i++) {
        graph[i].clear();
 
        getBrand[i] = mBrands[i];
        num[mBrands[i]]++;
    }
     
 
    for (i = 0; i < B_MAX; i++) {
        root[i] = i;
    }
}
 
void connect(int mHotelA, int mHotelB, int mDistance)
{
    graph[mHotelA].emplace_back(mHotelB, mDistance);
    graph[mHotelB].emplace_back(mHotelA, mDistance);
}
 
int getRoot(int i) {
    if (root[i] == i) {
        return i;
    }
 
    return root[i] = getRoot(root[i]);
}
 
int merge(int mHotelA, int mHotelB)
{
    int eat = getRoot(getBrand[mHotelA]);
    int eaten = getRoot(getBrand[mHotelB]);
 
    if (eat != eaten) {
        root[eaten] = eat;
 
        num[eat] += num[eaten];
        num[eaten] = 0;
    }
 
    return num[eat];
}
 
int move(int mStart, int mBrandA, int mBrandB)
{
    memset(dist, D_MAX, sizeof(int)*n);
     
    dijkstra(mStart, mBrandA, mBrandB);
     
    return min_a + min_b;
}