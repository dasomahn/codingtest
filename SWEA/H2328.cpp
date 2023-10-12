#include <iostream>
#include <algorithm>
#include <vector>
 
#define PERF_M 1000001
#define PRICE_M 100000
 
using namespace std;
 
vector<pair<int, int>> parts[2][3]; // 위치, 타입
int charge;
 
struct Result
{
    int mPrice;
    int mPerformance;
};
 
void init(int mCharge)
{
    parts[0][0].clear();
    parts[0][1].clear();
    parts[0][2].clear();
    parts[1][0].clear();
    parts[1][1].clear();
    parts[1][2].clear();
 
    charge = mCharge;
}
 
int stock(int mType, int mPrice, int mPerformance, int mPosition)
{
    parts[mPosition][mType].emplace_back(mPrice, mPerformance);
    return parts[mPosition][mType].size();
}
 
int get_min(int val) {
    int mins[2][3];
 
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            mins[i][j] = PRICE_M + 49427;
 
            for (auto a : parts[i][j]) {
                if (a.second >= val && mins[i][j] > a.first) {
                    mins[i][j] = a.first;
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