#include <iostream>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <vector>
 
#define MAXL    (10)
#define MAXU    (10000)
#define MAX     (50000)
 
using namespace std;
 
struct User {
    char c_id[MAXL+1];
    int point;
 
} Users[MAXU];
int user_cnt;
unordered_map<string, User*> user_map;
 
struct Message {
    User* user_p;
    int id;
    int point;
    int total;
    bool alive;
 
    Message* parent;
    vector<Message *> comments;
 
} Messages[MAX];
int mes_cnt;
unordered_map<int, Message*> mes_map;
 
struct cmp_user{
    bool operator()(pair<int, User*> a, pair<int, User*> b) const {
        if (a.first == b.first) {
            return strcmp(a.second->c_id, b.second->c_id) > 0;
        }
        return a.first < b.first;
    }
};
 
struct cmp_mes {
    bool operator()(pair<int, Message*> a, pair<int, Message*> b) const {
        if (a.first == b.first) {
            return a.second->id > b.second->id;
        }
        return a.first < b.first;
    }
};
 
priority_queue<pair<int, User*>, vector<pair<int, User*>>, cmp_user> user_heap;
priority_queue<pair<int, Message*>, vector<pair<int, Message*>>, cmp_mes> mes_heap;
 
void init()
{
    user_cnt = 0;
    mes_cnt = 0;
 
    while (!user_heap.empty()) user_heap.pop();
    while (!mes_heap.empty()) mes_heap.pop();
 
    user_map.clear();
    mes_map.clear();
 
    return;
}
 
User* get_user(char mUser[]) {
    // 유저 갖고오기 (없으면 생성)
    User *user = user_map[mUser];
 
    if (user == nullptr) {
        user = &Users[user_cnt];
        strcpy(user->c_id, mUser);
        user->point = 0;
 
        user_map[mUser] = user;
        user_cnt++;
    }
 
    return user;
}
 
int writeMessage(char mUser[], int mID, int mPoint)
{
    User *user = get_user(mUser);
    user->point += mPoint;
 
    // 글 작성
    Message *mes = &Messages[mes_cnt];
    mes->user_p = user;
    mes->id = mID;
    mes->parent = nullptr;
    mes->point = mPoint;
    mes->total = mPoint;
    mes->alive = true;
    mes->comments.clear();
    mes_map[mID] = mes;
 
    mes_cnt++;
 
    // heap 넣기
    user_heap.emplace(user->point, user);
    mes_heap.emplace(mes->total, mes);
 
    return user->point;
}
 
int commentTo(char mUser[], int mID, int mTargetID, int mPoint)
{
    User * user = get_user(mUser);
    user->point += mPoint;
 
    Message *mes = &Messages[mes_cnt];
    mes->user_p = user;
    mes->id = mID;
    mes->parent = mes_map[mTargetID];
    mes->point = mPoint;
    mes->total = mPoint;
    mes->alive = true;
    mes->comments.clear();
    mes_map[mID] = mes;
 
    mes_cnt++;
 
    Message *parent = mes_map[mTargetID];
    parent->comments.emplace_back(mes);
 
    while (parent != nullptr) {
        parent->total += mPoint;
        parent = parent->parent;
    }
 
    // heap 넣기
    user_heap.emplace(user->point, user);
 
    mes = mes->parent;
    while (mes->parent != nullptr) {
        mes = mes->parent;
    }
    mes_heap.emplace(mes->total, mes);
 
    return mes->total;
}
 
void remove(Message *erase) {
    if (!erase->alive) {
        return; // 이미 지워짐
    }
    erase->alive = false;
 
    erase->user_p->point -= erase->point;
    user_heap.emplace(erase->user_p->point, erase->user_p);
 
    for (Message *comment : erase->comments) {
        remove(comment);
    }
}
 
 
int erase(int mID)
{
    Message* erase = mes_map[mID];
    remove(erase);
 
    int total = erase->total;
    Message* ptr = erase->parent;
    while (ptr != nullptr) {
        ptr->total -= total;
        ptr = ptr->parent;
    }
     
    ptr = erase;
    if (ptr->parent == nullptr) {
        // 글일 경우
        mes_heap.emplace(ptr->total, ptr);
        return erase->user_p->point;
    }
    else {
        ptr = ptr->parent;
        if (ptr->parent != nullptr) {
            // 답글일 경우
            ptr = ptr->parent;
        }
        mes_heap.emplace(ptr->total, ptr);
        return ptr->total;
    }
}
 
void getBestMessages(int mBestMessageList[])
{
    int cnt = 0;
    int total;
    Message* mes;
 
    while (cnt < 5) {
        total = mes_heap.top().first;
        mes = mes_heap.top().second;
        mes_heap.pop();
 
        if (!mes->alive | (total != mes->total) | ((cnt > 0) & (mBestMessageList[cnt - 1] == mes->id))) {
            continue;
        }
        mBestMessageList[cnt] = mes->id;
        cnt++;
    }
 
    for (int i = 0; i < 5; i++) {
        mes_heap.emplace(mes_map[mBestMessageList[i]]->total, mes_map[mBestMessageList[i]]);
    }
}
 
void getBestUsers(char mBestUserList[][MAXL + 1])
{
    int cnt = 0;
    int total;
    User* user;
 
    while (cnt < 5) {
        total = user_heap.top().first;
        user = user_heap.top().second;
        user_heap.pop();
 
 
        // 과거꺼 거르기 (상이하거나, 동일한데 과거꺼거나)
        if ((total != user->point) | ((cnt > 0) & (strcmp(mBestUserList[cnt - 1], user->c_id))==0)) {
            continue;
        }
        strcpy(mBestUserList[cnt], user->c_id);
        cnt++;
    }
 
    for (int i = 0; i < 5; i++) {
        user_heap.emplace(user_map[mBestUserList[i]]->point, user_map[mBestUserList[i]]);
    }
}