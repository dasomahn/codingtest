#include<iostream>
#include<string>
#include<algorithm>
 
using namespace std;
 
int n, len;
int sum, M;
 
string s_num;
char temp;
 
void dfs(int left, int right, int depth) {
 
    if ((depth == n) | (depth >= len)) {
        // sum
        sum = s_num[0] - '0';
        for (int i = 1; i < len; i++) {
            sum *= 10;
            sum += s_num[i] - '0';
        }
        M = max(M, sum);
 
    } else {
        for (int i = left; i < len - 1; i++) {
            for (int j = i + 1; j < len; j++) {
                swap(s_num[i], s_num[j]);
                dfs(i, j, depth + 1);
                swap(s_num[i], s_num[j]);
             }
        }
    }
}

int main(int argc, char** argv) {
    int test_case;
    int T;
 
    cin >> T;
 
    int num, i;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> num;
        cin >> n;
        //printf("\nstart\t %d %d ---", num, n);
 
        s_num = to_string(num);
        len = s_num.length();
        //cout << s_num << " len: " << len << endl;
 
        M = 0;
        dfs(0, 0, 0);
        cout << "#" << test_case << " " << M << endl;
    }
    return 0;
}