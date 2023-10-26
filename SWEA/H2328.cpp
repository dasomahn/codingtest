#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
 
#define PERF_M 1000001
#define PRICE_M 100000
 
using namespace std;
 
struct Part {
    int price;
    int perf;
};
 
Part parts[2][3][4000]; // 위치, 타입
int partCnt[2][3];
int charge;
 
struct Result
{
    int mPrice;
    int mPerformance;
};
 
void init(int mCharge)
{
    memset(partCnt, 0, sizeof(partCnt));
    charge = mCharge;
}
 
int stock(int mType, int mPrice, int mPerformance, int mPosition)
{
    parts[mPosition][mType][partCnt[mPosition][mType]++] = { mPrice, mPerformance };
    return partCnt[mPosition][mType];
}
 
int get_min(int val) {
    int mins[2][3];
 
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            mins[i][j] = PRICE_M + 49427;
 
            for (int idx = 0; idx < partCnt[i][j]; idx++) {
                if (parts[i][j][idx].perf >= val && mins[i][j] > parts[i][j][idx].price) {
                    mins[i][j] = parts[i][j][idx].price;
                }
            }
        }
    }
 
    int same, cross;
    same = min(
        mins[0][0] + mins[0][1] + mins[0][2], // 창고 0에서
        mins[1][0] + mins[1][1] + mins[1][2]  // 창고 1에서
    );
 
    cross = min(mins[0][0], mins[1][0])
        + min(mins[0][1], mins[1][1])
        + min(mins[0][2], mins[1][2])
        + charge;
 
    return min(same, cross);
}
 
Result order(int mBudget)
{
    Result res = { 0, 0 };
 
    int left = 1;
    int right = PERF_M;
    int mid;
    int price, save_price;
 
    while (left + 1 < right) {
        mid = (left + right) >> 1;
 
        price = get_min(mid);
         
        if (price > mBudget) right = mid;
        else {
            save_price = price;
            left = mid;
        }
    }
 
    if (left != 1) {
        res = { save_price, left };
    }
 
    return res;
}