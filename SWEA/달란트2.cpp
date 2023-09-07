#include<iostream>
#include<cmath>
 
using namespace std;
 
int main(int argc, char** argv) {
    int test_case;
    int T;
    cin >> T;
    cout.precision(16);
 
    int n, p, ans;
    int div, rem;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> n >> p;
 
        div = n / p;
        rem = n - div * (p - 1) - div;
 
        cout << "#" << test_case << " " << pow(div, p-rem)*pow(div+1, rem) << endl;
    }
    return 0;
}