#include <iostream>
#include <algorithm>
#include <cstring>
 
#define MAX 100001
 
using namespace std;
typedef pair<int, int> pi;
 
int n;
int arr[MAX];
pi segtree[MAX*4];
 
pi myMax(pi left, pi right) {
    if (left.first > right.first) {
        return left;
    }
    return right;
}
 
pi initSeg(int start, int end, int idx) {
    if (start == end) {
        segtree[idx] = { 0, start };
        return segtree[idx];
    }
    int mid = (start + end) >> 1;
 
    segtree[idx] = myMax(initSeg(start, mid, idx * 2), initSeg(mid + 1, end, idx * 2 + 1));
    return segtree[idx];
}
 
pi getSeg(int start, int end, int left, int right, int idx) {
    if ((end < left) | (right < start)) {
        return { -1, -1 };
    }
 
    // 전부 포함된 범위
    if ((left <= start) & (end <= right)) {
        //printf("%d~%d는 다 봐도 됨\n", start, end);
        return segtree[idx];
    }
 
    // 일부 포함된 범위
    int mid = (start + end) >> 1;
    return myMax(getSeg(start, mid, left, right, idx * 2),
        getSeg(mid + 1, end, left, right, idx * 2 + 1));
}
 
pi updateSeg(int start, int end, int who, int how, int idx) {
    // 범위 벗어남
    if ((who < start) | (end < who)) {
        return segtree[idx];
    }
    // 자기 자신
    if (start == end) {
        segtree[idx] = { how, who };
        return segtree[idx];
    }
 
    int mid = (start + end) >> 1;
    segtree[idx] = myMax(updateSeg(start, mid, who, how, idx * 2),
        updateSeg(mid + 1, end, who, how, idx * 2 + 1));
    return segtree[idx];
}
 
void init(int N)
{
    memset(arr, 0, sizeof(arr));
    initSeg(0, N-1, 1);
 
    n = N;
 
    return;
}
 
int left(int start, int end) {
    if (end < 0) {
        return 0;
    }
    pi m = getSeg(0, n - 1, start, end, 1); // 부분 max 값, 해당 idx
    if (m.first == 0) return (end - m.second + 1) * m.first;
     
    return left(0, m.second - 1) + (end - m.second + 1) * m.first;
}
int right(int start, int end) {
    if (start >= n) {
        return 0;
    }
    pi m = getSeg(0, n - 1, start, end, 1); // 부분 max 값, 해당 idx
 
    return right(m.second + 1, n - 1) + (m.second - start + 1) * m.first;
}
 
int calculate(int idx) {
    return arr[idx] + left(0, idx - 1) + right(idx + 1, n - 1);
}
 
int stock(int mLoc, int mBox)
{
    int loc = mLoc - 1;
 
    arr[loc] += mBox;
    int M_idx = updateSeg(0, n - 1, loc, arr[loc], 1).second;
 
    return calculate(M_idx);
}
 
int ship(int mLoc, int mBox)
{
    int loc = mLoc - 1;
    arr[loc] -= mBox;
    int M_idx = updateSeg(0, n - 1, loc, arr[loc], 1).second;
 
    return calculate(M_idx);
}
 
int getHeight(int mLoc)
{
    return arr[mLoc-1];
}