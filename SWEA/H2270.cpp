#include <algorithm>
#define MAX 100000000
#define BUCKET_MAX 200000
#define SIZE 400
#define BUCKET BUCKET_MAX/SIZE
 
using namespace std;
 
struct bucket {
    int cnt;
    int max;
    int min;
    int arr[SIZE];
 
    void init() {
        cnt = 0;
        max = 0;
        min = MAX;
    }
 
} buckets[BUCKET];
 
bucket* Bucket[BUCKET];
 
int bucket_cnt;
 
void add_bucket(bucket* b, int n, int* value) {
    int i;
    int cnt = b->cnt;
     
    for (i=0; i<n; i++) {
        b->arr[cnt + i] = value[i];
        b->max = max(b->max, value[i]);
        b->min = min(b->min, value[i]);
    }
    b->cnt = cnt + i;
}
 
void new_bucket(int n, int* value) { // n은 버킷 size(400)이하임이 보장되어야 함
 
    bucket* b = &buckets[bucket_cnt];
    Bucket[bucket_cnt] = b;
    b->init();
 
    add_bucket(b, n, value);
}
 
void init(int N, int mValue[])
{
    bucket_cnt = 0;
 
    while (N > 0) {
        if (N <= SIZE) {
            new_bucket(N, mValue);
            break;
        }
        new_bucket(SIZE, mValue);
        bucket_cnt++;
 
        mValue += SIZE;
        N -= SIZE;
    }
}
 
void add(int M, int mValue[]) // M은 100 이하
{
    bucket* b = Bucket[bucket_cnt];
    if (b->cnt + M > SIZE) {
        int space = SIZE - b->cnt;
 
        if (space != 0) {
            add_bucket(b, space, mValue);
            mValue += space;
        }
        bucket_cnt++;
        new_bucket(M - space, mValue);
 
    }
    else {
        add_bucket(b, M, mValue);
    }
}
void erase(int mFrom, int mTo)
{
    int move_i = (mFrom - 1) / SIZE;
    int move_idx = (mFrom - 1) % SIZE;
    int move = bucket_cnt * SIZE + Bucket[bucket_cnt]->cnt - mTo;
 
    int ori_i = mTo / SIZE;
    int ori_idx = mTo % SIZE;
 
    int temp_max = 0;
    int temp_min = MAX;
 
    if (move_idx < SIZE) {
        for (int i = 0; i < move_idx; i++) {
            temp_max = max(temp_max, Bucket[move_i]->arr[i]);
            temp_min = min(temp_min, Bucket[move_i]->arr[i]);
        }
        Bucket[move_i]->max = temp_max;
        Bucket[move_i]->min = temp_min;
    }
 
    // 땡겨오기
    while (move > 0) {
        Bucket[move_i]->max = max(Bucket[move_i]->max, Bucket[ori_i]->arr[ori_idx]);
        Bucket[move_i]->min = min(Bucket[move_i]->min, Bucket[ori_i]->arr[ori_idx]);
 
        Bucket[move_i]->arr[move_idx++] = Bucket[ori_i]->arr[ori_idx++];
 
        if (move_idx == SIZE) {
            move_i++;
            move_idx = 0;
            Bucket[move_i]->max = 0; //////////////////////////////
            Bucket[move_i]->min = MAX; //////////////////////////////
        }
        if (ori_idx == SIZE) {
            ori_i++;
            ori_idx = 0;
        }
        move--;
    }
 
    if (move_idx == 0) {
        bucket_cnt = move_i - 1;
        Bucket[bucket_cnt]->cnt = SIZE;
    }
    else {
        bucket_cnt = move_i;
        Bucket[bucket_cnt]->cnt = move_idx;
    }
}
int find(int K)
{
    int i = bucket_cnt;
 
    int temp_max = 0;
    int temp_min = MAX;
 
    while (K > 0) {
        bucket* cur = Bucket[i];
        int temp_cnt = cur->cnt;
        if (K >= temp_cnt) {
            temp_max = max(temp_max, cur->max);
            temp_min = min(temp_min, cur->min);
        }
        else { // K가 버킷 안에서 짤릴 때
            while (K-- > 0)
            {
                temp_cnt--;
                temp_max = max(temp_max, cur->arr[temp_cnt]);
                temp_min = min(temp_min, cur->arr[temp_cnt]);
            }
        }
         
        K -= temp_cnt;
        i--;
    }
 
    return temp_max - temp_min;
}