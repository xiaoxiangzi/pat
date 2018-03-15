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
    Fraction(int n, int m) : n(n), m(m) {}
    
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

    int n;
    int m;
};

bool hasCommonDivisor(int x, int y) {
    int m = max(x, y);
    for (int i = 2; i <= m / 2; i++) {
//        cout << "test:" << x << " "<< y << " "<< i << ", " << x % i << " " << y % i << endl;
        if (x % i == 0 && y % i == 0) {
            return true;
        }
    }
    return false;
}

void findSimplestFractionList(const Fraction& a, const Fraction& b, int k) {
//    vector<Fraction> result;
    
    int x = a.m * b.m;
    int y = a.n * b.m * k;
    int z = b.n * a.m * k;
    int minNum = min(y, z);
    int maxNum = max(y, z);
    int count = 0;
    
    for (int i = minNum + 1; i < maxNum - 1; i++) {
        if (i % x != 0) {
            continue;
        }
        int n = i / x;
        int m = k;
        if (!hasCommonDivisor(n, m)) {
//            result.push_back(Fraction(n, m))
            if (count > 0) {
                cout << " ";
            }
            cout << n << "/" << m;
            count++;
        }
    }
    
//    return result;
}

int main(int argc, const char * argv[]) {
    freopen("1062.txt", "r", stdin);
    //    freopen("1045_1.txt", "r", stdin);
    
    int k = 0;
    Fraction a(-1, -1);
    Fraction b(-1, -1);
    a.readFraction();
    b.readFraction();
    cin >> k;
    
//    vector<Fraction> result = findSimplestFractionList(a, b, k);
//    for (int i = 0; i < result.size(); i++) {
//        const Fraction& f = result[i];
//        if (i > 0) {
//            cout << " ";
//        }
//        cout << f.n << "/" << f.m;
//    }
    findSimplestFractionList(a, b, k);
    
    return 0;
}
