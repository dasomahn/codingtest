#include <iostream>
#include <cstring>
#include <cstdlib>
 
using namespace std;
 
int N;
int Firstchild[101], Secondchild[101];
char Alpha[101];
 
void print(int idx) {
    if (Firstchild[idx]) {
        print(Firstchild[idx]);
    }
    cout << Alpha[idx];
    if (Secondchild[idx]) {
        print(Secondchild[idx]);
    }
}
 
int main(int argc, char** argv)
{
    int test_case;
     
    /*
       10개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for(test_case = 1; test_case <= 10; ++test_case)
    {
        int i;
        memset(Firstchild, 0, sizeof(int) * 101);
        memset(Secondchild, 0, sizeof(int) * 101);
        memset(Alpha, 0, sizeof(char) * 101);
         
        cin >> N;
        for(i = 0; i < N; i++)
        {
            int addr;
            char buf[100];
 
            cin >> addr;
            cin >> buf;
             
            Alpha[addr] = buf[0];
             
            if(addr*2 <= N)
            {
                cin >> Firstchild[addr];
                if(addr*2 + 1 <= N)
                    scanf("%d ",&Secondchild[addr]);
            }
        }
 
        cout << "#" << test_case << " ";
        print(1);
        cout << "\n";
 
    }
 
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}