#include <iostream>
 
#include <vector>
#include <set>
 
using namespace std;
 
typedef pair<int, int> pi;
 
struct cmp {
    bool operator()(pi a, pi b) const {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second > b.second;
    }
};
 
set<pi, cmp> trees[4000];
int n, l, l_size;
 
void init(int N, int L, int mAbility[])
{
    n = N;
    l = L;
    l_size = N / L;
 
    for (int i = 0; i < L; i++) {
        trees[i].clear();
        for (int j = 0; j < l_size; j++) {
            trees[i].emplace(i*l_size + j, mAbility[i*l_size + j]);
        }
    }
}
 
int change(int mid) {
    int ids = 0;
 
    set<pi, cmp>::iterator cur_last_iter, cur_first_iter;
    pi prev_last;
 
    // TODO 첫번째
    cur_last_iter = prev(trees[0].end());
    for (int i = 0; i < mid; i++) {
        cur_last_iter--;
    }
    pi cur_last = *cur_last_iter;
 
    trees[0].erase(cur_last_iter); // 내꺼 마지막 지웠어
    ids += cur_last.first;
    prev_last = cur_last;
 
    for (int i = 1; i < l - 1; i++) {
        // i-1번째의 마지막 vs i번째의 첫번째
        cur_first_iter = trees[i].begin();
        pi cur_first = *cur_first_iter;
        trees[i].erase(cur_first_iter); // 내 첫째 지우기
        trees[i - 1].emplace(cur_first); // 앞 리그에 내 첫째 넣기
         
 
        cur_last_iter = prev(trees[i].end());
        for (int i = 0; i < mid; i++) {
            cur_last_iter--;
        }
        pi cur_last = *cur_last_iter;
        trees[i].erase(cur_last_iter); // 내꺼 마지막 지웠어
         
        trees[i].emplace(prev_last); // 앞 리그 마지막 내꺼에 넣기
     
        prev_last = cur_last;
 
        ids += cur_first.first + cur_last.first;
    }
 
    // TODO 마지막
    cur_first_iter = trees[l - 1].begin();
    pi cur_first = *cur_first_iter;
    trees[l - 1].erase(cur_first_iter); // 내 첫째 지우기
 
    trees[l - 2].emplace(cur_first); // 앞 리그에 내 첫째 넣기
     
    trees[l - 1].emplace(prev_last); // 앞 리그 마지막 내꺼에 넣기
    ids += cur_first.first;
 
    return ids;
}
 
int move()
{   
    return change(0);
}
 
int trade()
{
    int mid = l_size / 2;
     
    return change(mid);
}