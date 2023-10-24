#include <iostream>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;
 
int N;
 
pair<int, string> waitlist[2001];
 
//unordered_map<string, unordered_set<int>> typos;
map<pair<string, string>, unordered_set<int>> typos;
unordered_map<string, int> dict_idx;
string dict[9000][5];
int dict_size[9000];
int dict_cnt;
 
void init(int n) {
    N = n;
    //memset(waitlist, 0, sizeof(waitlist));
    for (int i = 0; i < n; i++) {
        waitlist[i] = { 0, "" };
    }
 
    memset(dict_size, 0, sizeof(dict_size));
 
    dict_cnt = 0;
    typos.clear();
    dict_idx.clear();
}
 
bool isTypo(string a, string b) {
    int a_size = a.size();
    int b_size = b.size();
    int s = a.size() - b.size();
 
    int wrong = 0;
    int a_idx = 0, b_idx = 0;
 
    if (abs(s) <= 1) {
        while ((wrong <= 1) & (a_idx < a_size) & (b_idx < b_size)) {
            if (a[a_idx] != b[b_idx]) {
                wrong++;
                if (a_size < b_size) {
                    a_idx--;
                }
                else if (a_size > b_size) {
                    b_idx--;
                }
            }
            a_idx++;
            b_idx++;
        }
    }
    else {
        return false;
    }
 
    if (wrong == 1) return true;
    if ((wrong == 0) & (s != 0)) return true;
    else return false;
}
 
int search(int mId, int searchTime, char searchWord_c[11], char correctWord[5][11]) {
    if ((waitlist[mId].first) && (searchTime - waitlist[mId].first > 10)) {
        waitlist[mId].first = 0;
    }
 
    int ret = 0;
    int idx;
 
    string searchWord = string(searchWord_c);
    if (dict_idx.find(searchWord) != dict_idx.end()) {
        idx = dict_idx[searchWord];
        for (ret = 0; ret < dict_size[idx]; ret++) {
            strcpy(correctWord[ret], dict[idx][ret].c_str());
        }
    }
 
    if (waitlist[mId].first == 0) {
        // 초기값
        waitlist[mId] = { searchTime, searchWord };
    } else {
 
        string typo = waitlist[mId].second;
        pair<string, string> pi = { typo, searchWord };
        if (strcmp(typo.c_str(), searchWord_c) == 0);
        else if (isTypo(typo.c_str(), searchWord_c)) {
 
            typos[pi].insert(mId);
 
            if (typos[pi].size() == 3) {
                if (dict_idx.find(typo) == dict_idx.end()) {
                    dict_idx[typo] = dict_cnt++;
                }
 
                idx = dict_idx[typo];
                bool exist = false;
                for (int i = 0; i < dict_size[idx]; i++) {
                    if (strcmp(searchWord_c, dict[idx][i].c_str()) == 0) {
                        exist = true;
                        break;
                    }
                }
                if (!exist) {
                    dict[idx][dict_size[idx]] = searchWord;
                    ++dict_size[idx];
                }
            }
 
        }
        waitlist[mId].first = 0;
    }
 
    return ret;
}