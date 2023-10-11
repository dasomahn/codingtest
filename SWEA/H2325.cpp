#include <cstring>
#include <set>
#include <string>
#include <unordered_map>
 
#define LEN 11
 
using namespace std;
 
struct Room {
    int id;
    char full[12];
 
    char front[5];
    char back[5];
    char mid[4];
 
    int f, b;
 
    char l_front[5];
    char l_back[5];
 
    void init(int _id, char* _full) {
        id = _id;
        strcpy(full, _full);
    }
 
} Rooms[30000];
 
struct cmp {
    bool operator() (Room* a, Room* b) const {
        return strcmp(a->full, b->full) < 0;
    }
};
 
unordered_map<string, Room*> get_room;
int room_cnt;
 
unordered_map<string, set<Room*, cmp>> fronts;
unordered_map<string, set<Room*, cmp>> backs;
unordered_map<string, set<Room*, cmp>> l_fronts;
unordered_map<string, set<Room*, cmp>> l_backs;
unordered_map<string, set<Room*, cmp>> mids;
Room* cur = nullptr;
 
void init()
{
    room_cnt = 0;
 
    fronts.clear();
    backs.clear();
    l_fronts.clear();
    l_backs.clear();
    mids.clear();
 
    get_room.clear();
}
 
void word(Room* room, char* str, int f, int b) {
    room->f = f;
    room->b = b;
 
    for (int i = 0; i < 4; i++) {
        room->front[i] = str[i];
        room->l_front[i] = str[i];
        room->l_back[i] = str[LEN - 4 + i];
    }
    room->front[2] = 0;
    room->front[4] = 0;
    room->back[4] = 0;
 
    room->back[0] = str[LEN - 2];
    room->back[1] = str[LEN - 1];
    room->back[2] = 0;
 
    room->mid[0] = str[4];
    room->mid[1] = str[5];
    room->mid[2] = str[6];
    room->mid[3] = 0;
 
    fronts[string(room->front)].emplace(room);
    backs[string(room->back)].emplace(room);
    mids[string(room->mid)].emplace(room);
     
    l_fronts[string(room->l_front)].emplace(room);
    l_backs[string(room->l_back)].emplace(room);
}
 
void addRoom(int mID, char mWord[], int mDirLen[])
{
    Room* room = &Rooms[room_cnt++];
    get_room[string(mWord)] = room;
    room->init(mID, mWord);
    word(room, mWord, mDirLen[0], mDirLen[2]);
}
 
void setCurrent(char mWord[])
{
    Room* room = get_room[string(mWord)];
    cur = room;
}
 
int moveDir(int mDir)
{
    if (mDir == 0) {
        if (cur->f == 4) {
            auto iter = l_backs.find(string(cur->l_front));
            if (iter == l_backs.end()) return 0;
             
            auto begin = (*iter).second.begin();
            if (begin == (*iter).second.end()) return 0;
            if (cur == *begin) begin++;
            if (begin == (*iter).second.end()) return 0;
            cur = *begin;
        }
        else {
            auto iter = backs.find(string(cur->front));
            if (iter == backs.end()) return 0;
 
            auto begin = (*iter).second.begin();
            if (begin == (*iter).second.end()) return 0;
            if (cur == *begin) begin++;
            if (begin == (*iter).second.end()) return 0;
            cur = *begin;
        }
    }
    else if (mDir == 1) {
        auto iter = mids.find(string(cur->mid));
        if (iter == mids.end()) return 0;
 
        auto begin = (*iter).second.begin();
        if (begin == (*iter).second.end()) return 0;
        if (cur == *begin) begin++;
        if (begin == (*iter).second.end()) return 0;
        cur = *begin;
    }
    else {
        if (cur->b == 4) {
            auto iter = l_fronts.find(string(cur->l_back));
            if (iter == l_fronts.end()) return 0;
 
            auto begin = (*iter).second.begin();
            if (begin == (*iter).second.end()) return 0;
            if (cur == *begin) begin++;
            if (begin == (*iter).second.end()) return 0;
            cur = *begin;
        }
        else {
            auto iter = fronts.find(string(cur->back));
            if (iter == fronts.end()) return 0;
 
            auto begin = (*iter).second.begin();
            if (begin == (*iter).second.end()) return 0;
            if (cur == *begin) begin++;
            if (begin == (*iter).second.end()) return 0;
            cur = *begin;
        }
    }
 
    return cur->id;
}
 
void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
    Room* room = get_room[mWord];
 
    // 기존꺼 다 삭제
    // front, back, l_front, l_back, mid
    fronts[room->front]      .erase(fronts[room->front].find(room));
    backs[room->back]        .erase(backs[room->back].find(room));
    l_fronts[room->l_front]  .erase(l_fronts[room->l_front].find(room));
    l_backs[room->l_back]    .erase(l_backs[room->l_back].find(room));
    mids[room->mid]          .erase(mids[room->mid].find(room));
 
    get_room.erase(string(mWord));
 
    room->init(room->id, mChgWord);
    word(room, mChgWord, mChgLen[0], mChgLen[2]);
    get_room[string(mChgWord)] = room;
 
}