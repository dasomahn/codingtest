#include<iostream>
#include<algorithm>
#define M 1001
 
using namespace std;
 
int acc[M];
char arr[M];
int print[20];
 
int L, cnt;
 
void pos() {
    int half = acc[L - 1] >> 1;
 
    for (int i = L - 2; i >= 0; i--) {
        if (acc[i] == half) {
            print[cnt*2] = i+1;
            print[cnt*2 + 1] = L - 1;
            break;
        }
    }
}
 
int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int test_case;
    int T;
    cin >> T;
 
    int m, m_idx, i;
    char c;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cnt = 0;
        cin >> L >> arr;
     
        if (L & 1) {
            cout << "#" << test_case << " -1\n";
            continue;
        }
 
        arr[0] = (arr[0] == '(' ? 1 : -1);
        acc[0] = arr[0];
        m = arr[0];
        m_idx = 0;
         
        for (i = 1; i < L; i++) {
            arr[i] = (arr[i] == '(' ? 1 : -1);
            acc[i] = acc[i - 1] + arr[i];
             
            if (m > acc[i]) {
                m_idx = i;
                m = acc[i];
            }
        }
 
        char temp;
        if (m < 0) {
            cnt++;
            print[0] = 0;
            print[1] = m_idx;
             
            for (i = 0; i <= m_idx / 2; i++) {
                swap(arr[i], arr[m_idx - i]);
                if (i != m_idx - i) {
                    arr[i] = (arr[i] == 1 ? -1 : 1);
                }
                arr[m_idx - i] = (arr[m_idx - i] == 1 ? -1 : 1);
            }
 
            // 누적합
            acc[0] = arr[0];
            for (i = 1; i < L; i++) {
                acc[i] = acc[i - 1] + arr[i];
            }
 
            if (acc[L - 1]) {
                // 2분할 찾는 함수
                pos();
                cnt++;
            }
        }
        else if (!acc[L - 1]) { // 누적합이 0이면
             
        }
        else {
            // 2분할 찾는 함수
            pos();
            cnt++;
        }
 
        cout << "#" << test_case << " " << cnt << '\n';
        for (i = 0; i < cnt; i++) {
            cout << print[i*2] << " " << print[i*2 + 1] << "\n";
        }
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}