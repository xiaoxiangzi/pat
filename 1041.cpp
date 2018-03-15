//
//  1041.cpp
//  pat
//
//  Created by xiaoxiangzi on 2018/3/15.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

struct Pos {
    int tryPos;
    int realPos;
    string id;
};

int main(int argc, const char * argv[]) {
//    freopen("1041.txt", "r", stdin);
    //        freopen("1067_1.txt", "r", stdin);
    int n = 0;
    cin >> n;
    unordered_map<int, Pos> posMap;
    for (int i = 0; i < n; i++) {
        Pos p;
        cin >> p.id >> p.tryPos >> p.realPos;
        posMap.insert(pair<int, Pos>(p.tryPos, p));
    }
    
    int m = 0;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int tryPos = 0;
        cin >> tryPos;
        auto iter = posMap.find(tryPos);
        if (iter != posMap.end()) {
            Pos& p = iter->second;
            cout << p.id << " " << p.realPos;
            
            if (i < m - 1) {
                cout << endl;
            }
        } else {
            cout << endl;
        }
        
    }
    
    return 0;
}
