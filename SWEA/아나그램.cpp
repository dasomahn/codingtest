#include <iostream>
#include <cstring>
 
#define ALPHA 26
 
using namespace std;
 
int FindAnagram(int Len1, char *S1, int Len2, char *S2) {
    int answer = 0;
 
    char arr1[ALPHA];
    char arr2[ALPHA];
    memset(arr1, 0, sizeof(arr1));
    memset(arr2, 0, sizeof(arr2));
 
    int i;
 
    string s1 = S1;
    string s2 = S2;
 
    // s1의 구성 확인
    for (i = 0; i < Len1; i++) {
        arr1[S1[i] - 'a']++;
    }
 
    // s2의 부분문자열 추출
    for (i = 0; i < Len1 - 1; i++) {
        arr2[S2[i] - 'a']++;
    }
 
    for (i = Len1 - 1; i < Len2; i++) {
        arr2[S2[i] - 'a']++;
 
 
        // 정답과 부분문자열 비교
        if (memcmp(arr1, arr2, ALPHA) == 0) answer++;
 
        arr2[S2[i - Len1 + 1] - 'a']--;
    }
 
    return answer;
}