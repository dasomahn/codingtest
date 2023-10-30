#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
 
#define MAX 500
 
using namespace std;
 
struct News {
    int nid;
    int time;
    int status; // 1 전송 대기 0 전송 완료 -1 삭제
    int cid;
 
} NewsNews[30000];
int newsCnt;
unordered_map<int, News*> getNews;
 
struct cmp {
    bool operator() (News* a, News* b) const {
        if (a->time == b->time) {
            return a->nid < b->nid;
        }
        return a->time < b->time;
    }
};
 
struct User {
    int uid;
    News* news[30000];
    int newsCnt;
 
} Users[MAX];
int userCnt;
unordered_map<int, User*> getUser;
 
struct Channel {
    int cid;
    User* uids[MAX];
    int uidCnt;
 
} Channels[MAX];
int channelCnt;
unordered_map<int, Channel*> getChannel;
 
struct cmppq {
    bool operator() (News* a, News* b) {
        return a->time > b->time;
    }
};
 
priority_queue<News*, vector<News*>, cmppq> pq;
 
void init(int N, int K)
{
    newsCnt = userCnt = channelCnt = 0;
    getNews.clear();
    getUser.clear();
    getChannel.clear();
 
    while (!pq.empty()) {
        pq.pop();
    }
 
    //pq = {};
}
 
void sendNews(int time) {
    while (!pq.empty()) {
        News* news = pq.top();
        if (time < news->time) break;
        pq.pop();
 
        if (news->status == 0) {
            continue; // 삭제된 뉴스
        }
            Channel* channel = getChannel[news->cid];
            for (int i = 0; i < channel->uidCnt; i++) {
                User* user = channel->uids[i];
                user->news[user->newsCnt++] = news;
            }
    }
}
 
void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
    sendNews(mTime);
    // 유저
 
    // 신규 유저
    if (getUser.find(mUID) == getUser.end()) {
        User* user = &Users[userCnt++];
        user->newsCnt = 0;
        user->uid = mUID;
        getUser[mUID] = user;
    }
    User* user = getUser[mUID];
 
 
    // 채널 가입
    for (int i = 0; i < mNum; i++) {
        if (getChannel.find(mChannelIDs[i]) == getChannel.end()) {
            // 신규 채널
            Channel* channel = &Channels[channelCnt++];
            channel->uidCnt = 0;
            getChannel[mChannelIDs[i]] = channel;
        }
        Channel* channel = getChannel[mChannelIDs[i]];
        channel->uids[channel->uidCnt++] = user;
    }
}
 
int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{;
 
    sendNews(mTime); // delay 1 이상이라 순서 상관 X
 
    // 신규 뉴스
    News* news = &NewsNews[newsCnt++];
    news->time = mTime + mDelay;
    news->nid = mNewsID;
    news->cid = mChannelID;
    news->status = 1;
    getNews[mNewsID] = news;
 
    // 알림 대기 등록
    pq.emplace(news);
 
    // 채널
    Channel* channel = getChannel[mChannelID];
    return channel->uidCnt;
}
 
void cancelNews(int mTime, int mNewsID)
{
    News* news = getNews[mNewsID];
    news->status = 0;
}
 
int checkUser(int mTime, int mUID, int mRetIDs[])
{
    sendNews(mTime);
 
    User* user = getUser[mUID];
 
    int i = 0;
    int cnt = 0;
 
    priority_queue<News*, vector<News*>, cmp>p;
 
    while (i != user->newsCnt) {
        if (user->news[i]->status) {
            p.emplace(user->news[i]);
            cnt++;
        }
        i++;
    }
 
    i = 0;
    while (!p.empty() && i != 3) {
        mRetIDs[i++] = p.top()->nid;
        p.pop();
    }
 
    user->newsCnt = 0;
 
    return cnt;
}