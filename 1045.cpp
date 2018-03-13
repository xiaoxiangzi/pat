//
//  1045.cpp
//  PAT
//
//  Created by xiaoxiangzi on 18/3/10.
//  Copyright © 2018年 xiaoxiangzi.com. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

vector<int> findPrincipalElem(const vector<int>& nums) {
    vector<int> result;
    if (nums.size() == 1) {
        result.push_back(nums[0]);
        return result;
    }
    int size = (int) nums.size();
    for (int i = 0; i < size; i++) {
        bool isLeftLess = true;
        bool isRightMore = true;
        int num = nums[i];
        if (i > 0) {
            for (int j = 0; j < i; j++) {
                int leftNum = nums[j];
                if (leftNum > num) {
                    isLeftLess = false;
                    break;
                }
            }
        }
        
        if ((i < size - 1) && isLeftLess) {
            for (int j = i + 1; j < size; j++) {
                int rightNum = nums[j];
                if (rightNum < num) {
                    isRightMore = false;
                    break;
                }
            }
        }
        
        if (isLeftLess && isRightMore) {
            result.push_back(num);
        }
        
    }
    return result;
}

int main(int argc, const char * argv[]) {
        freopen("1045.txt", "r", stdin);
    //    freopen("1045_1.txt", "r", stdin);
    int n;
    vector<int> nums;
    cin >> n;
    nums.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    vector<int> result = findPrincipalElem(nums);
    cout << result.size() << endl;
    if (result.size() > 0) {
        cout << result[0];
    } else {
        cout << endl;
    }
    for (int i = 1; i < result.size(); i++) {
        cout << " " << result[i];
    }
    
    return 0;
}
