//
//  1014.cpp
//  PAT
//
//  Created by xiaoxiangzi on 18/3/10.
//  Copyright © 2018年 xiaoxiangzi.com. All rights reserved.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <sstream>
using namespace std;

int findDateIndex(const string& s1, const string&s2, int& day) {
    int i = 0;
    while (i < s1.size() && i < s2.size()) {
        char c1 = s1.at(i);
        char c2 = s2.at(i);
        if (c1 == c2) {
            if (c1 >= 'A' && c1 <= 'G') {
                day = c1 - 'A';
                break;
            }
        }
        i++;
    }
    return i;
}

int findHour(const string& s1, const string&s2) {
    int i = 0;
    int hour = -1;
    while (i < s1.size() && i < s2.size()) {
        char c1 = s1.at(i);
        char c2 = s2.at(i);
        if (c1 == c2) {
            if (c1 >= 'A' && c1 <= 'N') {
                hour = c1 - 'A' + 10;
                break;
            } else if (c1 >= '0' && c1 <= '9') {
                hour = c1 - '0';
                break;
            }
        }
        i++;
    }
    return hour;
}

int findMin(const string& s1, const string&s2) {
    int i = 0;
    int min = -1;
    while (i < s1.size() && i < s2.size()) {
        char c1 = s1.at(i);
        char c2 = s2.at(i);
        if (c1 == c2) {
            if ((c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z')) {
                min = i;
                break;
            }
        }
        i++;
    }
    return min;
}

string DAYS[7] = {
    "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"
};

//int main(int argc, const char * argv[]) {
////        freopen("1014.txt", "r", stdin);
//    //    freopen("1030_1.txt", "r", stdin);
//    string s1;
//    string s2;
//    string s3;
//    string s4;
//    cin >> s1 >> s2 >> s3 >> s4;
//    int day = -1;
//    int dayIndex = findDateIndex(s1, s2, day);
//    int hour = findHour(s1.substr(dayIndex + 1, s1.size() - dayIndex - 1), s2.substr(dayIndex + 1, s2.size() - dayIndex - 1));
//    int min = findMin(s3, s4);
//    stringstream hourStr;
//    if (hour < 10) {
//        hourStr << "0";
//    }
//    hourStr << hour;
//    
//    stringstream minStr;
//    if (min < 10) {
//        minStr << "0";
//    }
//    minStr << min;
//    
//    cout << DAYS[day] << " " << hourStr.str() << ":" << minStr.str();
//    return 0;
//}
