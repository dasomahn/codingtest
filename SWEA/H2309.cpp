#define MAX_SPOT 100000
 
struct road {
    int type;
    int time;
 
    road(int _type=0, int _time=0) : time(_time), type(_type){}
};
 
int n, m;
road arr[MAX_SPOT];
int seg[MAX_SPOT * 4];
 
int makeSeg(int idx, int s, int e) {
    if (s == e) {
        return seg[idx] = arr[s].time;
    }
    int m = (s + e) >> 1;
    return seg[idx] = makeSeg(idx * 2, s, m) + makeSeg(idx * 2 + 1, m + 1, e);
}
 
int querySeg(int idx, int s, int e, int l, int r) {
    if (l <= s && e <= r) {
        return seg[idx];
    }
    if (r < s || e < l) {
        return 0;
    }
 
    int m = (s + e) >> 1;
 
    return querySeg(idx * 2, s, m, l, r) +
            querySeg(idx * 2 + 1, m + 1, e, l, r);
}
 
void updateSeg(int idx, int s, int e, int who, int how) {
    if (who < s || e < who) {
        return ;
    }
 
    if (s == e) {
        arr[who].time += how;
        seg[idx] += how;
        return ;
    }
 
    seg[idx] += how;
    int m = (s + e) >> 1;
 
    updateSeg(idx * 2, s, m, who, how);
    updateSeg(idx * 2 + 1, m + 1, e, who, how);
 
}
 
void init(int N, int M, int mType[], int mTime[])
{
    n = N-1;
    m = M;
 
    for (int i = 0; i < n; i++) {
        arr[i] = road(mType[i], mTime[i]);
    }
 
    makeSeg(1, 0, n - 1);
}
 
void destroy()
{
 
}
 
void update(int mID, int mNewTime)
{
    updateSeg(1, 0, n - 1, mID, mNewTime - arr[mID].time);
}
 
int updateByType(int mTypeID, int mRatio256)
{
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].type == mTypeID) {
            int update = arr[i].time * mRatio256 / 256;
            updateSeg(1, 0, n - 1, i, update - arr[i].time);
            sum += update;
        }
    }
 
    return sum;
}
 
int calculate(int mA, int mB)
{
    if (mA > mB) {
        return querySeg(1, 0, n - 1, mB, mA - 1);
    }
    return querySeg(1, 0, n-1, mA, mB-1);
}