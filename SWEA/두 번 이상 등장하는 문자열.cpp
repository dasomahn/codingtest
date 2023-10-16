#include <algorithm>
#include <iostream>
 
#define MAX 200000
 
using namespace std;
 
int L;
char str[MAX];
 
int t, suffixArray[MAX], group[MAX], team[MAX];
int Rank[MAX];
int LCP[MAX];
 
bool cmp(int a, int b) {
    if (group[a] == group[b]) {
        return group[a + t] < group[b + t];
    }
    return group[a] < group[b];
}
 
void getSuffixArray() {
    t = 1;
 
    for (int i = 0; i < L; i++) {
        suffixArray[i] = i;
        group[i] = str[i] - 'a';
    }
 
    while (t <= L) {
        sort(suffixArray, suffixArray + L, cmp);
        team[suffixArray[0]] = 0;
 
        for (int i = 1; i < L; i++) {
            if (cmp(suffixArray[i - 1], suffixArray[i])) {
                team[suffixArray[i]] = team[suffixArray[i - 1]] + 1;
            }
            else {
                team[suffixArray[i]] = team[suffixArray[i - 1]];
            }
        }
 
        for (int i = 0; i < L; i++) {
            group[i] = team[i];
        }
        t <<= 1;
    }
}
 
int main(void)
{
    int test_case;
    int T;
    scanf("%d", &T);
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> L;
        scanf("%s", str);
 
        getSuffixArray();
 
        for (int i = 0; i < L; i++) {
            Rank[suffixArray[i]] = i;
        }
 
        int len = 0;
        for (int i = 0; i < L; i++) {
            int k = Rank[i];
            if (k) {
                int j = suffixArray[k - 1];
 
                while (str[i + len] == str[j + len]) {
                    len++;
                }
                LCP[k] = len;
 
                if (len) len--;
            }
        }
 
        sort(LCP, LCP + L);
        printf("#%d %d\n", test_case, LCP[L - 1]);
 
    }
    return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}