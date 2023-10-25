#include <cstring>
#include <algorithm>
 
using namespace std;
 
#define MAX 1000000
#define MIN 10000
#define ll long long
#define pi pair<int, int>
 
int arr[MAX];
pi seg[MAX * 4];
int lazy[MAX*4];
 
ll total;
int l, r;
int c, er;
 
pi cmp(pi a, pi b) {
    return { max(a.first, b.first), min(a.second, b.second) };
}
 
void updateLazy(int idx, int start, int end) {
    if (lazy[idx]) {
        seg[idx].first += lazy[idx];
        seg[idx].second += lazy[idx];
        if (start != end) {
            lazy[idx * 2] += lazy[idx];
            lazy[idx * 2 + 1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}
 
void updateSeg(int idx, int start, int end, int x) {
    updateLazy(idx, start, end);
     
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        seg[idx].first += x;
        seg[idx].second += x;
        if (start != end) {
            lazy[idx * 2] += x;
            lazy[idx * 2 + 1] += x;
        }
        return;
    }
 
    int mid = (start + end) / 2;
    updateSeg(idx * 2, start, mid, x);
    updateSeg(idx * 2 + 1, mid + 1, end, x);
    seg[idx] = cmp(seg[idx * 2], seg[idx * 2 + 1]);
}
 
struct Result {
    int top;
    int count;
};
 
void init(int C)
{
    total = 0;
    er = 0;
    c = C;
    memset(seg, 0, sizeof(seg));
    memset(lazy, 0, sizeof(lazy));
}
 
Result dropBlocks(int mCol, int mHeight, int mLength)
{
    int ret = 0;
    total += mLength * mHeight;
 
    l = mCol, r = mCol + mLength - 1;
 
    updateSeg(1, 0, c - 1, mHeight);
 
    int maximum = seg[1].first;
    int minimum = seg[1].second;
 
    total -= (minimum - er) * c;
    er = minimum;
 
    return { maximum - minimum, total % 1000000 };
}