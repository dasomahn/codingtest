#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
 
#define ORDER 30000
#define SOLD 30000
#define PROD 600
 
using namespace std;
 
struct Order {
    int id;
    int pid;
    int price;
    int ori;
    int cur;
 
    void init(int _id, int _pid, int _price, int quantity) {
        id = _id;
        pid = _pid;
        price = _price;
        ori = cur = quantity;
    }
 
} Orders[ORDER];
int order_cnt;
 
unordered_map<int, Order*> getByBid;
 
struct cmp {
    bool operator()(Order* a, Order* b) const {
        if (a->price == b->price) {
            return a->id < b->id;
        }
        return a->price < b->price;
    }
};
 
struct Product {
    int pid;
    int sum;
 
    set<Order*, cmp> stock;
 
    void clear(int _pid) {
        pid = _pid;
        sum = 0;
        stock.clear();
    }
 
} Products[PROD];
int prod_cnt;
 
unordered_map<int, Product*> getByPid;
 
struct SoldInfo {
    int bid;
    int cnt;
};
 
struct Sold {
    int sid;
    int pid;
    vector<SoldInfo> sold;
 
} Solds[SOLD];
int sold_cnt;
 
unordered_map<int, Sold*> getBySid;
 
void init() {
    order_cnt = 0;
    getByBid.clear();
 
    prod_cnt = 0;
    getByPid.clear();
 
    sold_cnt = 0;
    getBySid.clear();
 
    return;
}
 
int buy(int bId, int mProduct, int mPrice, int mQuantity) {
    Order* order = &Orders[order_cnt++];
    order->init(bId, mProduct, mPrice, mQuantity);
    getByBid[bId] = order;
 
    if (getByPid.find(mProduct) == getByPid.end()) {
        Product* prod = &Products[prod_cnt++];
        prod->clear(mProduct);
        getByPid[mProduct] = prod;
    }
    getByPid[mProduct]->stock.emplace(order);
    getByPid[mProduct]->sum += mQuantity;
 
    return getByPid[mProduct]->sum;
}
 
int cancel(int bId) {
    if (getByBid.find(bId) == getByBid.end()) return -1;
    Order* order = getByBid[bId];
 
    if (order->ori != order->cur) return -1;
     
    order->id = 0;
    getByPid[order->pid]->sum -= order->ori;
 
    getByBid.erase(bId);
 
    return getByPid[order->pid]->sum;
}
 
int sell(int sId, int mProduct, int mPrice, int mQuantity) {
    Product* prod = getByPid[mProduct];
 
    if (prod->sum < mQuantity) return -1;
 
    Sold* sold = &Solds[sold_cnt++];
    sold->sold.clear();
    getBySid[sId] = sold;
    sold->sid = sId;
    sold->pid = mProduct;
     
    int profit = 0;
    int temp;
 
    auto iter = prod->stock.begin();
    while (mQuantity) {
        Order* order = *iter;
        if (!order->id) { // 취소된거면
            iter = prod->stock.erase(iter);
            continue;
        }
 
        if (order->cur <= mQuantity) {
            temp = order->cur;
             
            iter = prod->stock.erase(iter);
        }
        else {
            temp = mQuantity;
        }
        SoldInfo info = { order->id, temp };
        sold->sold.emplace_back(info);
        profit += (mPrice - order->price) * temp;
        mQuantity -= temp;
        prod->sum -= temp;
        order->cur -= temp;
    }
 
    return profit;
}
 
int refund(int sId) {
    if (getBySid.find(sId) == getBySid.end()) return -1;
    Sold* sold = getBySid[sId];
 
    int cnt = 0;
    for (auto a : sold->sold) {
        cnt += a.cnt;
        getByBid[a.bid]->cur += a.cnt;
        getByPid[sold->pid]->sum += a.cnt;
 
        if (getByPid[sold->pid]->stock.find(getByBid[a.bid]) == getByPid[sold->pid]->stock.end()) {
            getByPid[getByBid[a.bid]->pid]->stock.emplace(getByBid[a.bid]);
        }
    }
 
    getBySid.erase(sId);
 
    return cnt;
}