#include <set>
#include <unordered_map>
 
#define MAX 18000
 
using namespace std;
 
struct Node {
    int id;
 
    int num;
    int total;
 
    Node* parent;
    Node* child[3];
    int child_cnt;
 
    void init(int _id, int _n, Node* _p) {
        id = _id;
        num = _n;
        total = 0;
        parent = _p;
 
        child_cnt = 0;
    }
 
} Nodes[MAX];
 
int node_cnt;
unordered_map<int, Node*> get_node;
 
int n;
int g_total;
 
multiset<int, greater<int>> groups; // 큰 순으로 들어와있음
 
void update(Node* node, int n) {
    while (node->parent) {
        node->total += n;
        node = node->parent;
    }
 
    groups.erase(groups.find(node->total));
    node->total += n;
    g_total += n;
    groups.emplace(node->total);
 
}
 
void init(int N, int mId[], int mNum[]) {
    n = N;
    node_cnt = 0;
    g_total = 0;
 
    get_node.clear();
    groups.clear();
 
    for (int i = 0; i < N; i++) {
        Node* node = &Nodes[node_cnt++];
        node->init(mId[i], mNum[i], nullptr);
        get_node[mId[i]] = node;
 
        node->total += mNum[i];
        g_total += mNum[i];
 
        groups.emplace(mNum[i]);
    }
 
    return;
}
 
int add(int mId, int mNum, int mParent) {
    Node* parent = get_node[mParent];
 
    if (parent->child_cnt == 3) return -1;
 
    // 노드 생성
    Node* node = &Nodes[node_cnt++];
    node->init(mId, mNum, parent);
    get_node[mId] = node;
 
    // 자식 추가
    parent->child[parent->child_cnt++] = node;
    update(node, mNum);
 
    return node->parent->total;
}
 
void del(Node* node) {
    get_node.erase(node->id);
 
    for (int i = 0; i < node->child_cnt; i++) {
        del(node->child[i]);
    }
}
 
int remove(int mId) {
    if (get_node.find(mId) == get_node.end()) return -1;
     
    Node* node = get_node[mId];
    Node* parent = node->parent;
     
    for (int i = 0; i < parent->child_cnt; i++) {
        if (parent->child[i] == node) {
            parent->child[i] = parent->child[parent->child_cnt - 1];
            parent->child_cnt--;
             
            break;
        }
    }
 
    update(node->parent, -node->total);
    del(node);
 
    return node->total;
}
 
int distribute(int K) {
    if (g_total <= K) return *groups.begin();
 
    int i = 0;
    int temp_total = g_total;
    int minus = 0;
 
    auto iter = groups.begin();
    int first = *iter;
    int second = *iter;
 
    while (true) {
        temp_total -= (first - second) * i;
        if (temp_total <= K) break;
 
        minus += second;
 
        iter++;
        first = second;
        second = (*iter);
 
        i++;
    }
 
    if (temp_total == K) return second;
     
    // 이분 탐색
    temp_total = g_total - minus;
     
    int mid, res;
    while (second <= first) {
         
        mid = (first + second) / 2;
        res = temp_total + mid * i;
 
        if (res > K) first = mid - 1;
        else if (res < K) second = mid + 1;
        else return mid;
    }
 
    return first;
}