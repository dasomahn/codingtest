#include <string>
#include <vector>
#include <unordered_map>
#define MAXL    (10)
using namespace std;
 
struct Word {
    int num, cnt, subject;
    string s;   
 
}wordArr[10001];
 
struct User {
    int alive, score, Best;
    int cnt[10001];
    vector<int> cards;    
    vector<int> cardInfo[22][27 * 27];
 
}userArr[51];
 
int playerCnt, tid;
unordered_map<string, int> getSubject;
 
void init(int N, char mWordList[][MAXL + 1], char mSubjectList[][MAXL + 1])
{
    tid = 1;
    getSubject.clear();
    for (int i = 0; i < N; i++) {
        int t = getSubject[mSubjectList[i]];
        if (!t) t = getSubject[mSubjectList[i]] = tid++;
        wordArr[i + 1] = { i + 1, 0, t, mWordList[i] };
    }
    return;
}
 
void join(int mID, int M, int mCardList[])
{
    playerCnt = mID;
 
    // 초기화
    User* user = &userArr[mID];
    user->alive = 1;
    user->score = 0;
    user->Best = 0;
    user->cards.clear();
 
    for (int i = 1; i <= tid; i++)
        for (int j = 0; j < 729; j++)
            user->cardInfo[i][j].clear();
    // 초기화 끝
 
    for (int i = 0; i < M; i++) {
        if (!userArr[mID].cnt[mCardList[i]]++) {
            int cid = mCardList[i];
            Word * cur = &wordArr[cid];
            wordArr[cid].cnt++;
 
            user->cards.push_back(cid);
            user->cardInfo[cur->subject][cur->s[0] - 'a' + 1].push_back(cid);
            user->cardInfo[cur->subject][(cur->s[0] - 'a' + 1) * 27 + (cur->s[1] - 'a' + 1)].push_back(cid);
        }
    }
    return;
}
 
int playRound(char mBeginStr[], char mSubject[])
{
    int visit[10001] = {};
    int temp = getSubject[mSubject];
    int pre = mBeginStr[0] - 'a' + 1;
    pre = ('a' <= mBeginStr[1] && mBeginStr[1] <= 'z') ? pre * 27 + mBeginStr[1] - 'a' + 1 : pre;
    int result = 0;
 
    vector<pair<int, int>> played;
 
    for (int i = 1; i <= playerCnt; i++) {
        if (userArr[i].alive) {
            int Best = 0;
            for (auto j : userArr[i].cardInfo[temp][pre]) {
                if (!userArr[i].cnt[j]) continue; // 이미 사용함
                if (wordArr[Best].cnt < wordArr[j].cnt ||
                    (wordArr[Best].cnt == wordArr[j].cnt && wordArr[Best].s > wordArr[j].s)) {
                    Best = j;
                }
            }
            if (Best) {
                result += Best;
                played.emplace_back(i, Best);
                visit[Best]++;
            }
        }
    }
 
    for (auto i : played) {
        userArr[i.first].score += (visit[i.second] - 1) * (visit[i.second] - 1);
        if (--userArr[i.first].cnt[i.second] == 0) --wordArr[i.second].cnt;
    }
    return result;
}
 
int leave(int mID)
{
    userArr[mID].alive = 0;
    for (auto id : userArr[mID].cards)
        if (userArr[mID].cnt[id]) userArr[mID].cnt[id] = 0, --wordArr[id].cnt;
 
    return userArr[mID].score;
}