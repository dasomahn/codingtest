#include<iostream>
 
#define M 10
#define ll long long
 
using namespace std;
 
int rem[M];
int num[M];
int N;
 
int inverse(int n, int b) {
    int r1 = n;
    int r2 = b;
 
    int t1 = 0;
    int t2 = 1;
 
    int q, r, t;
 
    while (r2) {
        q = r1 / r2;
        r = r1 % r2;
 
        r1 = r2;
        r2 = r;
 
        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }
 
    if (r1 != 1) return 0;
    if (t1 < 0) t1 += n;
     
    return t1;
}
 
int CRT() {
    ll product = 1;
    for (int i = 0; i < N; i++) {
        product *= num[i];
    }
 
    ll res = 0;
    for (int i = 0; i < N; i++) {
        ll partialProduct = product / num[i];
        res += rem[i] * inverse(num[i], partialProduct) * partialProduct;
    }
 
    return res % product;
}
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
     
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
         
        for (int i = 0; i < N; i++) {
            cin >> rem[i];
            cin >> num[i];
        }
 
        cout << "#" << test_case << " " << CRT() << "\n";
 
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}