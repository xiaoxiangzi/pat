//
//  1062.cpp
//  pat
//
//  Created by xiaoxiangzi on 2018/3/14.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;

class Fraction {
    
public:
    Fraction(int64_t n, int64_t m) : n(n), m(m) {}
    
    void readFraction() {
        string input;
        char c;
        while (true) {
            cin.get(c);
            if (c == '/') {
                n = stoi(input);
                input.clear();
            } else if (c == ' ') {
                if (n < 0 && m < 0) {
                    n = stoi(input);
                    m = n * n;
                    input.clear();
                } else {
                    m = stoi(input);
                    input.clear();
                }
                break;
            } else {
                input.append(&c, 1);
            }
            
            if (m >= 0 && n >= 0) {
                break;
            }
        }
    }
    
    int64_t n;
    int64_t m;
};

bool hasCommonDivisor(int64_t x, int64_t y) {
    int64_t m = max(x, y);
    for (int64_t i = 2; i <= m / 2; i++) {
        //        cout << "test:" << x << " "<< y << " "<< i << ", " << x % i << " " << y % i << endl;
        if (x % i == 0 && y % i == 0) {
            return true;
        }
    }
    return false;
}

// 通分方式要用int64_t才能解决溢出问题
void findSimplestFractionList(const Fraction& a, const Fraction& b, int64_t k) {
    int64_t x = a.m * b.m;
    int64_t y = a.n * b.m * k;
    int64_t z = b.n * a.m * k;
    int64_t minNum = min(y, z);
    int64_t maxNum = max(y, z);
    int count = 0;

    for (int64_t i = minNum + 1; i <= maxNum - 1;) {
        if (i % x != 0) {
            i = ceil(i * 1.0 / x) * x;
            continue;
        }
        int64_t n = i / x;
        int64_t m = k;
        i++;
        if (!hasCommonDivisor(n, m)) {
            if (count > 0) {
                cout << " ";
            }
            cout << n << "/" << m;
            count++;
        }
    }
}

// 参考贤华的方式，比较简洁的处理方式
void findSimplestFractionListRefXianhua(const Fraction& a, const Fraction& b, int k) {
    double f1 = a.n * 1.0 / a.m;
    double f2 = b.n * 1.0 / b.m;
    double minF = min(f1, f2);
    double maxF = max(f1, f2);
    int minNum = minF * k;
    int maxNum = maxF * k;
    int count = 0;
    for (int i = minNum; i <= maxNum; i++) {
        double fi = i * 1.0 / k;
        if (fi > minF && fi < maxF && !hasCommonDivisor(i, k)) {
            if (count > 0) {
                cout << " ";
            }
            cout << i << "/" << k;
            count++;
        }
    }
}

int main(int argc, const char * argv[]) {
//    freopen("1062.txt", "r", stdin);
    //    freopen("1045_1.txt", "r", stdin);
    
    int k = 0;
    Fraction a(-1, -1);
    Fraction b(-1, -1);
    a.readFraction();
    b.readFraction();
    cin >> k;
    
//    findSimplestFractionList(a, b, k);
    findSimplestFractionListRefXianhua(a, b, k);
    
    return 0;
}

