#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
 
#define NODE_MAX 100000
#define MAX_STOCK_LEN 10
#define SIZE 400
#define BUCKET NODE_MAX/SIZE // 250
 
using namespace std;
 
struct Node {
    int id;
    int ori;
    int price;
 
    int b_idx;
    int idx;
 
    string name;
 
    void init(int _id, int _ori, string _name) {
        id = _id;
        ori = _ori;
        price = _ori;
 
        name = _name;
    }
 
} Nodes[NODE_MAX];
 
bool cmp(Node* a, Node* b) {
    return a->name < b->name;
}
 
struct Bucket {
    int lazy;
    int max_id;
    int max_inc;
    //Node* max;
 
} Buckets[BUCKET];
 
unordered_map<string, Node*> get_node;
 
int n;
int bucket_cnt;
int node_cnt;
 
Node* arr[NODE_MAX];
 
void my_max(int* m_price, int* m_id, Node* node, int lazy) {
    int changes = node->price - node->ori + lazy;
 
    if (*m_price < changes) {
        *m_price = changes;
        *m_id = node->id;
    }
    else if (*m_price == changes) { // 최대 가격 같다면 id 낮은 순    
        if (node->id < *m_id) {
            *m_id = node->id;
        }
    }
}
 
void init(int N, char mStocks[][MAX_STOCK_LEN + 1], int mPrices[])
{
    n = N;
 
    bucket_cnt = 0;
    node_cnt = 0;
 
    for (int i = 0; i < N; i++) {
        Node* node = &Nodes[node_cnt++];
        node->init(i, mPrices[i], mStocks[i]);
        arr[i] = node;
 
        get_node[string(mStocks[i])] = node;
    }
    sort(arr, arr + n, cmp);
 
    // 버킷 처리
    int temp_i, j; // i는 버킷 idx(번호), j는 버킷 내의 idx
    int max_id;
 
    while (bucket_cnt * SIZE < N) {
        temp_i = bucket_cnt * SIZE;
 
        j = 0;
        max_id = NODE_MAX;
        while (temp_i + j < N && j < SIZE) {
            arr[temp_i + j]->b_idx = bucket_cnt;
            arr[temp_i + j]->idx = j;
            max_id = min(max_id, arr[temp_i + j]->id);
            j++;
        }
 
        Buckets[bucket_cnt].max_id = max_id;
        Buckets[bucket_cnt].max_inc = 0;
        Buckets[bucket_cnt].lazy = 0;
 
        bucket_cnt++;
    }
}
 
void update_bucket(int bucket_idx) {
    int lazy = Buckets[bucket_idx].lazy;
 
    int idx = 0;
    int max_inc = -NODE_MAX;
    int max_id = NODE_MAX;
 
    int temp_i = bucket_idx * SIZE;
    while (temp_i + idx < n && idx < SIZE) {
        my_max(&max_inc, &max_id, arr[temp_i + idx], lazy);
        idx++;
    }
 
    Buckets[bucket_idx].max_id = max_id;
    Buckets[bucket_idx].max_inc = max_inc;
}
 
void changePrices(char mFromStock[], char mToStock[], int mPriceDiff)
{
    Node* from = get_node[string(mFromStock)];
    Node* to = get_node[string(mToStock)];
 
    int temp_idx;
 
    // 버킷 걸침
    if (from->b_idx != to->b_idx) {
 
        // 왼쪽 버킷
        temp_idx = from->b_idx * SIZE;
        for (int idx = from->idx; idx < SIZE; idx++) {
            arr[temp_idx + idx]->price += mPriceDiff;
        }
        update_bucket(from->b_idx);
 
        // 가운데 버킷 (있으면 lazy update)
        for (int i = from->b_idx + 1; i < to->b_idx; i++) {
            Buckets[i].lazy += mPriceDiff;
            Buckets[i].max_inc += mPriceDiff;
        }
         
        // 오른쪽 버킷
        temp_idx = to->b_idx * SIZE;
        for (int idx = 0; idx <= to->idx; idx++) {
            arr[temp_idx + idx]->price += mPriceDiff;
        }
        update_bucket(to->b_idx);
    }
    // 한 버킷 내
    else {
        temp_idx = from->b_idx * SIZE;
        for (int idx = from->idx; idx <= to->idx; idx++) {
            arr[temp_idx + idx]->price += mPriceDiff;
        }
        update_bucket(from->b_idx);
    }
}
 
int getPrice(char mStock[])
{
    Node* node = get_node[string(mStock)];
    return node->price + Buckets[node->b_idx].lazy;
}
 
int getMostIncreasedStock(char mFromStock[], char mToStock[])
{
    Node* from = get_node[string(mFromStock)];
    Node* to = get_node[string(mToStock)];
 
    int temp_idx;
 
    int lazy, max_inc, max_id;
    max_inc = -NODE_MAX;
    max_id = NODE_MAX;
 
    // 버킷 걸침
    if (from->b_idx != to->b_idx) {
 
        // 왼쪽 버킷
        temp_idx = from->b_idx * SIZE;
        lazy = Buckets[from->b_idx].lazy;
        for (int idx = from->idx; idx < SIZE; idx++) {
            my_max(&max_inc, &max_id, arr[temp_idx + idx], lazy);
        }
 
        // 가운데 버킷 (있으면)
        for (int i = from->b_idx + 1; i < to->b_idx; i++) {
            int bucket_inc = Buckets[i].max_inc;
 
            if (max_inc < bucket_inc) {
                max_inc = bucket_inc;
                max_id = Buckets[i].max_id;
            }
            else if (max_inc == bucket_inc) {
                if (Buckets[i].max_id < max_id) max_id = Buckets[i].max_id;
            }
        }
 
        // 오른쪽 버킷
        temp_idx = to->b_idx * SIZE;
        lazy = Buckets[to->b_idx].lazy;
        for (int idx = 0; idx <= to->idx; idx++) {
            my_max(&max_inc, &max_id, arr[temp_idx + idx], lazy);
        }
    }
    // 한 버킷 내
    else {
        temp_idx = from->b_idx * SIZE;
        for (int idx = from->idx; idx <= to->idx; idx++) {
            my_max(&max_inc, &max_id, arr[temp_idx + idx], 0); // 한 버킷 내라 안넣어도 무방
        }
    }
 
    return max_id;
}