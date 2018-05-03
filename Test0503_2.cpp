//
//  Test0503_2.cpp
//  pat
//
//  Created by xiaoxiangzi on 2018/5/3.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

struct Member {
    int id;
    int depth;
    int parent;
    vector<int> children;
};

class FamilyTree {
    
public:
    void readTree(int n) {
        _root = -1;
        for (int i = 1; i <= n; i++) {
            Member m;
            m.id = i;
            m.parent = -1;
            _members.insert(pair<int, Member>(i, m));
        }
        
        for (int i = 1; i <= n; i++) {
            Member& m = _members[i];
            cin >> m.parent;
            if (m.parent == -1) {
                _root = i;
                Member& rootMem = _members[_root];
                rootMem.depth = 1;
                continue;
            }
            
            Member& parent = _members[m.parent];
            parent.children.push_back(m.id);
        }
    }
    
    void printYoungest() {
        if (_root < 0) {
            cout << 0 << endl;
            return;
        }
        int depth = 1;
        queue<int> q;
        q.push(_root);
        vector<int> result;
        result.push_back(_root);
        
        while (!q.empty()) {
            int curId = q.front();
            q.pop();
            Member& curMem = _members[curId];
            int curDepth = curMem.depth;
            int curChildDepth = curDepth + 1;
            bool isYoungest = false;
            if (curChildDepth >= depth && curMem.children.size() > 0) {
                if (curChildDepth > depth) {
                    result.clear();
                }
                depth = curChildDepth;
                isYoungest = true;
            }
            
            for (int i = 0; i < curMem.children.size(); i++) {
                int childId = curMem.children[i];
                Member& child = _members[childId];
                child.depth = curChildDepth;
                
                if (isYoungest) {
                    result.push_back(childId);
                }
                q.push(childId);
            }
        }
        
        cout << depth << endl;
        if (result.size() > 0) {
            cout << result[0];
            for (int i = 1; i < result.size(); i++) {
                cout << " " << result[i];
            }
        } else {
            cout << endl;
        }
    }
private:
    int _root;
    unordered_map<int, Member> _members;
};

int main(int argc, const char * argv[]) {
//    freopen("Test0503_2.txt", "r", stdin);
    int n = 0;
    cin >> n;
    FamilyTree tree;
    tree.readTree(n);
    tree.printYoungest();

    return 0;
}
