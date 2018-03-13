//
//  1030.cpp
//  PAT
//
//  Created by xiaoxiangzi on 18/3/10.
//  Copyright © 2018年 xiaoxiangzi.com. All rights reserved.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int64_t calcPerfectSeq(vector<int64_t> nums, int64_t p) {
    int size = (int) nums.size();
    
    if (size == 1) {
        return 1;
    }
    
    // 从小到大排列，从最大的数开始找，如果有符合条件的，那么两个index的距离就是序列的长度
    sort(nums.begin(), nums.end());
    int maxCount = 0;
    for (int i = size - 1; i >= 0; i--) {
        int64_t ni = nums[i];
        
        int left = 0;
        int right = i - 1;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            int64_t nj = nums[middle];
            if (ni <= nj * p) {
                int count = i - middle + 1;
                if (count > maxCount) {
                    maxCount = count;
                }
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }
    }
    return maxCount;
}

int main(int argc, const char * argv[]) {
//        freopen("1030.txt", "r", stdin);
    //    freopen("1030_1.txt", "r", stdin);
    int64_t p = 0;
    int n = 0;
    vector<int64_t> nums;
    cin >> n >> p;
    nums.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    cout << calcPerfectSeq(nums, p);
    
    return 0;
}
