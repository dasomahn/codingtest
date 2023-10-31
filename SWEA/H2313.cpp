#include <iostream>
#include <cmath>
#include <cstring>
#include <unordered_map>
 
#define MAXL    (11)    
#define MAX 50000
 
using namespace std;
 
struct Species {
    char name[MAXL];
    int depth;
    int idx;
 
    Species* parent[12];
    Species* child[400];
    int childCnt;
    int dist[5];
 
} AllSpecies[MAX];
int speciesCnt;
unordered_map<string, Species*> getSpecies;
 
int gc;
Species* queue[50000];
int dist[50000];
 
Species* newSpecies(char* name, Species* parent) {
    Species* species = &AllSpecies[speciesCnt++];
    strcpy(species->name, name);
    species->childCnt = 0;
    species->idx = speciesCnt - 1;
    species->parent[0] = parent;
     
    memset(species->dist, 0, sizeof(species->dist));
    species->dist[0] = 1;
 
    getSpecies[name] = species;
 
    if (parent) {
        species->depth = parent->depth + 1;
        parent->child[parent->childCnt++] = species;
    }
    return species;
}
 
void saveParent(Species* species)
{
    int h = log2(species->depth);
 
    for (int i = 1; i <= h; i++) {
        species->parent[i] = species->parent[i - 1]->parent[i - 1];
    }
 
    species = species->parent[0];
    for (int d = 1; d < 5; d++) {
        if (!species) break;
        species->dist[d]++;
        species = species->parent[0];
    }
}
 
void init(char mRootSpecies[MAXL])
{
    speciesCnt = 0;
    newSpecies(mRootSpecies, nullptr);
}
 
void add(char mSpecies[MAXL], char mParentSpecies[MAXL])
{
    Species* parent = getSpecies[mParentSpecies];
    Species* species = newSpecies(mSpecies, parent);
    saveParent(species);
}
 
int getDistance(char mSpecies1[MAXL], char mSpecies2[MAXL])
{
    Species* sp1 = getSpecies[mSpecies1];
    Species* sp2 = getSpecies[mSpecies2];
 
    if (sp1->depth < sp2->depth) swap(sp1, sp2);
 
    // 껑충 LCA
    int dist = sp1->depth - sp2->depth;
 
    while (dist) {
        int l = log2(dist);
        sp1 = sp1->parent[l];
        dist = sp1->depth - sp2->depth;
    }
 
    if (sp1 == sp2) {
        return getSpecies[mSpecies1]->depth + getSpecies[mSpecies2]->depth - sp1->depth * 2;
    }
 
    while (sp1->parent[0] != sp2->parent[0]) {
        dist = log2(sp1->depth);
        for (int i = dist; i >= 0; i--) {
            if (sp1->parent[i] != sp2->parent[i]) {
                sp1 = sp1->parent[i];
                sp2 = sp2->parent[i];
                break;
            }
        }
    }
 
    return getSpecies[mSpecies1]->depth + getSpecies[mSpecies2]->depth - sp1->parent[0]->depth * 2;
}
 
int getCount(char mSpecies[MAXL], int mDistance)
{
    Species* species = getSpecies[mSpecies];
    int cnt = species->dist[mDistance];
 
    for (int dist = 1; dist <= mDistance; dist++) {
        if (!species->parent[0]) break;
         
        if (mDistance == dist) {
            cnt++;
            break;
        }
         
        cnt += species->parent[0]->dist[mDistance - dist];
        cnt -= species->dist[mDistance - dist - 1];
        species = species->parent[0];
    }
 
    return cnt;
}