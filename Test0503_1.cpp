//
//  Test0503_1.cpp
//  pat
//
//  Created by xiaoxiangzi on 2018/5/3.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//
#include <iostream>
#include <unordered_map>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

struct Vertex {
    int id;
    vector<int> edges;
};

class Graph {
    
public:
    void readGraph(int n, int m) {
        for (int i = 1; i <= n; i++) {
            Vertex v;
            v.id = i;
            _vertexes.insert(pair<int, Vertex>(i, v));
        }
        
        for (int i = 0; i < m; i++) {
            int v1Id = 0;
            int v2Id = 0;
            cin >> v1Id >> v2Id;
            auto& v1 = _vertexes.at(v1Id);
            auto& v2 = _vertexes.at(v2Id);
            v1.edges.push_back(v2Id);
            v2.edges.push_back(v1Id);
        }
        _totalEdgeNum = m;
    }
    
    bool canConquer(const vector<int>& cities) {
        if (_vertexes.empty()) {
            return true;
        }
        
        if (_vertexes.size() == 1) {
            return true;
        }
        
        int delEdges = 0;
        unordered_map<int, bool> checkedFlags;
        for (auto iter = cities.begin(); iter != cities.end(); iter++) {
            int vId = *iter;
            if (checkedFlags.find(vId) == checkedFlags.end()) {
                auto& v = _vertexes[vId];
                for (int j = 0; j < v.edges.size(); j++) {
                    int vjId = v.edges[j];
                    if (checkedFlags.find(vjId) == checkedFlags.end()) {
                        delEdges++;
                    }
                }
                checkedFlags[vId] = true;
            }
        }
        
        return delEdges == _totalEdgeNum;
    }
private:
    unordered_map<int, Vertex> _vertexes;
    int _totalEdgeNum;
};

int main(int argc, const char * argv[]) {
//    freopen("Test0503_1.txt", "r", stdin);
    int n = 0;
    int m = 0;
    cin >> n >> m;
    Graph g;
    g.readGraph(n, m);
    int k = 0;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int num = 0;
        cin >> num;
        vector<int> vertexes;
        
        for (int j = 0; j < num; j++) {
            int vId = 0;
            cin >> vId;
            vertexes.push_back(vId);
        }
        
        if (g.canConquer(vertexes)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}


