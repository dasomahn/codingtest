#include <iostream>
#include <set>
#include <unordered_map>
 
using namespace std;
 
struct Student {
    int score, id, idx;
 
    Student(int a=-1, int b=-1, int c=-1) : score(a), id(b), idx(c) {}
 
    bool operator<(Student s) const {
        // score 기준 오름차순
        if (score != s.score) {
            return score < s.score;
        }
        // 같다면 id 비교
        return id < s.id;
    }
};
 
set<Student> trees[6]; // 1학년 male, 1학년 female, 2학년 male, 2학년 female, 3학년 male, 3학년 female
unordered_map<int, Student> id_map; // id
 
void init() {
    ////cout << "init\n";
    trees[0].clear();
    trees[1].clear();
    trees[2].clear();
    trees[3].clear();
    trees[4].clear();
    trees[5].clear();
 
    id_map.clear();
 
    return;
}
 
int find_idx(int mGrade, char mGender[7]) {
    if (mGrade == 1) {
        if (mGender[0] == 'm') return 0;
        else return 1;
    }
    else if (mGrade == 2) {
        if (mGender[0] == 'm') return 2;
        else return 3;
    }
    else {
        if (mGender[0] == 'm') return 4;
        else return 5;
    }
}
 
int add(int mId, int mGrade, char mGender[7], int mScore) {
 
    int idx = find_idx(mGrade, mGender);
 
    Student student = Student(mScore, mId, idx);
    id_map[mId] = student; 
 
    trees[idx].insert(student);
 
 
    return trees[idx].rbegin()->id; // 제일 점수높은/id작은 학생의 id
}
 
int remove(int mId) {
    // 아예 없을 경우
    auto it = id_map.find(mId);
    if (it == id_map.end()) {
        return 0;
    }
 
    Student rm = it->second;
    id_map.erase(it); // hash에서 제거
    trees[rm.idx].erase(rm); // tree에 있는 rm을 지움. rm은 아직 살아있음
 
    return trees[rm.idx].size() == 0 ? 0: trees[rm.idx].begin()->id;
}
 
int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
    Student target = Student(mScore, 0, 0);
    Student *minNode = nullptr;
    int min_score = 300001;
    int min_id = 1000000001;
 
    int idx;
    for (int i = 0; i < mGradeCnt; i++) {
        for (int j = 0; j < mGenderCnt; j++) {
            idx = find_idx(mGrade[i], mGender[j]);
 
            auto iter = trees[idx].lower_bound(target);
            if (iter == trees[idx].end()) continue;
 
            if (min_score == 300001 || min_score > iter->score || (min_score == iter->score && min_id > iter->id)) {
                min_id = iter->id;
                min_score = iter->score;
            }
        }
    }
     
    if (min_score == 300001) return 0;
    return min_id;
}