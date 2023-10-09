#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <vector>
 
#define NODE_M 12001
 
using namespace std;
 
struct Node {
    string name;
    vector<Node*> child;
 
    int height;
    int max_log;
    Node* ac[11];
 
    void init(string n, int h) {
        name = n;
        height = h;
 
        child.clear();
    }
 
    void dp(Node* p) {
 
        max_log = log2(height);
        ac[0] = p;
 
        for (int i = 1; i <= max_log; i++) {
            ac[i] = ac[i - 1]->ac[i - 1];
        }
    }
 
} nodes[NODE_M];
 
 
Node* root;
unordered_map<string, Node*> get_node;
int node_cnt;
 
vector<int> v_birth;
vector<int> v_death;
 
void init(char mAncestor[], int mDeathday)
{
    node_cnt = 0;
 
    root = &nodes[node_cnt++];
    root->init(mAncestor, 0);
    get_node[root->name] = root;
 
    v_birth.clear();
    v_death.clear();
 
    v_birth.push_back(0);
    v_death.push_back(mDeathday);
 
    return;
}
 
Node* add_node(string n, string p_n) {
 
    Node* node = &nodes[node_cnt++];
    Node* p = get_node[p_n];
 
    node->init(n, p->height + 1);
    node->dp(p);
 
    get_node[n] = node;
    return node;
}
 
int add(char mName[], char mParent[], int mBirthday, int mDeathday)
{
    Node* node = add_node(mName, mParent);
 
    v_birth.insert(upper_bound(v_birth.begin(), v_birth.end(), mBirthday), mBirthday);
    v_death.insert(upper_bound(v_death.begin(), v_death.end(), mDeathday), mDeathday);
 
    return node->height;
}
 
Node* match_height(Node* node, int h) {
    int diff, up;
    while (node->height != h) {
        diff = node->height - h;
        up = log2(diff);
        node = node->ac[up];
    }
 
    return node;
}
 
int distance(char mName1[], char mName2[])
{
    Node* node1 = get_node[mName1];
    Node* node2 = get_node[mName2];
 
    int h1 = node1->height;
    int h2 = node2->height;
 
    // 높이 같게 맞춰주기
    if (h1 > h2) node1 = match_height(node1, h2);
    else if (h1 < h2) node2 = match_height(node2, h1);
 
    int i, h_log;
    while (node1 != node2) {
 
        if (node1->ac[0] == node2->ac[0]) {
            node1 = node1->ac[0];
            break;
        }
 
        h_log = log2(node1->height);
        for (i = 1; i <= h_log; i++) {
            if (node1->ac[i] == node2->ac[i]) {
                node1 = node1->ac[i - 1];
                node2 = node2->ac[i - 1];
 
                break;
            }
            if (i == h_log) {
                node1 = node1->ac[i];
                node2 = node2->ac[i];
            }
        }
    }
 
    return h1 + h2 - 2 * node1->height;
}
 
int count(int mDay)
{
    int a = upper_bound(v_birth.begin(), v_birth.end(), mDay) - v_birth.begin();
    int c = upper_bound(v_death.begin(), v_death.end(), mDay - 1) - v_death.begin();
 
    return a - c;
}