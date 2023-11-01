#include <iostream>
 
using namespace std;
 
#define MAX 1000000
 
#define Min(A, B)   (A) < (B) ? (A) : (B)
#define Max(A, B)   (A) > (B) ? (A) : (B)
 
struct Node  {
    int start, end;
    int max, min;
    int lazy;
    Node* leftTree;
    Node* rightTree;
};
 
Node segTree[MAX * 4];
 
long long total;
int c, nodeCnt, erased;
 
void updateSeg(Node* node, int left, int right, int val) {
    if (left > node->end || right < node->start) return;
 
    if (left <= node->start && node->end <= right) {
        node->lazy += val;
        return;
    }
 
    int mid = (node->start + node->end) >> 1;
    if (node->leftTree == 0) {
        segTree[nodeCnt] = { node->start, mid, 0, node->min, node->max, 0, 0 };
        node->leftTree = &segTree[nodeCnt++];
 
        segTree[nodeCnt] = { mid + 1, node->end, 0, node->min, node->max, 0, 0 };
        node->rightTree = &segTree[nodeCnt++];
    }
 
    if (node->lazy != 0) {
        node->rightTree->lazy += node->lazy;
        node->leftTree->lazy += node->lazy;
        node->lazy = 0;
    }
 
    updateSeg(node->leftTree, left, right, val);
    updateSeg(node->rightTree, left, right, val);
 
    node->max = Max(node->leftTree->max + node->leftTree->lazy,
                    node->rightTree->max + node->rightTree->lazy);
    node->min = Min(node->leftTree->min + node->leftTree->lazy,
                    node->rightTree->min + node->rightTree->lazy);
}
struct Result {
    int top;
    int count;
};
 
void init(int C)
{
    total = 0;
    c = C;
    erased = 0;
     
    segTree[0] = { 0, C - 1, 0, 0, 0, 0, 0 };
    nodeCnt = 1;
}
 
Result dropBlocks(int mCol, int mHeight, int mLength)
{
    total += mLength * mHeight;
    updateSeg(&segTree[0], mCol, mCol + mLength - 1, mHeight);
 
    int maximum = segTree[0].max + segTree[0].lazy;
    int minimum = segTree[0].min + segTree[0].lazy;
 
    total -= (minimum - erased) * c;
    erased = minimum;
 
    return { maximum - minimum, total % 1000000 };
}