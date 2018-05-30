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
#include <math.h>
using namespace std;

static const double TARGET_NUM = 24;

double calc(double a, double b, char op, bool& valid) {
    if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else if (op == '*') {
        return a * b;
    } else {
        if (b == 0) {
            valid = false;
            return -1;
        }
        
        return a / b;
    }
}

string formatOutput(const string& format, int a, int b, int c, int d, int op1, int op2, int op3) {
    char buf[128];
    snprintf(buf, sizeof(buf), format.c_str(), a, op1, b, op2, c, op3, d);
    return string(buf);
}

double calcForm1(int a, int b, int c, int d, int op1, int op2, int op3) {
    // ((a op1 b) op2 c) op3 d
    bool valid = true;
    double tmp = calc(a, b, op1, valid);
    if (!valid) {
        return -1;
    }
    
    tmp = calc(tmp, c, op2, valid);
    if (!valid) {
        return -1;
    }
    
    tmp = calc(tmp, d, op3, valid);
    if (!valid) {
        return -1;
    }
    
    return tmp;
}

double calcForm2(int a, int b, int c, int d, int op1, int op2, int op3) {
    // (a op1 (b op2 c)) op3 d
    bool valid = true;
    double tmp = calc(b, c, op2, valid);
    if (!valid) {
        return -1;
    }
    
    tmp = calc(a, tmp, op1, valid);
    if (!valid) {
        return -1;
    }
    
    tmp = calc(tmp, d, op3, valid);
    if (!valid) {
        return -1;
    }
    
    return tmp;
}

double calcForm3(int a, int b, int c, int d, int op1, int op2, int op3) {
    // (a op1 b) op2 (c op3 d)
    bool valid = true;
    double tmp1 = calc(a, b, op1, valid);
    if (!valid) {
        return -1;
    }
    
    double tmp2 = calc(c, d, op3, valid);
    if (!valid) {
        return -1;
    }
    
    double tmp = calc(tmp1, tmp2, op2, valid);
    if (!valid) {
        return -1;
    }
    
    return tmp;
}

double calcForm4(int a, int b, int c, int d, int op1, int op2, int op3) {
    // a op1 ((b op2 c) op3 d)
    bool valid = true;
    double tmp = calc(b, c, op2, valid);
    if (!valid) {
        return -1;
    }
    
    tmp = calc(tmp, d, op3, valid);
    if (!valid) {
        return -1;
    }
    
    tmp = calc(a, tmp, op1, valid);
    if (!valid) {
        return -1;
    }
    
    return tmp;
}

double calcForm5(int a, int b, int c, int d, int op1, int op2, int op3) {
    // a op1 (b op2 (c op3 d))
    bool valid = true;
    double tmp = calc(c, d, op3, valid);
    if (!valid) {
        return -1;
    }
    
    tmp = calc(b, tmp, op2, valid);
    if (!valid) {
        return -1;
    }
    
    tmp = calc(a, tmp, op1, valid);
    if (!valid) {
        return -1;
    }
    
    return tmp;
}

bool isTargetNum(double value) {
    return abs(value - TARGET_NUM) < 0.0000001;
}

string calc24(int a, int b, int c, int d, const vector<char>& ops) {
    
    for (int i = 0; i < ops.size(); i++) {
        char op1 = ops[i];
        for (int j = 0; j < ops.size(); j++) {
            char op2 = ops[j];
            for (int k = 0; k < ops.size(); k++) {
                char op3 = ops[k];
                // ((a op1 b) op2 c) op3 d
                double result = calcForm1(a, b, c, d, op1, op2, op3);
                if (result == TARGET_NUM) {
                    return formatOutput("((%d%c%d)%c%d)%c%d", a, b, c, d, op1, op2, op3);
                }
                
                // (a op1 (b op2 c)) op3 d
                result = calcForm2(a, b, c, d, op1, op2, op3);
                if (isTargetNum(result)) {
                    return formatOutput("(%d%c(%d%c%d))%c%d", a, b, c, d, op1, op2, op3);
                }
                
                // (a op1 b) op2 (c op3 d)
                result = calcForm3(a, b, c, d, op1, op2, op3);
                if (isTargetNum(result)) {
                    return formatOutput("(%d%c%d)%c(%d%c%d)", a, b, c, d, op1, op2, op3);
                }
                
                // a op1 ((b op2 c) op3 d)
                result = calcForm4(a, b, c, d, op1, op2, op3);
                if (isTargetNum(result)) {
                    return formatOutput("%d%c((%d%c%d)%c%d)", a, b, c, d, op1, op2, op3);
                }

                // a op1 (b op2 (c op3 d))
                result = calcForm5(a, b, c, d, op1, op2, op3);
                if (isTargetNum(result)) {
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
    
    bool hasCalced24 = false;
    for (int i = 0; i < totalNum; i++) {
        int a = nums[i];
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
                    result = calc24(a, b, c, d, ops);
                    hasCalced24 = result != "";
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
            cout << result << endl;
            break;
        }
    }
    
    if (!hasCalced24) {
        cout << -1 << endl;
    }
    
    return 0;
}
