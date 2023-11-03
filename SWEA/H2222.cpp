#include <cstring>
#include <string>
#include <set>
#include <unordered_map>
 
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX_BCNT    100
#define MAX_NAME    10
 
using namespace std;
 
int power[17] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65534 };
 
struct Bacteria;
 
struct Node {
    Bacteria* bact;
 
    int life;
    int added;
    int cur;
    int count;
 
    set<Node*>::iterator iter;
    int poolIdx;
 
    void add(Bacteria* _bact, int _time, int _life, int _count) {
        bact = _bact;
        added = _time;
        cur = _time;
        life = _life;
        count = _count;
    }
 
} Nodes[15000];
int nodeCnt;
 
struct cmp {
    bool operator()(Node* a, Node* b) {
        if (a->life == b->life) {
            return a->added < b->added;
        }
 
        return a->life < b->life;
    }
};
 
set<Node*, cmp> order;
 
struct Bacteria { // 박테리아 사전
    char name[MAX_NAME];
    int half;
    int total;
 
    void init(char *_name, int _half) {
        strcpy(name, _name);
        half = _half;
        total = 0;
    }
 
} Bacterium[MAX_BCNT];
unordered_map<string, Bacteria*> getBact;
int N;
 
void init(int N, char bNameList[MAX_BCNT][MAX_NAME], int mHalfTime[MAX_BCNT])
{
    ::N = N;
    getBact.clear();
    nodeCnt = 0;
    order = {};
 
    for (int i = 0; i < N; i++) {
        Bacteria* bacteria = &Bacterium[i];
        bacteria->init(bNameList[i], mHalfTime[i]);
        getBact[bNameList[i]] = bacteria;
    }
}
 
void addBacteria(int tStamp, char bName[MAX_NAME], int mLife, int mCnt)
{
    Bacteria* bacteria = getBact[bName];
     
    Node* node = &Nodes[nodeCnt++];
    node->add(bacteria, tStamp, mLife, mCnt);
 
    bacteria->total += mCnt;
    node->iter = order.emplace(node).first;
}
 
void update(int time) {
    auto iter = order.begin();
    while (iter != order.end()) {
        Node* node = *iter;
         
        int halved = MIN(16, (time - node->cur) / node->bact->half);
        if (halved == 0) {
            iter++;
            continue;
        }
        node->life /= power[halved];
        iter = order.erase(node->iter);
 
        if (node->life < 10) {
            node->bact->total -= node->count;
            continue;
        }
        node->cur += halved * node->bact->half;
        node->iter = order.emplace(node).first;
    }
}
 
int takeOut(int tStamp, int mCnt)
{
    update(tStamp);
     
    int lives = 0;
    auto iter = order.begin();
    while (iter != order.end() && mCnt) {
        Node* node = *iter;
 
        if (mCnt >= node->count) {
            lives += node->count * node->life;
            node->bact->total -= node->count;
 
            mCnt -= node->count;
            iter = order.erase(node->iter);
        }
        else {
            // mCnt < node->count;
            lives += mCnt * node->life;
            node->bact->total -= mCnt;
 
            node->count -= mCnt;
            break;
        }
    }
    return lives;
}
 
int checkBacteria(int tStamp, char bName[MAX_NAME])
{
    update(tStamp);
    Bacteria* bacteria = getBact[bName];
    return bacteria->total;
}