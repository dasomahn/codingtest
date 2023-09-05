#include<iostream>
#include<map>

using namespace std;

int find_code(char* arr, int M) {
	for (int i = M; i > 0; --i) {
		if (arr[i] == '1') return i;
	}

	return 0;
}

int decode(char* p) {
	int key = 0;
	int flag = 0;

	while (key < 1000) {
		key *= 10;
		while (flag + 48 == *p) {
			key++;
			p++;
		}
		flag ^= 1;
	}
	return key;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	const int max = 100; // define?
	char buf[max];
	int N, M, start, end;

	int num[8];
	int odd, even;

	map<int, int> m;
	m.insert({ 3211, 0 });
	m.insert({ 2221, 1 });
	m.insert({ 2122, 2 });
	m.insert({ 1411, 3 });
	m.insert({ 1132, 4 });
	m.insert({ 1231, 5 });
	m.insert({ 1114, 6 });
	m.insert({ 1312, 7 });
	m.insert({ 1213, 8 });
	m.insert({ 3112, 9 });

	for (test_case = 1; test_case <= T; ++test_case)
	{
		odd = even = 0;
        cin >> N; // 10
		cin >> M; // 70

		while (N > 0) {
			// 한줄 받기
			for (int i = 0; i < M; i++) {
				cin >> buf[i];
			}

			if (end = (find_code(buf, M))) {
				break;
			}
			N--;
		}

		start = end - 56 + 1;
		for (int i = 0; i < 8; i++) {
			num[i] = m.find(decode(buf + start)) -> second;
			start += 7;
		}

		for (int i = 0; i < 8; i++) {
			odd += num[i];
			i++;
			even += num[i];
		}

		if ((odd*3 + even) % 10) {
			odd = even = 0;
		}

		cout << "#" << test_case << " " << odd + even << endl;

		while (N > 1) {
			// 한줄 받기, 나머지 줄 털기
			for (int i = 0; i < M; i++) {
				cin >> buf[i];
			}
			N--;
		}
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}