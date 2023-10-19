#include <iostream>
#include <algorithm>
#include <list>
#include <unordered_map>
 
#define MAX 300004
 
using namespace std;
 
struct Score;
 
struct Soldier {
 
    int id;
    int team;
 
} Soldiers[MAX];
 
int soldier_cnt;
unordered_map<int, Soldier*> get_soldier;
 
struct Team {
 
    int team;
    list<Soldier*> scores[5];
 
} Teams[5];
 
void init()
{
    soldier_cnt = 0;
    get_soldier.clear();
 
    for (int i = 0; i < 5; i++) {
        Teams[i].scores[0].clear();
        Teams[i].scores[1].clear();
        Teams[i].scores[2].clear();
        Teams[i].scores[3].clear();
        Teams[i].scores[4].clear();
    }
}
 
void hire(int mID, int mTeam, int mScore)
{
    Soldier* soldier = &Soldiers[soldier_cnt++];
    soldier->id = mID;
    soldier->team = mTeam;
 
    Teams[mTeam - 1].scores[mScore - 1].emplace_back(soldier);
 
    get_soldier[mID] = soldier;
}
 
void fire(int mID)
{
    Soldier* soldier = get_soldier[mID];
    soldier->id = 0;
}
 
void updateSoldier(int mID, int mScore)
{
    Soldier* soldier = get_soldier[mID];
    soldier->id = 0;
 
    hire(mID, soldier->team, mScore);
}
 
void updateTeam(int mTeam, int mChangeScore)
{
    Team* team = &Teams[mTeam - 1];
    int t;
 
    if (!mChangeScore) return;
 
    if (mChangeScore > 0) {
        for (int i = 3; i >= 0; i--) {
            if (i + 1 + mChangeScore >= 5) { // 현재 점수(i+1) + 변동 >= 5
                t = 4;
            }
            else {
                t = i + mChangeScore;
            }
 
            team->scores[t].splice(team->scores[t].end(), team->scores[i]);
        }
    }
    else {
        for (int i = 1; i <= 4; i++) {
            if (i + 1 + mChangeScore <= 1) {
                t = 0;
            }
            else {
                t = i + mChangeScore;
            }           
             
            team->scores[t].splice(team->scores[t].end(), team->scores[i]);
        }
    }
}
 
int bestSoldier(int mTeam)
{
    Team* team = &Teams[mTeam - 1];
    int m = 0;
 
    for (int sc = 4; sc >= 0; sc--) {
        if (!team->scores[sc].empty()) {
 
            for (auto iter = team->scores[sc].begin(); 
                iter != team->scores[sc].end();
                iter++) {
                if ((*iter)->id != 0) {
                    m = max(m, (*iter)->id);
                }
            }
 
            if (m) return m;
        }
    }
 
    return 0;
}