#include <cstring>
#include <vector>
 
using namespace std;
 
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
 
int FindString(int N, char *A, int M, char *B) {
    vector<int> table = makeTable(B);
 
    int answer = 0;
    int patternCnt = 0;
 
    vector<int> found_index;
    for (int parentCnt = 0; parentCnt < N; parentCnt++) {
        while (patternCnt > 0 && A[parentCnt] != B[patternCnt]) {
            patternCnt = table[patternCnt - 1];
        }
        if (A[parentCnt] == B[patternCnt]) {
            if (patternCnt == M - 1) {
                answer++;
                patternCnt = table[patternCnt];
            }
            else {
                patternCnt++;
            }
        }
    }
    return answer;
}