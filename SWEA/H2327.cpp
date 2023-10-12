#include <algorithm>
#include <unordered_map>
 
#define MAX 8000
 
using namespace std;
 
struct Team {
    int id;
    int n;
    int total;
    bool alive;
 
    Team* parent;
    Team* child[2];
    int child_cnt;
 
    void init(int _id, int _n, Team* _p) {
        id = _id;
        n = _n;
        alive = true;
 
        parent = _p;
        child_cnt = 0;
        total = 0;
    }
 
} Teams[MAX];
int team_cnt;
 
unordered_map<int, Team*> get_team;
Team* root;
 
void update(Team* team, int n) {
    while (team->parent) {
        team->total += n;
        team = team->parent;
    }
    team->total += n;
}
 
Team* new_team(int id, int n, Team* parent) {
    Team* team = &Teams[team_cnt++];
    team->init(id, n, parent);
 
    get_team[id] = team;
    return team;
}
 
void init(int mId, int mNum) {
    team_cnt = 0;
 
    get_team.clear();
 
    root = new_team(mId, mNum, nullptr);
    update(root, mNum);
     
    return;
}
 
int add(int mId, int mNum, int mParent) {
    Team* parent = get_team[mParent];
    if (parent->child_cnt == 2) return -1;
 
    Team* team;
    if (get_team.find(mId) != get_team.end()) {
        team = get_team[mId];
        team->init(mId, mNum, parent);
    }
    else {
        team = new_team(mId, mNum, parent);
    }
 
    update(team, mNum);
    parent->child[parent->child_cnt++] = team;
 
    return team->parent->total;
}
 
void erase(Team* team) {
    team->alive = false;
 
    for (int i = 0; i < team->child_cnt; i++) {
        erase(team->child[i]);
    }
}
 
int remove(int mId) {
    Team* team = get_team[mId];
    if (!team || !team->alive) return -1;
 
    Team* parent = team->parent;
    int total = team->total;
 
    update(team, -total);
 
    if (parent->child[0] == team) {
        parent->child[0] = parent->child[1];
    }
    parent->child_cnt--;
 
    erase(team);
 
    return total;
}
 
int m, k;
int cut;
int dfs(Team* team) {
    if (team->n > k) return -1;
 
    int left = 0;
    int right = 0;
 
    if (team->child_cnt == 0) {
        return team->n;
    }
 
    if (team->child_cnt == 2) {
        right = dfs(team->child[1]);
    }
    left = dfs(team->child[0]);
 
    if (left == -1 || right == -1) {
        return -1;
    }
 
    int n_sum = left + right + team->n;
 
    if (n_sum > k) {
        n_sum -= max(left, right);
        cut++;
    }
    if (n_sum > k) {
        n_sum -= min(left, right);
        cut++;
    }
    if (cut >= m) {
        return  -1;
    }
 
    return n_sum;
}
 
int reorganize(int M, int K) {
    m = M;
    k = K;
    cut = 0;
 
    return dfs(root) == -1 ? 0 : 1;
}