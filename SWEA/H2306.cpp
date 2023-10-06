#include <cstring>
#include <queue>
#include <vector>
#include <unordered_map>
 
#define MAX_N 10000
 
using namespace std;
 
struct Node {
    int id;
    int um;
    int sum;
    int height;
     
    Node* parent;
    int parent_w;
 
    void init(int _id, Node* _parent, int _um, int _w) {
        id = _id;
        um = _um;
        sum = _um;
         
        parent = _parent;
        parent_w = _w;
    }
         
} Nodes[MAX_N];
 
int n;
 
vector<pair<int, int>> graph[MAX_N];
bool visited[MAX_N];
 
void update(Node* node, int um) {
    while (node) {
        node->sum += um;
        node = node->parent;
    }
}
 
void init(int N, int mParent[], int mDistance[], int mQuantity[])
{
    int i;
    n = N;
 
    // graph vector 초기화
    for (i = 0; i < N; i++) graph[i].clear();
 
    i = 0;
    Node* node = &Nodes[i];
    node->init(i, nullptr, mQuantity[i], 0);
    node->height = 0;
 
    for (i = 1; i < N; i++) {
        // tree
        Node* parent = &Nodes[mParent[i]];
         
        Node* node = &Nodes[i];
        node->init(i, parent, mQuantity[i], mDistance[i]);
        node->height = parent->height + 1;
 
        update(parent, mQuantity[i]);
 
        // graph
        graph[mParent[i]].emplace_back(i, mDistance[i]);
        graph[i].emplace_back(mParent[i], mDistance[i]);
    }
}
 
 
int carry(int mFrom, int mTo, int mQuantity)
{
    Node* from = &Nodes[mFrom];
    Node* to = &Nodes[mTo];
     
    // 우산 업데이트
    from->um -= mQuantity;
    to->um += mQuantity;
    update(from, -mQuantity);
    update(to, mQuantity);
     
     
    // 비용 계산 (1 높이 맞춤 2 부모 찾기)
    if (from->height < to->height) swap(from, to);
     
    int cost = 0;
    while (from->height != to->height) {
        cost += from->parent_w;
        from = from->parent;
    }
 
    while (from != to) {
        cost += from->parent_w;
        from = from->parent;
         
        cost += to->parent_w;
        to = to->parent;
    }
 
    return cost * mQuantity;
}
 
struct compare {
    bool operator() (pair<int, int> a, pair<int, int> b) {
        if (a.first == b.first) {
            return a.second > b.second;
        }
        return a.first > b.first;
    }
};
 
int gather(int mID, int mQuantity)
{
    Node* node = &Nodes[mID];
    node->um += mQuantity;
    update(node, mQuantity);
 
    memset(visited, 0, sizeof(bool)*n);
 
    int id, dist;
    int cost = 0;
 
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
 
    visited[mID] = 1;
    for (pair<int, int> p : graph[mID]) {
        visited[p.first] = 1;
        pq.emplace(p.second, p.first);
    }
 
    while (mQuantity != 0) {
        tie(dist, id) = pq.top();
        pq.pop();
 
        node = &Nodes[id];
        if (mQuantity > node->um) {
            update(node, -node->um);
 
            cost += node->um * dist;
            mQuantity -= node->um;
            node->um = 0;
 
        }
        else if (mQuantity <= node->um) {
            update(node, -mQuantity);
 
            cost += mQuantity * dist;
            node->um -= mQuantity;
            mQuantity = 0;
            break;
        }
 
        for (pair<int, int> p : graph[id]) {
            if (!visited[p.first]) {
                visited[p.first] = 1;
                pq.emplace(dist + p.second, p.first);
            }
        }
    }
 
    return cost;
}
 
int sum(int mID)
{
    return Nodes[mID].sum;
}