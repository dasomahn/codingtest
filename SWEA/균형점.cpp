#include<iostream>

using namespace std;

int main(int argc, char** argv) {

	freopen("input_������.txt", "r", stdin);

	int test_case;
	int T;

	cin >> T;

	int i, n;
	double low, mid, high;

	double dist, cal;

	double pos[10];
	double mass[10];

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> n;

		// �Է� �ޱ�
		for (i = 0; i < n; i++) {
			cin >> pos[i]; // ��ǥ
		}

		for (i = 0; i < n; i++) {
			cin >> mass[i]; // ����
		}

		printf("#%d ", test_case);
		for (i = 1; i < n; i++) {
			low = pos[i - 1];
			high = pos[i];

			while (high - low > 0.000000000001) {
				mid = (low + high) / 2;

				cal = 0.0;
				for (int j = 0; j < i; j++) {
					dist = mid - pos[j];
					cal += (mass[j]) / (dist * dist);
				}

				for (int j = i; j < n; j++) {
					dist = pos[j] - mid;
					cal -= (mass[j]) / (dist * dist);
				}

				/*if (abs(cal) <= 0.000000000001) {
					break;
				}*/

				// �̰� �ְ������ ���̰� ���� ...

				if (cal > 0) {
					low = mid;
				}
				else {
					high = mid;
				}
			}
			printf("%.10lf ", mid);
		}
		printf("\n");
	}
	return 0;
}