#include <iostream>
#include <cstring>
#include <queue>

#define MAX_N 350
#define MAX_ID 200

using namespace std;

int dirs[][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

int map[MAX_N][MAX_N];
int n, range, max_id;

int visited[MAX_N][MAX_N]; // bfs용
vector<pair<int, int>> graph[MAX_ID]; // node, weight

int visited_dist[MAX_ID]; // dijsktra용

void init(int N, int mRange, int mMap[MAX_N][MAX_N])
{
	memcpy(map, mMap, sizeof(map));

	for (int i = 0; i < MAX_ID; i++) {
		graph[i].clear();
	}

	n = N;
	range = mRange;
	max_id = 0;

	return;
}

bool bound(int x, int y) {
	if ((0 <= x) & (x < n) & (0 <= y) & (y < n)) {
		return true;
	}
	return false;
}

void bfs(int mID, int mRow, int mCol) {
	int x, y, nx, ny, d;

	memset(visited, -1, sizeof(visited));

	queue<pair<int, int>> q;
	q.emplace(mRow, mCol);
	visited[mRow][mCol] = 0;

	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second;
		d = visited[x][y];
		q.pop();

		if ((map[x][y] >= 2) & (d != 0)) { // 대여소 방문
			int id = map[x][y] - 2;
			graph[mID].emplace_back(id, d);
			graph[id].emplace_back(mID, d);
		}

		for (int i = 0; i < 4; i++) {
			nx = x + dirs[i][0];
			ny = y + dirs[i][1];

			if (bound(nx, ny) & (map[nx][ny] != 1) & (visited[nx][ny] == -1) & (d + 1 <= range)) {
				visited[nx][ny] = d + 1;
				q.emplace(nx, ny);
			}
		}
	}
}

void add(int mID, int mRow, int mCol)
{
	max_id++;
	map[mRow][mCol] = mID + 2;

	bfs(mID, mRow, mCol);
	return;
}

int distance(int mFrom, int mTo)
{
	int node, d;

	fill_n(visited_dist, max_id + 1, n*n);
	
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 거리, 노드
	visited_dist[mFrom] = 0;
	pq.emplace(0, mFrom);

	while (!pq.empty()) {
		d = pq.top().first;
		node = pq.top().second;
		pq.pop();

		if (d > visited_dist[node]) continue;
		if (node == mTo) break;

		for (auto g : graph[node]) {
			if (d + g.second < visited_dist[g.first]) {
				visited_dist[g.first] = d + g.second;
				pq.emplace(d + g.second, g.first);
			}
		}   
	}

	return visited_dist[mTo] == n*n? -1: visited_dist[mTo];
}