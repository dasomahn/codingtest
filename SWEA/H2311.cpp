#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_map>
 
#define CAPACITY 1000
#define SCHOOL 10
#define STUDENT 7500
 
using namespace std;
 
struct Student {
 
    int id;
    int rank;
 
    // 우선순위 순서대로
    pair<int, int> schools[SCHOOL]; // 학교, 거리
    int school_idx;
 
} Students[STUDENT];
 
int student_cnt;
unordered_map<int, Student*> get_student;
 
struct cmp_student {
    bool operator () (Student* s1, Student* s2) const {
        if (s1->rank == s2->rank) {
            return s1->id < s2->id;
        }
        return s1->rank > s2->rank;
    }
};
 
struct School {
    int id;
    int x, y;
 
    set<Student*, cmp_student> students;
    set<Student*, cmp_student> waitlist;
 
    void init(int _id, int _x, int _y) {
        id = _id;
        x = _x; 
        y = _y;
 
        students.clear();
        waitlist.clear();
    }
 
} Schools[SCHOOL];
 
int c, n;
 
void init(int C, int N, int mX[], int mY[]) {
    c = C;
    n = N;
    student_cnt = 0;
 
    for (int i = 0; i < n; i++) {
        Schools[i].init(i, mX[i], mY[i]);
    }
 
    get_student.clear();
     
    return;
}
 
Student* new_student(int mStudent) {
    Student* student = &Students[student_cnt++];
    student->id = mStudent;
    student->school_idx = 0;
 
    get_student[mStudent] = student;
 
    return student;
}
 
bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
}
 
void add_student(Student* student, int s_id) {
    School* school = &Schools[s_id];
    school->students.insert(student);
 
    if (school->students.size() == c + 1) {
        auto iter = prev(school->students.end());
        Student* s = get_student[(*iter)->id];
 
        school->students.erase(iter);
        school->waitlist.insert(s);
 
        s->school_idx++;
        int next_s = s->schools[s->school_idx].first;
        add_student(s, next_s);
    }
}
 
int add(int mStudent, int mX, int mY) {
    Student* student = new_student(mStudent);
 
    int i;
    for (i = 0; i < n; i++) {
        student->schools[i] = { i,
            abs(mX - Schools[i].x) + abs(mY - Schools[i].y) };
    }
    sort(student->schools, student->schools + n, cmp);
    student->rank = student->schools[n - 1].second;
 
    add_student(student, student->schools[0].first);
 
    return student->schools[student->school_idx].first;
}
 
void pull_wait(int s_id) {
    School* school = &Schools[s_id];
 
    if (school->waitlist.size() != 0) {
        auto iter = school->waitlist.begin();
        Student* s = get_student[(*iter)->id];
 
        school->waitlist.erase(iter);
        school->students.insert(s);
 
        int ori_id = s->schools[s->school_idx].first;
        School* ori_s = &Schools[ori_id];
        ori_s->students.erase(ori_s->students.find(s));
 
        s->school_idx--;
        pull_wait(ori_id);
    }
}
 
int remove(int mStudent) {
    Student* student = get_student[mStudent];
 
    int s_id = student->schools[student->school_idx].first;
    School* school = &Schools[s_id];
     
    school->students.erase(school->students.find(student));
 
    pull_wait(s_id);
 
    if (student->school_idx != 0) {
        School* wait_s = &Schools[student->schools[student->school_idx - 1].first];
        wait_s->waitlist.erase(wait_s->waitlist.find(student));
    }
 
    return s_id;
}
 
int status(int mSchool) {
    return Schools[mSchool].students.size();
}