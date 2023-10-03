#include <algorithm>
 
extern int CalcFinalSpeed(int N, int *a, int *b, int *p);
 
using namespace std;
 
int p[200000];
int *A, *B;

bool cmp(int i, int j) {
    return (double)(A[i]-1) / B[i] > (double)(A[j]-1) / B[j];
}
 
int MinRailSpeed(int n, int *a, int *b) {
    A = a, B = b;
 
    for (int i = 0; i < n; i++) p[i] = i;
 
    sort(p, p+n, cmp);
 
    return CalcFinalSpeed(n, a, b, p);
}