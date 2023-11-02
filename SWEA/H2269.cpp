#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
  
#define mod(a) ((a) >= 0 ? (a) % 24 : (a) % 24 + 24)
#define pi pair<int, int>
  
using namespace std;
  
struct Edge {
    int start;
    int travel;
    int endAirport;
  
    Edge(int s, int t, int e):
        start(s), travel(t), endAirport(e) {}
};
  
vector<Edge> timeGraph[61];
int priceGraph[61][61];
  
int N;
int cost[61];
  
void init(int N)
{
    ::N = N;
  
    for (int i = 0; i < N; i++) {
        timeGraph[i].clear();
    }
    memset(priceGraph, 0, sizeof(priceGraph));
}
  
void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice)
{
    timeGraph[mStartAirport].emplace_back(mStartTime, mTravelTime, mEndAirport);
  
    int m = priceGraph[mStartAirport][mEndAirport];
    priceGraph[mStartAirport][mEndAirport] = (m ? min(mPrice, m) : mPrice);
}
  
struct Node {
    int curAirport;
    int curTime;
    int totalTime;
  
    Node(int airport, int time, int total):
        curAirport(airport), curTime(time), totalTime(total) {}
};
  
struct cmp {
    bool operator()(Node a, Node b) {
        return a.totalTime > b.totalTime;
    }
};
  
int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime)
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.emplace(mStartAirport, mStartTime, 0); // 공항까지, 걸리는 총 시간, 현재 시각
  
    for (int i = 0; i < N; i++) {
        cost[i] = 2760;
    }
  
    cost[mStartAirport] = 0;
  
    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
  
        if (node.curAirport == mEndAirport) return node.totalTime;
        if (node.totalTime > cost[node.curAirport]) continue;
         
        for (Edge edge : timeGraph[node.curAirport]) {
  
            int wait = mod(edge.start - node.curTime);
            int time = wait + edge.travel;
            if (node.totalTime + time >= cost[edge.endAirport]) continue;
  
            cost[edge.endAirport] = node.totalTime + time;
  
            pq.emplace(edge.endAirport, // 도착할 공항
                mod(node.curTime + time), // 현재 시각
                node.totalTime + time); // 걸린 총 시간
        }
    }
  
    return -1;
}
  
struct cmpPrice {
    bool operator() (pi a, pi b) {
        return a.second > b.second;
    }
};
  
int minPrice(int mStartAirport, int mEndAirport)
{
    priority_queue<pi, vector<pi>, cmpPrice> pq; // 도착 공항, 총 가격
    pq.emplace(mStartAirport, 0);
  
    for (int i = 0; i < N; i++) {
        cost[i] = 300'000;
    }
    cost[mStartAirport] = 0;
  
    while (!pq.empty()) {
        int curAirport = pq.top().first;
        int total = pq.top().second;
        pq.pop();
  
        if (total > cost[curAirport]) continue;
  
        if (curAirport == mEndAirport) {
            return total;
        }
  
        for (int i = 0; i < 61; i++) {
            if (priceGraph[curAirport][i]) {
                int next = total + priceGraph[curAirport][i];
  
                if (next >= cost[i]) continue;
  
                cost[i] = next;
                pq.emplace(i, next);
            }
        }
    }
  
    return -1;
}