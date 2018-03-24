//
//  1068.cpp
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

enum FindState {
    UNIQUE,
    MULTIPLE,
    NOT_EXIST,
};

bool compareColor(const vector<vector<int> >& colors, int m, int n, int color, int dstRow, int dstCol, int tol) {
    if (dstRow >= 0 && dstCol >= 0 && dstRow < n && dstCol < m) {
        int dstColor = colors[dstRow][dstCol];
        int threshold = abs(color - dstColor);
        if (threshold <= tol) {
            return false;
        }
    }
    
    return true;
}

bool checkColor(const vector<vector<int> >& colors, int m, int n, int tol, int color, int row, int col) {
    // left top
    if (!compareColor(colors, m, n, color, row - 1, col - 1, tol)) {
        return false;
    }
    // top
    if (!compareColor(colors, m, n, color, row - 1, col, tol)) {
        return false;
    }
    // right top
    if (!compareColor(colors, m, n, color, row - 1, col + 1, tol)) {
        return false;
    }
    // left
    if (!compareColor(colors, m, n, color, row, col - 1, tol)) {
        return false;
    }
    // right
    if (!compareColor(colors, m, n, color, row, col + 1, tol)) {
        return false;
    }
    // left bottom
    if (!compareColor(colors, m, n, color, row + 1, col - 1, tol)) {
        return false;
    }
    // bottom
    if (!compareColor(colors, m, n, color, row + 1, col, tol)) {
        return false;
    }
    // right bottom
    if (!compareColor(colors, m, n, color, row + 1, col + 1, tol)) {
        return false;
    }
    
    return true;
}

FindState findColor(const vector<vector<int> >& colors, int m, int n, int tol, const unordered_map<int, bool>& skipMap, int& targetColor, int& targetRow, int& targetCol) {
    bool find = false;
    FindState state = NOT_EXIST;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int color = colors[i][j];
            bool skipped = skipMap.at(color);
            if (skipped) {
                // mutiple, skip
                continue;
            }
            
            if (checkColor(colors, m, n, tol, color, i, j)) {
                if (!find) {
                    targetRow = i;
                    targetCol = j;
                    targetColor = color;
                    state = UNIQUE;
                    find = true;
                } else {
                    state = MULTIPLE;
                }
            }
        }
    }
    
    return state;
}

//int main(int argc, const char * argv[]) {
////    freopen("1068.txt", "r", stdin);
////    freopen("1068_2.txt", "r", stdin);
////    freopen("1068_3.txt", "r", stdin);
//    int m = 0;
//    int n = 0;
//    int tol = 0;
//    vector<vector<int> > colors;
//    unordered_map<int, bool> skipMap;
//    cin >> m >> n >> tol;
//    colors.resize(n);
//    for (int i = 0; i < n; i++) {
//        vector<int>& vRow = colors[i];
//        vRow.resize(m);
//        for (int j = 0; j < m; j++) {
//            int color = 0;
//            cin >> color;
//            if (skipMap.find(color) != skipMap.end()) {
//                // 重复颜色，跳过检查
//                skipMap[color] = true;
//            } else {
//                skipMap.insert(pair<int, bool>(color, false));
//            }
//            colors[i][j] = color;
//        }
//    }
//    int targetRow = -1;
//    int targetCol = -1;
//    int targetColor = -1;
//    FindState state = findColor(colors, m, n, tol, skipMap, targetColor, targetRow, targetCol);
//    switch (state) {
//        case UNIQUE:
//            // (5, 3): 16711680
//            cout << "(" << targetCol + 1 << ", " << targetRow + 1 << "): " << targetColor;
//            break;
//        case MULTIPLE:
//            cout << "Not Unique" << endl;
//            break;
//        default:
//            cout << "Not Exist" << endl;
//            break;
//    }
//    
//    return 0;
//}


