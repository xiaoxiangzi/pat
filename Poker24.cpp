//
//  Poker24.cpp
//  pat
//
//  Created by xiaoxiangzi on 2018/5/30.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

static const int TARGET_NUM = 24;

int calc(int a, int b, char op) {
    if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else if (op == '*') {
        return a * b;
    } else {
        return a / b;
    }
}

string formatOutput(const string& format, int a, int b, int c, int d, int op1, int op2, int op3) {
    char buf[128];
    snprintf(buf, sizeof(buf), format.c_str(), a, b, c, d, op1, op2, op3);
    return string(buf);
}

string calc24(int a, int b, int c, int d, const vector<char>& ops) {
    
    for (int i = 0; i < ops.size(); i++) {
        char op1 = ops[i];
        for (int j = 0; j < ops.size(); j++) {
            char op2 = ops[j];
            for (int k = 0; k < ops.size(); k++) {
                char op3 = ops[j];
                // ((a op1 b) op2 c) op3 d
                int result = calc(calc(calc(a, b, op1), c, op2), d, op3);
                if (result == TARGET_NUM) {
                    return formatOutput("((%d%c%d)%c%d)%c%d", a, b, c, d, op1, op2, op3);
                }
                
                // (a op1 (b op2 c)) op3 d
                result = calc(calc(a, calc(b, c, op2), op1), d, op3);
                if (result == TARGET_NUM) {
                    return formatOutput("(%d%c(%d%c%d))%c%d", a, b, c, d, op1, op2, op3);
                }
                
                // (a op1 b) op2 (c op3 d)
                result = calc(calc(a, b, op1), calc(c, d, op3), op2);
                if (result == TARGET_NUM) {
                    return formatOutput("(%d%c%d)%c(%d%c%d)", a, b, c, d, op1, op2, op3);
                }
                
                // a op1 ((b op2 c) op3 d)
                result = calc(calc(a, calc(b, c, op2), op1), d, op3);
                if (result == TARGET_NUM) {
                    return formatOutput("%d%c((%d%c%d)%c%d)", a, b, c, d, op1, op2, op3);
                }
                
                // a op1 (b op2 (c op3 d))
                result = calc(calc(a, calc(b, c, op2), op1), d, op3);
                if (result == TARGET_NUM) {
                    return formatOutput("%d%c(%d%c(%d%c%d))", a, b, c, d, op1, op2, op3);
                }
            }
        }
    }
    
    return "";
}

int main(int argc, const char * argv[]) {
    freopen("Poker24.txt", "r", stdin);
    vector<int> nums;
    vector<char> ops = {'+', '-', '*', '/'};
    int totalNum = 4;
    nums.resize(totalNum);
    cin >> nums[0] >> nums[1] >> nums[2] >> nums[3];
    
    for (int i = 0; i < totalNum; i++) {
        int a = nums[i];
        bool hasCalced24 = false;
        string result;
        for (int j = 0; j < totalNum; j++) {
            if (i == j) {
                continue;
            }
            int b = nums[j];
            for (int k = 0; k < totalNum; k++) {
                if (k == j || k == i) {
                    continue;
                }
                int c = nums[k];
                
                for (int l = 0; l < totalNum; l++) {
                    if (l == k || l == j || l == i) {
                        continue;
                    }
                    int d = nums[l];
                    hasCalced24 = calc24(a, b, c, d, ops) == "";
                    if (hasCalced24) {
                        break;
                    }
                }
                
                if (hasCalced24) {
                    break;
                }
            }
            
            if (hasCalced24) {
                break;
            }
        }
        
        if (hasCalced24) {
            cout << result;
            break;
        }
    }
    
    return 0;
}
