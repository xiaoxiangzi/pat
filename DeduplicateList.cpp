//
//  DeduplicateList.cpp
//  PAT
//
//  Created by xiaoxiangzi on 18/3/24.
//  Copyright © 2018年 xiaoxiangzi.com. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node {
    int address;
    int data;
    int nextAddress;
    bool isDuplicated;
};

vector<int> deduplicateList(int headAddress, unordered_map<int, Node>& nodes, const unordered_map<int, bool>& absDataMap) {
    vector<int> lists;
    lists.push_back(headAddress);
    if (nodes.size() == 0) {
        return lists;
    }
    
    Node* preNode = nullptr;
    Node* curNode = &nodes.at(headAddress);
    int removedList = -1;
    Node* removedTailNode = nullptr;
    while (curNode) {
        int curNextAddress = curNode->nextAddress;
        if (curNode->isDuplicated) {
            if (removedList == -1) {
                // 新开一个移除链表
                removedList = curNode->address;
                lists.push_back(removedList);
            } else {
                // 已经有一个移除的链表，则往该链表后面加元素
                removedTailNode->nextAddress = curNode->address;
            }
            removedTailNode = curNode;
            curNode->nextAddress = -1;
            
            if (preNode) {
                preNode->nextAddress = curNextAddress;
            }
            
            if (curNextAddress != -1) {
                curNode = &nodes.at(curNextAddress);
            } else {
                curNode = nullptr;
            }
        } else {
            if (curNextAddress != -1) {
                preNode = curNode;
                curNode = &nodes.at(curNextAddress);
            } else {
                curNode = nullptr;
            }
        }
    }
    
    return lists;
}

int main(int argc, const char * argv[]) {
//    freopen("DuplicateList.txt", "r", stdin);
    //    freopen("1030_1.txt", "r", stdin);
    int headAddress = -1;
    int n = 0;
    cin >> headAddress;
    cin >> n;
    unordered_map<int, Node> nodes;
    unordered_map<int, bool> absDataMap;
    for (int i = 0; i < n; i++) {
        Node node;
        cin >> node.address >> node.data >> node.nextAddress;
        nodes.insert(pair<int, Node>(node.address, node));
    }
    
    int pointer = headAddress;
    while (pointer != -1) {
        Node& node = nodes.at(pointer);
        int absData = abs(node.data);
        auto iter = absDataMap.find(absData);
        if (iter == absDataMap.end()) {
            node.isDuplicated = false;
            absDataMap.insert(pair<int, bool>(absData, true));
        } else {
            node.isDuplicated = true;
        }
        pointer = node.nextAddress;
    }
    
    vector<int> lists = deduplicateList(headAddress, nodes, absDataMap);
    for (int i = 0; i < lists.size(); i++) {
        int pointer = lists[i];
        
        if (pointer == -1) {
            cout << endl;
        }
        
        while (pointer != -1) {
            Node& node = nodes[pointer];
            if (node.nextAddress < 0) {
                printf("%05d %d %d\n", node.address, node.data, node.nextAddress);
            } else  {
                printf("%05d %d %05d\n", node.address, node.data, node.nextAddress);
            }
            
            pointer = node.nextAddress;
        }
    }
    
    return 0;
}



