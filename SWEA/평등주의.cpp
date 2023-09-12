#include<iostream>
#include<algorithm>
#include<cstring>

#define MAX 100000

using namespace std;

int ori[MAX];
int arr[MAX];
int N, K;

int main(int argc, char** argv)
{
	ios::sync_with_stdio(0);
 	cin.tie(0);
    
	int test_case;
	int T;
  
	cin >> T;
	int i, cnt, diff, ab;
	int M = 0, m = MAX;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> K;
		for (i = 0; i < N; i++) {
			cin >> ori[i];
			M = max(M, ori[i]);
			m = min(m, ori[i]);
		}

		M -= m;
		m = 0;

		
		while (m < M) {
			// 정답 배열 arr로 복사
			cnt = 0;
			memcpy(arr, ori, sizeof(int)*N);


			diff = (M + m) >> 1;
			//printf("\ndiff %d 로 시작\n", diff);

			// ->
			i = -1;
			while ((cnt <= K) & (i++ < N - 1)) {
				// 오른쪽보고 오른쪽 줄이기
				if (arr[i + 1] == 1) continue;

				ab = arr[i + 1] - arr[i];
				if (ab > diff) {
					arr[i + 1] -= (ab - diff);
					cnt += (ab - diff);
				}
			}
			if (cnt > K) {
				m = diff + 1;
				continue;
			}

			while ((cnt <= K) & (--i >= 1)) { // i = N-1 부터
				// 왼쪽보고 왼쪽 줄이기
				if (arr[i - 1] == 1) continue;

				ab = arr[i - 1] - arr[i];
				if (ab > diff) {
					arr[i - 1] -= (ab - diff);
					cnt += (ab - diff);
				}
			}

			if (cnt > K) {
				m = diff + 1;
				continue;
			}
			M = diff;
		}
        
        	printf("#%d %d\n", test_case, m);        
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
