//
//  1068_2.cpp
//  PAT
//
//  Created by xiaoxiangzi on 18/3/9.
//  Copyright © 2018年 xiaoxiangzi.com. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h>
using namespace std;

int row = 0;
int col = 0;
int tol = 0;
vector<vector<int>> colors;
unordered_map<int, int> countMap;
int result = 0;
int targetRow = 0;
int targetCol = 0;
int targetColor = 0;

int pos[8][2] = {
    {1, 1},
    {1, 0},
    {1, -1},
    {0, 1},
    {0, -1},
    {-1, 1},
    {-1, 0},
    {-1, -1},
};

bool check(int r, int c) {
    int color = colors[r][c];
    for (int i = 0; i < 8; i++) {
        int dstR = r + pos[i][0];
        int dstC = c + pos[i][1];
        if (dstR >= 0 && dstC >=0 && dstR < row && dstC < col && abs(colors[dstR][dstC] - color) <= tol) {
            return false;
        }
    }
    
    return true;
}

//int main(int argc, const char * argv[]) {
////        freopen("1068.txt", "r", stdin);
////        freopen("1068_2.txt", "r", stdin);
////        freopen("1068_3.txt", "r", stdin);
//    
//    cin >> col >> row >> tol;
//    colors.resize(row, vector<int>(col));
//    for (int i = 0; i < row; i++) {
//        for (int j = 0; j < col; j++) {
//            int color = 0;
//            cin >> color;
//            colors[i][j] = color;
//            int count = countMap[color];
//            countMap[color] = ++count;
//        }
//    }
//    
//    for (int i = 0; i < row; i++) {
//        for (int j = 0; j < col; j++) {
//            int color = colors[i][j];
//            if ((countMap[color] == 1) && check(i, j)) {
//                result++;
//                targetRow = i;
//                targetCol = j;
//                targetColor = color;
//            }
//        }
//    }
//    
//    if (result == 0) {
//        cout << "Not Exist";
//    } else if (result == 1) {
//        cout << "(" << targetCol + 1 << ", " << targetRow + 1 << "): " << targetColor;
//    } else {
//        cout << "Not Unique";
//    }
//    
//    return 0;
//}

