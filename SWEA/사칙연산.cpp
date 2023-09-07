#include <iostream>
#include <cstring>
#include <cstdlib>
 
using namespace std;
 
int N;
int Number[1001], Firstchild[1001], Secondchild[1001];
char Operator[1001];
 
double calc(int v) {
    double l, r;
 
    if (!Operator[v]) {
        return Number[v];
    }
 
    l = calc(Firstchild[v]);
    r = calc(Secondchild[v]);
 
    if (Operator[v] == '+') return l + r;
    if (Operator[v] == '-') return l - r;
    if (Operator[v] == '*') return l * r;
    if (Operator[v] == '/') return l / r;
}
 
int main(int argc, char** argv)
{
    int test_case;
 
    for (test_case = 1; test_case <= 10; ++test_case)
    {
        int i;
        memset(Firstchild, 0, sizeof(int) * 1001);
        memset(Secondchild, 0, sizeof(int) * 1001);
        memset(Operator, 0, sizeof(char) * 1001);
 
        cin >> N;
        for (i = 0; i < N; i++)
        {
            int addr;
            char buf[100];
 
            cin >> addr;
            cin >> buf;
 
            if ((buf[0] == '+') || (buf[0] == '-') || (buf[0] == '*') || (buf[0] == '/'))
            {
                Operator[addr] = buf[0];
                cin >> Firstchild[addr] >> Secondchild[addr];
            }
            else Number[addr] = atoi(buf);
        }
 
        cout << "#" << test_case << " " << calc(1) << endl;;
    }
 
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}