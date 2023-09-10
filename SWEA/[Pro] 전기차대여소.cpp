#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 350

using namespace std;

pair<int, int> dirs[] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };

int map[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];

vector<pair<int, int>> charger;
vector<int> graph[200];
int d[200][200];

int d_visited[200];
int dijkstra[200];

int n, full, max_id;

int check(int r, int c) {
	if ((0 <= r & r < n) & (0 <= c & c < n)) {
		return 1;
	}
	return 0;
}

void init(int N, int mRange, int mMap[MAX_N][MAX_N])
{
	n = N;
	full = mRange;

	memcpy(map, mMap, sizeof(map));
	charger.clear();
	
	memset(d, -1, sizeof(d));
	for (int i = 0; i <= max_id; i++) {
		graph[i].clear();
	}
	return;
}

void bfs(int mFrom, int mTo) {
	pair<int, int> cur = charger[mFrom];
	pair<int, int> end = charger[mTo];

	memset(visited, 0, sizeof(visited));

	int nx, ny, dist;

	queue<pair<pair<int, int>, int>> q;
	q.push({ cur, 0 });
	visited[cur.first][cur.second] = 1;

	while (!q.empty()) {
		cur = q.front().first;
		dist = q.front().second;

		if (dist > full) {
			//d[mFrom][mTo] = -1;
			//d[mTo ][mFrom] = -1;
			break;
		}

		if (cur == end) {
			// 도착했으면
			d[mFrom][mTo] = dist;
			d[mTo][mFrom] = dist;
			graph[mFrom].push_back(mTo);
			graph[mTo].push_back(mFrom);
			break;
		}

		for (pair<int, int> d : dirs) {
			nx = cur.first + d.first;
			ny = cur.second + d.second;

			if (check(nx, ny) & (map[nx][ny] != 1) & (!visited[nx][ny])) {
				visited[nx][ny] = 1;
				q.push({ {nx, ny}, dist + 1 });
			}
		}

		q.pop();
	}
}

void add(int mID, int mRow, int mCol)
{
	// 지도 표시
	map[mRow][mCol] = -1;

	// 충전소 위치 저장
	charger.push_back({ mRow, mCol });

	for (int i = 0; i < mID; i++) {
		bfs(i, mID);
	}
	max_id = mID;

	return;
}

int distance(int mFrom, int mTo)
{
	if (graph[mFrom].empty()) {
		return -1;
	}

	int cur, r;
	int ans = n * n;
	memset(d_visited, 0, sizeof(d_visited));
	fill(dijkstra, dijkstra+max_id+1, n*n);

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, mFrom });
	dijkstra[mFrom] = 0;
	d_visited[mFrom] = 1;

	while (!pq.empty()) {
		r = pq.top().first;
		cur = pq.top().second;
		pq.pop();

		if (cur == mTo) {

		}
		else {
			for (int g : graph[cur]) {
				if (!d_visited[g]) {
					int cur_d = d[cur][g] + r;
					int ori = dijkstra[g];

					if (cur_d < ori) {
						d_visited[g] = 1;
						dijkstra[g] = cur_d;
						pq.emplace(dijkstra[g], g);
					}

				}
			}
		}
	}

	return dijkstra[mTo] == n*n ? -1 : dijkstra[mTo];
}