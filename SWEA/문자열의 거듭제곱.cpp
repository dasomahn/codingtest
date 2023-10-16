#include <iostream>
#include <cstring>
#include <vector>
 
#define MAX 1000000
 
using namespace std;
 
char str[MAX];
 
// 최대 일치 길이 배열
vector<int> makeTable(char *pattern) {
    int len = strlen(pattern);
    vector<int> table(len, 0);
 
    int start = 0;
    for (int end = 1; end < len; end++) {
        while (start > 0 && pattern[start] != pattern[end]) {
            start = table[start - 1];
        }
 
        if (pattern[start] == pattern[end]) {
            table[end] = ++start;
        }
    }
 
    return table;
}
 
int main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(0);
     
    int test_case;
    int T;
     
    scanf("%d", &T);
     
    for (test_case = 1; test_case <= T; ++test_case)
    {
        scanf("%s", str);
 
        vector<int> table = makeTable(str);
        int len = strlen(str);
 
        if (len % (len - table[len - 1] != 0)) {
            printf("#%d %d\n", test_case, 1);
        }
        else {
            printf("#%d %d\n", test_case, len / (len - table[len - 1]));
        }
 
    }
    return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}