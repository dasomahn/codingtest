#include <cstring>
#include <vector>
#include <queue>
 
#define H_MAX 5001
#define B_MAX 50
#define D_MAX 50000
 
using namespace std;
 
int hotels_brand[H_MAX];
vector<int> brands_hotel[B_MAX];
 
vector<pair<int, int>> graph[H_MAX]; // 호텔, 거리
int dist[H_MAX];
 
int n;
int min_a, min_b;
 
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
            if (!found_a && hotels_brand[cur] == brandA) {
                found_a = true;
                min_a = d;
            }
            else if (!found_b && hotels_brand[cur] == brandB) {
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
    int i;
    for (i = 0; i < N; i++) graph[i].clear();
    for (i = 0; i < B_MAX; i++)  brands_hotel[i].clear();
 
    n = N;
    for (i = 0; i < N; i++) {
        hotels_brand[i] = mBrands[i];
        brands_hotel[mBrands[i]].emplace_back(i);
    }
}
 
void connect(int mHotelA, int mHotelB, int mDistance)
{
    graph[mHotelA].emplace_back(mHotelB, mDistance);
    graph[mHotelB].emplace_back(mHotelA, mDistance);
}
 
int merge(int mHotelA, int mHotelB)
{
    int eat = hotels_brand[mHotelA];
    int eaten = hotels_brand[mHotelB];
 
    if (eat != eaten) {
        for (int hotel : brands_hotel[eaten]) {
            brands_hotel[eat].emplace_back(hotel);
            hotels_brand[hotel] = eat;
        }
        brands_hotel[eaten].clear();
    }
 
    return brands_hotel[eat].size();
}
 
int move(int mStart, int mBrandA, int mBrandB)
{
    memset(dist, D_MAX, sizeof(int)*n);
     
    dijkstra(mStart, mBrandA, mBrandB);
     
    return min_a + min_b;
}