//
//  1002.cpp
//  PAT
//
//  Created by xiaoxiangzi on 2018/3/9.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Sum {
    static const unordered_map<char, string> NUM_MAP;
public:
    string sum(const string& input) {
        int sumResult = 0;
        for (size_t i = 0; i < input.size(); i++) {
            char c = input.at(i);
            sumResult += (int)c - 48;
        }
        string sumStr = std::to_string(sumResult);
        string result = "";
        bool isEmpty = true;
        for (size_t i = 0; i < sumStr.size(); i++) {
            auto str = NUM_MAP.at(sumStr.at(i));
            if (!isEmpty) {
                result += " ";
            }
            result += str;
            isEmpty = false;
        }
        
        return result;
    }
};

const unordered_map<char, string> Sum::NUM_MAP = {
    {'1', "yi"},
    {'2', "er"},
    {'3', "san"},
    {'4', "si"},
    {'5', "wu"},
    {'6', "liu"},
    {'7', "qi"},
    {'8', "ba"},
    {'9', "jiu"},
    {'0', "ling"},
};

int main(int argc, const char * argv[]) {
   string input;
   std::cin >> input;
   Sum s;
   cout << s.sum(input);
  
   return 0;
}

