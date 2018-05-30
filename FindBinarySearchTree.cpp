//
//  FindBinarySearchTree.cpp
//  pat
//
//  Created by xiaoxiangzi on 2018/5/30.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;

static const int NULL_NODE = -1;

struct Node {
    int id;
    int value;
    int left;
    int right;
};

class SearchTree {
    
public:
    SearchTree() {
        _root = NULL_NODE;
        _n = 0;
    }
    
    void readTreePreOrder() {
        cin >> _n;
        _preOrderValues.resize(_n);
        for (int i = 0; i < _n; i++) {
            Node node;
            node.id = i;
            cin >> node.value;
            node.left = NULL_NODE;
            node.right = NULL_NODE;
            _nodes.insert(pair<int, Node>(i, node));
            _preOrderValues[i] = node.value;
            insertNodeToTree(_nodes.at(i));
        }
    }
    
    bool checkSearchTree() {
        vector<int> result = preOrderScan();
        bool isSearchTree = true;
        for (int i = 0; i < _n; i++) {
            if (result[i] != _preOrderValues[i]) {
                isSearchTree = false;
                break;
            }
        }
        
        return isSearchTree;
    }
    
    bool checkSearchTreeMirror() {
        formSearchTreeMirror();
        return checkSearchTree();
    }
    
    void printPostOrderScan() {
        vector<int> result;

        postOrderScanInternal(_root, result);
        
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) {
                cout << " ";
            }
            cout << result[i];
        }
        cout << endl;
    }
private:
    void formSearchTreeMirror() {
        _root = NULL_NODE;
        for (int i = 0; i < _n; i++) {
            Node& node = _nodes.at(i);
            node.left = NULL_NODE;
            node.right = NULL_NODE;
        }
        
        for (int i = 0; i < _n; i++) {
            insertNodeToTreeMirror(_nodes.at(i));
        }
    }
    
    void postOrderScanInternal(int nodeId, vector<int>& v) {
        if (nodeId == NULL_NODE) {
            return;
        }
        
        Node& node = _nodes.at(nodeId);
        postOrderScanInternal(node.left, v);
        postOrderScanInternal(node.right, v);
        v.push_back(node.value);
    }
    
    
    void insertNodeToTree(Node& node) {
        if (_root == NULL_NODE) {
            // 如果是空树直接插入
            _root = node.id;
            return;
        }
        
        Node* curNode = &_nodes.at(_root);
        while (true) {
            if (node.value < curNode->value) {
                if (curNode->left == NULL_NODE) {
                    curNode->left = node.id;
                    
                    break;
                } else {
                    curNode = &_nodes.at(curNode->left);
                }
            } else {
                if (curNode->right == NULL_NODE) {
                    curNode->right = node.id;
                    break;
                } else {
                    curNode = &_nodes.at(curNode->right);
                }
            }
        }
    }
    
    void insertNodeToTreeMirror(Node& node) {
        if (_root == NULL_NODE) {
            // 如果是空树直接插入
            _root = node.id;
            return;
        }
        
        Node* curNode = &_nodes.at(_root);
        while (true) {
            if (node.value >= curNode->value) {
                if (curNode->left == NULL_NODE) {
                    curNode->left = node.id;
                    break;
                } else {
                    curNode = &_nodes.at(curNode->left);
                }
            } else {
                if (curNode->right == NULL_NODE) {
                    curNode->right = node.id;
                    break;
                } else {
                    curNode = &_nodes.at(curNode->right);
                }
            }
        }
    }
    
    void preOrderScanInternal(int nodeId, vector<int>& v) {
        if (nodeId == NULL_NODE) {
            return;
        }
        Node& node = _nodes.at(nodeId);
        v.push_back(node.value);
        preOrderScanInternal(node.left, v);
        preOrderScanInternal(node.right, v);
    }
    
    vector<int> preOrderScan() {
        vector<int> result;
        preOrderScanInternal(_root, result);
        return result;
    }
private:
    int _root;
    int _n;
    unordered_map<int, Node> _nodes;
    vector<int> _preOrderValues;
};

int main(int argc, const char * argv[]) {
//    freopen("FindBinarySearchTree.txt", "r", stdin);
    SearchTree tree;
    tree.readTreePreOrder();
    bool result = false;
    if (tree.checkSearchTree()) {
        result = true;
    } else if (tree.checkSearchTreeMirror()) {
        result = true;
    }
    
    if (result) {
        cout << "YES" << endl;
        tree.printPostOrderScan();
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}
