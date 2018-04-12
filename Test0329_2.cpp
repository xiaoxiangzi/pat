//
//  Test0329_2.cpp
//  pat
//
//  Created by xiaoxiangzi on 2018/3/29.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int id;
    int left;
    int right;
};

void readNodeChild(Node& node) {
    string left;
    string right;
    cin >> left;
    cin >> right;
    if (left == "-") {
        node.left = -1;
    } else {
        node.left = atoi(left.c_str());
    }
    
    if (right == "-") {
        node.right = -1;
    } else {
        node.right = atoi(right.c_str());
    }

}

vector<int> scanBinaryTreeLeaves(int root, const unordered_map<int, Node>& nodes) {
    vector<int> result;
    
    if (root < 0) {
        return result;
    }
    
    deque<int> queue;
    queue.push_back(root);
    while (!queue.empty()) {
        int id = queue.front();
        queue.pop_front();
        auto& node = nodes.at(id);
        if (node.left < 0 && node.right < 0) {
            result.push_back(node.id);
        } else {
            if(node.left >= 0) {
                queue.push_back(node.left);
            }
            
            if (node.right >= 0) {
                queue.push_back(node.right);
            }
        }
    }
    
    return result;
}

int main(int argc, const char * argv[]) {
//    freopen("Test0329_2.txt", "r", stdin);
    int n = 0;
    cin >> n;
    unordered_map<int, Node> nodes;
    int root = -1;
    for (int i = 0; i < n; i++) {
        Node node;
        node.id = i;
        readNodeChild(node);
        if (root < 0) {
            root = node.id;
        } else {
            if (root == node.left || root == node.right) {
                // 更新根节点
                root = node.id;
            }
        }
        nodes.insert(pair<int, Node>(i, node));
    }
    
    vector<int> result = scanBinaryTreeLeaves(root, nodes);
    if (result.empty()) {
        cout << endl;
    } else {
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) {
                cout << " ";
            }
            cout << result[i];
        }
    }
    
    return 0;
}
