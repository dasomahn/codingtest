#include <stdio.h>
#include <queue>
 
#define MAX_N 50000
 
using namespace std;
 
vector<int> map[MAX_N];
int indegree[MAX_N] = {0, };
int test_case, n, m;
 
void reset()
{
    int i;
    for (i = 0; i < n; i++) 
    {
        map[i].clear();
    }
    for (i = 0; i < n; i++) 
    {
        indegree[i] = 0;
    }
}
 
int main(void) 
{
    int dest, tc, i;
    queue<int> queue;
 
    scanf("%d", &test_case);
 
    for (tc = 1; tc <= test_case; tc++) 
    {
        scanf("%d %d", &n, &m);
        reset();
 
        for (i = 0; i < m; i++) 
        {
            int src, dest;
            scanf("%d %d", &src, &dest);
            map[src - 1].push_back(dest - 1);
            indegree[dest - 1]++;
        }
 
        for (i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                queue.push(i);
            }
        }
 
        printf("#%d  ", tc);
        while (!queue.empty())
        {
            int src = queue.front();
            queue.pop();
            printf("%d ", src + 1);
 
            for (int d : map[src])
            {
                indegree[d]--;
                if (indegree[d] == 0)
                {
                    queue.push(d);
                }
            }
        }
        printf("\n");
    }
 
    return 0;
}