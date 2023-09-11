#include<iostream>
#include<stdio.h>
#include<algorithm>

#define MAX 200000

using namespace std;

int arr[MAX];
int group[MAX];
int divide[MAX];
int N, K;

int find (int x) {
	int flag;

	int idx = 0; // 그룹핑 인덱스
	int i = 0; // 숫자 arr 인덱스
	int cnt = 0;

	while ((idx < K) & (i < N)) {
		int cur = group[idx];

		while ((arr[i] > x) & (i < N)) { // 클 때
			i++;
		}
		while ((arr[i] <= x) & (i < N) & (cur > 0)) { // 작을 때
			i++;
			cur--;
		}
		if (cur == 0) {
			idx++;
		}
	}
	return idx;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin >> T;

	int i;
	int M = 0;
	int m = MAX;
	int upper, lower;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> K;

		for (i = 0; i < N; i++) {
			cin >> arr[i];
			m = min(arr[i], m);
			M = max(arr[i], M);
		}

		for (i = 0; i < K; i++) {
			cin >> group[i];
		}

		while (m < M) {
			int mid = (M + m) >> 1;  // 나누기 2

			int result = find(mid);
			if (result == K) {
				M = mid;
			}
			else {
				m = mid + 1;
			}
		}

		printf("#%d %d\n", test_case, m);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

