#include <iostream>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <cstring>
#include <string>
using namespace std;
 
int N;
 
pair<int, string> waitlist[2001];
 
//unordered_map<string, unordered_set<int>> typos;
map<pair<string, string>, unordered_set<int>> typos;
unordered_map<string, unordered_set<string>> dict;
 
void init(int n) {
    N = n;
 
    memset(waitlist, 0, sizeof(waitlist));
 
    typos.clear();
    dict.clear();
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
    string searchWord = string(searchWord_c);
    int i = 0;
 
    // 과거 검색 기록 O
    if  ((waitlist[mId].first != 0) & (searchTime - waitlist[mId].first <= 10)) {
        // 오타검사
        string typo = waitlist[mId].second;
         
        if (isTypo(waitlist[mId].second, searchWord)) {
            pair<string, string> pi = { typo, searchWord };
            if (typos.find(pi) == typos.end()) {
                unordered_set<int> set;
                typos[pi] = set;
            }
            typos[pi].emplace(mId);
 
            if (typos[pi].size() == 3) {
                if (dict.find(typo) == dict.end()) {
                    unordered_set<string> s;
                    s.emplace(searchWord);
                    dict[typo] = s;
                }
                else {
                    // 여러 정답
                    dict[typo].emplace(searchWord);
                }
            }
        }
        // 오타검사 끝
    }
    else { //if ((waitlist[mId].first == 0) | (searchTime - waitlist[mId].first > 10)) {
        waitlist[mId] = { searchTime, searchWord };
    }
    if (dict.find(searchWord) != dict.end()) {
        for (string s : dict[searchWord]) {
            strcpy(correctWord[i], s.c_str());
            i++;
        }
    }
    return i;
}