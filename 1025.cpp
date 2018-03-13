//
//  1025.cpp
//  PAT
//
//  Created by xiaoxiangzi on 2018/3/12.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <sstream>
using namespace std;

struct Node {
    int address;
    int data;
    int next;
};

int reverseList(int headAddress, int n, int k, unordered_map<int, Node>& listMap) {
    if (n < k) {
        return headAddress;
    }
    int nullAddr = -1;
    if (headAddress == nullAddr) {
        return headAddress;
    }
    
    Node& oldHead = listMap[headAddress];
    int cur = headAddress;
    int next = listMap[headAddress].next;
    for (int i = 1; i < k; i++) {
        if (next != nullAddr) {
            Node& nextNode = listMap[next];
            int tmp = nextNode.next;
            nextNode.next = cur;
            cur = next;
            next = tmp;
            headAddress = cur;
        }
    }
    
    if (next == nullAddr) {
        oldHead.next = nullAddr;
    } else {
        oldHead.next = reverseList(next, n - k, k, listMap);
    }
    
    return headAddress;
}

void printListMap(int headAddress, unordered_map<int, Node>& listMap) {
//    printf("#############\n");
    int pointer = headAddress;
    while (pointer != -1) {
        Node& node = listMap[pointer];
        string s = "";
        if (node.next < 0) {
            printf("%05d %d %d\n", node.address, node.data, node.next);
        } else  {
            printf("%05d %d %05d\n", node.address, node.data, node.next);
        }
        
        pointer = node.next;
    }
//    printf("#############\n");
}

int main(int argc, const char * argv[]) {
//    freopen("1025.txt", "r", stdin);
   //        freopen("1067_1.txt", "r", stdin);
   
   string listHead;
   unordered_map<int, Node> listMap;
   int n = 0;
   int k = 0;
   cin >> listHead >> n >> k;
   int headAddress = 0;
   istringstream(listHead) >> headAddress;
   for (int i = 0; i < n; i++) {
       Node node;
       cin >> node.address >> node.data >> node.next;
       listMap.insert(pair<int, Node>(node.address, node));
   }
//    printListMap(headAddress, listMap);
   headAddress = reverseList(headAddress, n, k, listMap);
   printListMap(headAddress, listMap);
   
   return 0;
}

