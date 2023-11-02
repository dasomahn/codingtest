#include <iostream>
#include <unordered_map>
 
#define MAX 1'000'000'000
 
using namespace std;
 
struct Node {
    int pos;
    int id;
 
    Node* left;
    Node* right;
 
} Nodes[27002];
int nodeCnt;
unordered_map<int, Node*> getNode;
 
Node* head;
Node* tail;
int N;
 
bool debug = false;
 
Node* find(int pos) {
    Node* node = head;
 
    while (node) {
        if (pos <= node->pos) {
            return node;
        }
        node = node->right;
    }
 
    return tail;
}
 
Node* newNode(int id, int pos) {
    Node* node = &Nodes[nodeCnt++];
    getNode[id] = node;
 
    node->id = id;
    node->pos = pos;
 
    node->left = 0;
    node->right = 0;
 
    return node;
}
 
void connect(Node* node, Node* next) {
    node->left = next->left;
    next->left->right = node;
 
    node->right = next;
    next->left = node;
}
 
Node* insert(Node* node) {
    Node* next = find(node->pos);
    connect(node, next);
 
    return node;
}
 
void init(int N, int mId[], int mLocation[]) {
    ::N = N;
    getNode.clear();
 
    head = &Nodes[0];
    tail = &Nodes[1];
    tail->pos = MAX + 1;
 
    head->right = tail;
    tail->left = head;
 
    nodeCnt = 2;
    for (int i = 0; i < N; i++) {
        Node* node = newNode(mId[i], mLocation[i]);
        insert(node);
    }
     
    return;
}
 
int add(int mId, int mLocation) {
    Node* node;
 
    if (getNode.find(mId) != getNode.end()) {
        node = getNode[mId];
        getNode.erase(mId);
 
        node->left->right = node->right;
        node->right->left = node->left;
        N--;
    }
     
    node = newNode(mId, mLocation);
    insert(node);
     
    return ++N;
}
 
int remove(int mStart, int mEnd) {
    Node* cur = find(mStart);
    Node* start = cur->left;
     
    while (cur->pos <= mEnd) {
        getNode.erase(cur->id);
        cur = cur->right;
        N--;
    }
 
    start->right = cur;
    cur->left = start;
     
    return N;
}
 
bool group(int val, int groups) {
    Node* cur = head->right;
    int dist = 0;
    int cnt = 0;
 
    while (cur->right != tail && cnt < groups) {
        while (cur->right != tail && dist < val) {
            dist += cur->right->pos - cur->pos;
            cur = cur->right;
        }
 
        if (dist >= val) {
            cnt++;
            dist = 0;
        }
    }
 
    if (cnt == groups) return true;
    return false;
}
 
int install(int M) {
    int left = 0;
    int right = tail->left->pos;
 
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (group(mid, M - 1)) {
            left = mid;
        }
        else {
            right = mid;
        }
    }
 
    return left;
}