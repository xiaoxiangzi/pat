//
//  1067.cpp
//  PAT
//
//  Created by xiaoxiangzi on 18/3/11.
//  Copyright © 2018年 xiaoxiangzi.com. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
//        freopen("1067.txt", "r", stdin);
//        freopen("1067_1.txt", "r", stdin);
   int n;
   string password;
   vector<string> inputs;
   cin >> password >> n;
   int bufSize = 1024;
   char buf[bufSize];
   cin.getline(buf, bufSize);
   cin.getline(buf, bufSize);
   string input(buf);
   int tryCount = 0;
   bool succeed = false;
   while (input != "#") {
       if (input == password) {
           succeed = true;
           cout << "Welcome in" << endl;
           break;
       } else {
           cout << "Wrong password: " << input << endl;
       }
       tryCount++;
       
       if (tryCount >= n && !succeed) {
           cout << "Account locked" << endl;
           break;
       }
       
       cin.getline(buf, bufSize);
       input.clear();
       input.append(buf);
   }
   
   return 0;
}

