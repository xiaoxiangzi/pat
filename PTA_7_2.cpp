//
//  PTA_7_2.cpp
//  PAT
//
//  Created by xiaoxiangzi on 18/4/1.
//  Copyright © 2018年 xiaoxiangzi.com. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int id;
    int left;
    int right;
};

int readChild() {
    string s;
    cin >> s;
    int child = -1;
    if (s == "-") {
        child = -1;
    } else {
        child = atoi(s.c_str());
    }
    return child;
}

vector<int> findLeaves(const unordered_map<int, Node>& nodes, int root) {
    vector<int> leaves;
    
    if (root < 0) {
        return leaves;
    }
    
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int curId = q.front();
        q.pop();
        auto& node = nodes.at(curId);
        if (node.left < 0 && node.right < 0) {
            leaves.push_back(node.id);
        } else {
            if (node.left >= 0) {
                q.push(node.left);
            }
            
            if (node.right >= 0) {
                q.push(node.right);
            }
        }
    }
    
    return leaves;
}

int main(int argc, const char * argv[]) {
    freopen("PTA_7_2.txt", "r", stdin);

    int n = 0;
    cin >> n;
    int root = -1;
    
    unordered_map<int, Node> nodes;
    for (int i = 0; i < n; i++) {
        Node node;
        node.id = i;
        node.left = readChild();
        node.right = readChild();
        if (root < 0) {
            root = node.id;
        } else {
            if (root == node.left || root == node.right) {
                root = node.id;
            }
        }
        nodes[node.id] = node;
    }
//    cout << "root:" << root << endl;
    vector<int> leaves = findLeaves(nodes, root);
    for (int i = 0; i < leaves.size(); i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << leaves[i];
    }
}



