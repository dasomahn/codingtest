#include <iostream>
#include <cstring>
#include <queue>
 
#define M 201
#define pi pair<int, int>
 
using namespace std;
 
struct Result
{
    int row;
    int col;
};
 
struct Bacteria
{
    int id;
    int size;
    int time;
 
} Bacterium[300001];
int bactCnt;
 
int arr[M][M];
bool visited[M][M];
 
int n; // 셀 크기
int avail;
int row, col;
 
priority_queue<pi, vector<pi>, greater<pi>> pq;
 
pi dirs[4] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
 
void init(int N)
{
    n = N;
     
    bactCnt = 0;
    memset(arr, 0, sizeof(arr));
 
    avail = N * N;
}
 
bool check(int r, int c) {
    if ((1 <= r && r <= n) && (1 <= c && c <= n)) return true;
    return false;
}
 
struct cmp {
    bool operator()(pi a, pi b) {
        int dist_a = abs(a.first - row) + abs(a.second - col);
        int dist_b = abs(b.first - row) + abs(b.second - col);
 
        if (dist_a == dist_b) {
            if (a.first == b.first) {
                return a.second > b.second;
            }
            return a.first > b.first;
        }
        return dist_a > dist_b;
    }
};
 
Result putBacteria(int mTime, int mRow, int mCol, Bacteria mBac)
{
    int i = 0, cnt = 0;
    int spread = 0;
    int  r, c, nr = mRow, nc = mCol;
 
    Bacterium[mBac.id].id = mBac.id;
    Bacterium[mBac.id].time = 0;
 
    //if (mBac.size > avail) return { 0, 0 };
    if (arr[nr][nc] && Bacterium[arr[nr][nc]].time > mTime) return { 0, 0 };
 
 
    //print_map();
 
    memset(visited, 0, sizeof(visited));
 
    queue<pi> queue;
    queue.emplace(mRow, mCol);
 
    while (!queue.empty() && cnt < mBac.size) {
        r = queue.front().first;
        c = queue.front().second;
        queue.pop();
        cnt++;
 
 
        if (cnt == mBac.size) break;
 
        // 상하좌우
        for (i = 0; i < 4; i++) {
            nr = r + dirs[i].first;
            nc = c + dirs[i].second;
 
            if (!check(nr, nc) || visited[nr][nc]) continue;
            if (arr[nr][nc]
                && Bacterium[arr[nr][nc]].time > mTime) continue;
 
            visited[nr][nc] = true;
 
            queue.emplace(nr, nc);
        }
    }
 
    if (cnt != mBac.size) return { 0, 0 };
 
    cnt = 0;
    memset(visited, 0, sizeof(visited));
 
    priority_queue<pi, vector<pi>, cmp> q;
    row = mRow;
    col = mCol;
 
    q.emplace(mRow, mCol);
    visited[mRow][mCol] = 1;
 
    while (!q.empty() && cnt < mBac.size) {
        r = q.top().first;
        c = q.top().second;
        q.pop();
         
        arr[r][c] = mBac.id;
        cnt++;
         
        if (cnt == mBac.size) break;
 
        // 상하좌우
        for (i = 0; i < 4; i++) {
            nr = r + dirs[i].first;
            nc = c + dirs[i].second;
 
            if (!check(nr, nc) || visited[nr][nc]) continue;
            if (arr[nr][nc]
                && Bacterium[arr[nr][nc]].time > mTime) continue;
             
            visited[nr][nc] = true;
            q.emplace(nr, nc);
        }
    }
 
    if (cnt < mBac.size) {
        return { 0, 0 };
    }
 
    Bacterium[mBac.id].time = mTime + mBac.time;
    Bacterium[mBac.id].size = mBac.size;
    avail -= cnt;
 
    return { r, c };
}
 
int killBacteria(int mTime, int mRow, int mCol)
{
    //checkTime(mTime);
 
    // 셀에 박테리아가 없을 경우
    if (!arr[mRow][mCol]) return 0;
    // 소멸됐을 경우
    if (Bacterium[arr[mRow][mCol]].time <= mTime) return 0;
 
    int id = arr[mRow][mCol];
    Bacterium[id].time = 0;
 
    avail += Bacterium[id].size;
    return id;
}
 
int checkCell(int mTime, int mRow, int mCol)
{
    //checkTime(mTime);
 
    // 셀에 박테리아가 없을 경우
    if (!arr[mRow][mCol]) return 0;
    // 소멸됐을 경우
    if (Bacterium[arr[mRow][mCol]].time <= mTime) return 0;
 
    return arr[mRow][mCol];
}