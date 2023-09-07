#include<iostream>
#include<string>
 
using namespace std;
 
int main(int argc, char** argv) {
    int test_case;
    int T = 10;
 
    string haystack, needle;
    int pos, ans, len;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> test_case;
        cin >> needle >> haystack;
        len = needle.length();
 
        ans = pos = 0;
        while (haystack.find(needle, pos) != string::npos) {
            pos += haystack.find(needle, pos) + len;
            ans++;
        }
 
        // 출력
        cout << "#" << test_case << " " << ans << endl;
    }
    return 0;
}