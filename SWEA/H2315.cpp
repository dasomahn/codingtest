#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
 
#define MAX 10000
 
using namespace std;
 
struct Bucket;
struct Rect;
 
struct Rect {
    int id;
    int rank;
 
    int rowStart;
    int colStart;
 
    int height;
    int width;
 
    vector<Bucket*> buckets;
 
    void init(int _id, int r, int c, int h, int w, int _rank) {
        id = _id;
        rank = _rank;
 
        rowStart = r;
        height = h;
 
        colStart = c;
        width = w;
 
        buckets.clear();
    }
 
} Rects[MAX + 1];
 
struct cmp {
    bool operator() (Rect* a, Rect* b) const {
        return a->rank > b->rank;
    }
};
 
struct Bucket {
    int i;
    set<Rect*, cmp> rects;
 
} Buckets[101*101];
 
int front;
int realSize;
 
void init(int);
void addRect(int, int, int, int, int);
void selectAndMove(int, int, int, int);
int moveFront(int);
int selectAndErase(int, int);
int check(int, int);
void erase(int);
 
void init(int N)
{
    realSize = sqrt(N);
    realSize++;
 
    for (int i = 0; i < realSize*realSize; i++) {
        Buckets[i].i = i;
        Buckets[i].rects.clear();
    }
 
    front = 1;
    Rects[0].id = 0;
}
 
Rect* add(int mID, int mY, int mX, int mHeight, int mWidth, int r) {
    Rect* rect = &Rects[mID];
    rect->init(mID, mY, mX, mHeight, mWidth, r);
 
    int up = mY / realSize;
    int down = (mY + mHeight - 1) / realSize;
 
    int left = mX / realSize;
    int right = (mX + mWidth - 1) / realSize;
 
    for (; up <= down; up++) {
        for (int i = left; i <= right; i++) {
            Buckets[up*realSize + i].rects.emplace(rect);
            rect->buckets.emplace_back(&Buckets[up*realSize + i]);
        }
    }
 
    return rect;
}
 
void addRect(int mID, int mY, int mX, int mHeight, int mWidth)
{
    Rect* rect = add(mID, mY, mX, mHeight, mWidth, front++);
}
 
void selectAndMove(int y1, int x1, int y2, int x2)
{
    int mID = selectAndErase(y1, x1);
    add(mID, y2, x2, Rects[mID].height, Rects[mID].width, Rects[mID].rank);
}
 
bool overlap(Rect* rect, Rect* s) {
    if (s->rowStart <= rect->rowStart + rect->height - 1 // 대상의 시작 <= 기준 끝
        && rect->rowStart <= s->rowStart + s->height - 1) // 기준 시작 <= 대상 끝
        if (s->colStart <= rect->colStart + rect->width - 1
            && rect->colStart <= s->colStart + s->width - 1)
            return true;
    return false;
}
 
int moveFront(int mID)
{
    if (!Rects[mID].id) return 0;
 
    erase(mID);
    Rect* rect = add(mID, Rects[mID].rowStart, Rects[mID].colStart, 
        Rects[mID].height, Rects[mID].width, front++);
 
    set<Rect*, cmp> list;
    list.emplace(&Rects[0]);
 
    for (auto a : rect->buckets) {
        for (auto s : a->rects) {
            if (rect == s) continue;
            if (rect != s && overlap(rect, s)) {
                list.emplace(s);
            }
        }
    }
 
    return (*list.begin())->id;
}
 
void erase(int id) {
    Rect* rect = &Rects[id];
 
    for (auto a : rect->buckets) {
        a->rects.erase(rect);
    }
    rect->buckets.clear();
 
    rect->id = 0;
}
 
int selectAndErase(int mY, int mX)
{
    int id = check(mY, mX);
    if (!id) return 0;
 
    erase(id);
    return id;
}
 
int check(int mY, int mX)
{
    int up = (mY / realSize) * realSize;
    int left = mX / realSize;
 
    Bucket* bucket = &Buckets[up + left];
 
 
    for (auto a : bucket->rects) {
        if (a->rowStart <= mY && mY <= a->rowStart + a->height - 1) {
            if (a->colStart <= mX && mX <= a->colStart + a->width - 1) {
                if (a->id) return a->id;
            }
        }
    }
 
    return 0;
}