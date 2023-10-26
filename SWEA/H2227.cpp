#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
 
#define LAND 625
 
using namespace std;
typedef pair<int, int> pi;
 
struct Land {
    string name;
    int soldier;
 
    int id;
    int x, y;
 
    void init(string _name, int s, int _x, int _y, int _id) {
        name = _name;
        soldier = s;
        x = _x;
        y = _y;
        id = _id;
    }
 
} Lands[LAND];
int land_cnt;
 
unordered_map<string, Land*> get_land;
 
int n;
int root[LAND];
set<int> allies[LAND]; // 동맹 관계
unordered_set<int> enemy[LAND]; // 적대 관계인 동맹
 
void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
    land_cnt = 0;
    n = N;
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Land* land = &Lands[land_cnt++];
            land->init(mMonarch[i][j], mSoldier[i][j], i, j, i*n + j);
            get_land[land->name] = land;
 
            root[land->id] = land->id;
            allies[land->id].emplace(land->id);
        }
    }
}
 
void destroy() {
    for (int i = 0; i < n*n; i++) {
        enemy[i].clear();
        allies[i].clear();
    }
    get_land.clear();
}
 
int get_parent(int a) {
    if (root[a] == a) return a;
 
    root[a] = get_parent(root[a]);
    return root[a];
}
 
void copy(int to, int from) {
    // 동맹 쪽 업데이트
    for (auto a : allies[from]) {
        allies[to].emplace(a);
        root[a] = to;
    }
    root[to] = to;
    allies[from].clear();
    allies[from].emplace(from);
 
    // enemy 쪽 업데이트
    for (auto e : enemy[from]) {
        enemy[to].emplace(e);
        enemy[e].erase(find(enemy[e].begin(), enemy[e].end(), from));
        enemy[e].emplace(to);
    }
    enemy[from].clear();
}
 
void alliance(int p_a, int p_b) {
    if (p_a > p_b) {
        swap(p_a, p_b);
    }
    copy(p_a, p_b);
    root[p_b] = p_a;
    allies[p_a].emplace(p_b);
}
 
int ally(char mMonarchA[11], char mMonarchB[11])
{
    Land* a = get_land[mMonarchA];
    Land* b = get_land[mMonarchB];
 
    int p_a = get_parent(a->id);
    int p_b = get_parent(b->id);
 
    if (p_a == p_b) return -1;
     
    if (find(enemy[p_a].begin(), enemy[p_a].end(), p_b) != enemy[p_a].end()) return -2;
 
    // 동맹
    alliance(p_a, p_b);
 
    return 1;
}
 
int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
    Land* a = get_land[mMonarchA];
    Land* b = get_land[mMonarchB];
 
    int p_a = get_parent(a->id);
    int p_b = get_parent(b->id);
 
    // 이미 동맹
    if (p_a == p_b) return -1;
     
    int a_helpers = 0;
    bool attk = false;
 
    for (auto al : allies[p_a]) {
        int _x = abs(Lands[al].x - b->x);
        int _y = abs(Lands[al].y - b->y);
 
        if ((_x + _y == 1) || (_x == 1 && _y == 1)) {
            attk = true;
            a_helpers += Lands[al].soldier / 2;
            Lands[al].soldier -= Lands[al].soldier / 2;
        }
    }
 
    if (!attk) return -2; 
 
    for (auto al : allies[p_b]) {
        int _x = abs(Lands[al].x - b->x);
        int _y = abs(Lands[al].y - b->y);
 
        if ((_x + _y == 1) || (_x == 1 && _y == 1)) {
            b->soldier += Lands[al].soldier / 2;
            Lands[al].soldier -= Lands[al].soldier / 2;
        }
    }
 
    // 방어 성공
    if (a_helpers <= b->soldier) {
        b->soldier = b->soldier - a_helpers;
 
        // 서로를 적대관계로 등록
        enemy[p_a].emplace(p_b);
        enemy[p_b].emplace(p_a);
 
        return 0;
    }
 
    if (allies[p_b].size() != 1) {
        enemy[p_a].emplace(p_b);
        enemy[p_b].emplace(p_a);
    }
 
    b->soldier = a_helpers - b->soldier;
    get_land.erase(b->name);
 
    b->name = mGeneral;
    get_land[b->name] = b;
 
    if ((b->id == p_b) && allies[b->id].size() != 1) { // 멸망될 나라가 그룹의 왕이었다면
        allies[b->id].erase(b->id);
 
        int n = *allies[b->id].begin(); // 바꿀 왕
        copy(n, b->id);
    } else if (b->id == p_b && allies[b->id].size() == 1) { // 멸망될 나라가 그냥 혼자 있었다면 (동맹 없이)
        for (auto e : enemy[b->id]) {
            enemy[e].erase(b->id);
        }
 
        enemy[b->id].clear();
    }
    else if (b->id != p_b) { // 동맹의 소속
        allies[p_b].erase(b->id);
    }
 
    // 동맹
    alliance(b->id, p_a);
 
    return 1;
}
 
int recruit(char mMonarch[11], int mNum, int mOption)
{
    Land* land = get_land[mMonarch];
 
    if (!mOption) {
        land->soldier += mNum;
        return land->soldier;
    }
 
    int total = 0;
    for (auto a : allies[root[land->id]]) {
        Lands[a].soldier += mNum;
        total += Lands[a].soldier;
    }
 
    return total;
}