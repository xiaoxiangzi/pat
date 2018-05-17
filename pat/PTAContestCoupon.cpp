//
//  PTAContestCoupon.cpp
//  pat
//
//  Created by xiaoxiangzi on 2018/5/17.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <deque>
using namespace std;

struct Student {
    string email;
    int score;
};

static const int MIN_SCORE = 60;

int calcCoupon(int score, int g) {
    if (score >= MIN_SCORE && score < g) {
        return 20;
    }
    
    if (score >= g && score <= 100) {
        return 50;
    }
    
    return 0;
}

bool compareScore(const Student& a, const Student& b) {
    if (a.score == b.score) {
        return a.email < b.email;
    }
    return a.score > b.score;
}

int main(int argc, const char * argv[]) {
    freopen("PTAContestCoupon.txt", "r", stdin);
    
    int n, g, k;
    cin >> n >> g >> k;
    vector<Student> students;
    int totalCoupon = 0;
    for (int i = 0; i < n; i++) {
        Student s;
        cin >> s.email >> s.score;
        if (s.score >= MIN_SCORE) {
            students.push_back(s);
            totalCoupon += calcCoupon(s.score, g);
        }
    }
    
    sort(students.begin(), students.end(), compareScore);
    
    int totalStudent = (int) students.size();
    cout << totalCoupon << endl;
    int curRank = 0;
    int lastScore = -1;
    for (int i = 0; i < totalStudent; i++) {
        auto& s = students[i];
        if (lastScore != s.score) {
            curRank = i + 1;
        }
        
        if (curRank <= k) {
            lastScore = s.score;
            cout << curRank << " " << s.email << " " << s.score << endl;
        } else {
            break;
        }
    }
    
    return 0;
}
