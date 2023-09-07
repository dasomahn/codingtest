include<iostream>
#include<string>
 
using namespace std;
 
int main(int argc, char** argv) {
    int test_case;
    int T;
    cin >> T;
 
    string code[] = { "ZRO", "ONE", "TWO", "THR", "FOR", "FIV", "SIX", "SVN", "EGT", "NIN" };
 
    int n, i;
    string arr[10000];
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        int count[10] = { 0, };
        cin >> n >> n;
 
        for (i = 0; i < n; i++) {
            cin >> arr[i];
        }
 
        for (i = 0; i < n; i++) {
            if (arr[i] == "ZRO") count[0]++;
            else if (arr[i] == "ONE") count[1]++;
            else if (arr[i] == "TWO") count[2]++;
            else if (arr[i] == "THR") count[3]++;
            else if (arr[i] == "FOR") count[4]++;
            else if (arr[i] == "FIV") count[5]++;
            else if (arr[i] == "SIX") count[6]++;
            else if (arr[i] == "SVN") count[7]++;
            else if (arr[i] == "EGT") count[8]++;
            else if (arr[i] == "NIN") count[9]++;
        }
 
        cout << "#" << test_case << endl;
        for (i = 0; i < 10; i++) {
            for (int rep = 0; rep < count[i]; rep++) {
                cout << code[i] << " ";
            }
        }
 
        cout << endl;
    }
    return 0;
}