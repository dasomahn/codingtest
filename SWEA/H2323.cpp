#include <cstring>
 
extern void scanFromRobot(int ceilingState[3][3]);
extern int moveRobot(int mCommand);
 
int n, dir;
int scan[3][3];
bool visited[60][60];
 
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };
 
void init(int N, int subTaskCount)
{
    n = N;
}
 
void dfs(int x, int y) {
    register int nx, ny, cmd;
 
    visited[x][y] = 1;
 
    for (register int i = 0; i < 4; i++) {
        nx = x + dx[i];
        ny = y + dy[i];
 
        cmd = (4 - dir + i) % 4; // dir만큼 원복하고, i만큼 가기
 
        scanFromRobot(scan);
        if (!scan[1 + dx[cmd]][1 + dy[cmd]] && !visited[nx][ny]) {
            dir = i;
            moveRobot(cmd);
             
            dfs(nx, ny);
 
            moveRobot(((4 - dir + i) + 2) % 4);
            dir = (i + 2) % 4;
        }
    }
}
 
void cleanHouse(int mLimitMoveCount)
{
    dir = 0;
    memset(visited, 0, sizeof(visited));
    dfs(n, n);
}