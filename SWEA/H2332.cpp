#include <vector>

using namespace std;

#define MAX_N 20
#define MAX_HASH 9999
#define INF 987654321

int N;
int map[MAX_N][MAX_N];
int visit[MAX_N + 2][MAX_N + 2];

int dir[4][2] = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

struct Candidate {
    int row;
    int col;
    bool isHorizontal;
};

struct Section {
    int row;
    int col;
    int height;
};

vector<Candidate> HASH[9999];

void init(int N, int mMap[MAX_N][MAX_N])
{
    for (int i = 0; i < MAX_HASH; i++) {
        HASH[i].clear();
    }
    ::N = N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            map[i][j] = mMap[i][j];
        }
    }
 
    int horKey, verKey;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            horKey = 0, verKey = 0;
            for (int k = 1; k < 5; k++) {
                if (j + k >= N) break;
 
                horKey = horKey * 10 + map[i][j + k] - map[i][j + k - 1] + 5;
                HASH[horKey].push_back({ i, j, true });
 
                verKey = verKey * 10 + map[j + k][i] - map[j + k - 1][i] + 5;
                HASH[verKey].push_back({ j, i, false });
            }
        }
    }
}

int get_block_hash_key(int M, int value[5]) {
    int hash_key = 0;
    for (int i = 0; i < M - 1; i++) {
        hash_key *= 10;
        hash_key += (value[i + 1] - value[i] + 5);
    }
    return hash_key;
}

int numberOfCandidate(int M, int mStructure[])
{
    int key = 0, rkey = 0;
    for (int i = 1; i < M; i++) {
        key = key * 10 + mStructure[i - 1] - mStructure[i] + 5;
        rkey = rkey * 10 + mStructure[M - i] - mStructure[M - i - 1] + 5;
    }
    int count = HASH[key].size();
    if (key != rkey)
        count += HASH[rkey].size();
    return count;
}

int floodfill(int mDir, int row, int col, int M, bool isH, int h) {
 
    int head = 0;
    int tail = 0;
    Section q[401];

    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < N + 2; j++) {
            visit[i][j] = 0;
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            visit[i][j] = map[i - 1][j - 1];
        }
    }
    row++;
    col++;
    for (int i = 0; i < M; i++) {
        if (isH)
            visit[row][col + i] = h;
        else
            visit[row + i][col] = h;
    }
    if (mDir == 0) {
        for (int i = 1; i < N + 1; i++) {
            int height = visit[1][i];
            q[tail++] = { 1, i, height };
            visit[1][i] = -1;
        }
    }
    else if (mDir == 1) {
        for (int i = 1; i < N + 1; i++) {
            int height = visit[i][N];
            q[tail++] = { i, N, height };
            //q.push({ i, N, height });
            visit[i][N] = -1;
        }
    }
    else if (mDir == 2) {
        for (int i = 1; i < N + 1; i++) {
            int height = visit[N][i];
            q[tail++] = { N, i, height };
            //q.push({ N, i, height });
            visit[N][i] = -1;
        }
    }
    else if (mDir == 3) {
        for (int i = 1; i < N + 1; i++) {
            int height = visit[i][1];
            q[tail++] = { i, 1, height };
            //q.push({ i, 1, height });
            visit[i][1] = -1;
        }
    }
 
    int cnt = 0;
    while (head < tail) {
        Section sec = q[head++];
        cnt++;
        for (int i = 0; i < 4; i++) {
            int rr = sec.row + dir[i][0];
            int cc = sec.col + dir[i][1];
            int next_height = visit[rr][cc];
            if (next_height < 1 || next_height < sec.height) continue;
            q[tail++] = { rr, cc, next_height };
            //q.push({ rr, cc, next_height });
            visit[rr][cc] = -1;
        }
    }
    return cnt;
 
}

int maxBlockedRobots(int M, int mStructure[], int mDir)
{
    int key = 0, rkey = 0;
    int value[5] = { mStructure[0] };
    int rvalue[5] = { mStructure[M - 1] };
 
    for (int i = 1; i < M; i++) {
        value[i] = mStructure[i];
        rvalue[i] = mStructure[M - i - 1];
        key = key * 10 + mStructure[i - 1] - mStructure[i] + 5;
        rkey = rkey * 10 + mStructure[M - i] - mStructure[M - i - 1] + 5;
    }
 
    int count = INF;
    vector<Candidate> &v = HASH[key];
    for (Candidate c : v) {
        int h = value[0] + map[c.row][c.col];
        int val = floodfill(mDir, c.row, c.col, M, c.isHorizontal, h);
        count = val < count ? val : count;
    }
    if (key != rkey) {
        vector<Candidate> &v = HASH[rkey];
        for (Candidate c : v) {
            int h = rvalue[0] + map[c.row][c.col];
            int val = floodfill(mDir, c.row, c.col, M, c.isHorizontal, h);
            count = val < count ? val : count;
        }
    }
    int ret = N * N - count;
    return ret;
}