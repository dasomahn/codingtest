#include<iostream>
#include<cmath>
 
using namespace std;
 
const int N = 18;
int prime[] = { 2, 3, 5, 7, 11, 13, 17 };
int c[19][10];
int digit = pow(10, 6);
 
int comb(int n, int r) {
    if (r > n/2) {
        r = n - r;
    }
 
    if (r == 0) return 1;
 
    if (c[n][r])
        return c[n][r];
    else {
        return comb(n - 1, r - 1) + comb(n - 1, r);
    }
}
 
int main(int argc, char** argv) {
    int test_case;
    int T;
    cin >> T;
    cout.precision(7);
 
    float a, b;
    double prime_a, prime_b;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> a >> b;
        a *= 0.01;
        b *= 0.01;
 
        prime_a = prime_b = 0;
 
        for (int i = 0; i < 7; i++) {
            int pr = prime[i];
            prime_a += comb(N, pr) * pow(a, pr) * pow(1 - a, N - pr);
            prime_b += comb(N, pr) * pow(b, pr) * pow(1 - b, N - pr);
        }
 
        printf("#%d %.6lf\n", test_case, 1-round((1-prime_a)*(1-prime_b)*digit)/digit);
    }
    return 0;
}