#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stack>
 
using namespace std;
 
int N;
int Firstchild[201], Secondchild[201];
char Oper[201];
stack<char> st;
int answer;
 
int check(char a) {
    if ('0' <= a && a <= '9')
        return 1;
    return 0;
}
 
void read(int v) {
    if (answer) {
        if (Firstchild[v]) {
            read(Firstchild[v]);
        }
 
        // 검증 후 push
        char temp = st.top();
        if (check(temp) ^ check(Oper[v])) {
            st.push(Oper[v]);
        }
        else {
            answer = 0;
        }
 
        if (Secondchild[v]) {
            read(Secondchild[v]);
        }
    }
}
 
int main(int argc, char** argv)
{
    int test_case;
 
    for (test_case = 1; test_case <= 10; ++test_case)
    {
        int i;
        memset(Firstchild, 0, sizeof(int) * 201);
        memset(Secondchild, 0, sizeof(int) * 201);
        memset(Oper, 0, sizeof(char) * 201);
 
        cin >> N;
        for (i = 0; i < N; i++)
        {
            int addr;
            char buf[200];
 
            cin >> addr;
            cin >> buf;
 
            Oper[addr] = buf[0];
 
            if (addr * 2 <= N)
            {
                cin >> Firstchild[addr];
                if (addr * 2 + 1 <= N)
                    cin >> Secondchild[addr];
            }
        }
 
        answer = 1;
        st.push('+');
        read(1);
 
        // 배열 비우기
        while (!st.empty()) {
            st.pop();
        }
 
        cout << "#" << test_case << " " << answer << endl;
    }
 
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}