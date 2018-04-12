//
//  HamiltonCircuit.cpp
//  pat
//
//  Created by xiaoxiangzi on 2018/4/12.
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
    unordered_map<int, bool> edges;
};

class Graph {
    
public:
    void readGraph(int n, int m) {
        for (int i = 1; i <= n; i++) {
            Vertex v;
            v.id = i;
            vertexes.insert(pair<int, Vertex>(i, v));
        }
        
        for (int i = 0; i < m; i++) {
            int v1Id = 0;
            int v2Id = 0;
            cin >> v1Id >> v2Id;
            auto& v1 = vertexes.at(v1Id);
            auto& v2 = vertexes.at(v2Id);
            v1.edges[v2Id] = true;
            v2.edges[v1Id] = true;
        }
    }
    
    bool isHamiltonCircuit(const vector<int>& circuit) {
        if (circuit.empty()) {
            if (vertexes.empty()) {
                return true;
            }
            
            return false;
        }
        
        if (circuit.size() == 1) {
            if (vertexes.size() == 1) {
                if (vertexes.find(circuit[0]) != vertexes.end()) {
                    // 只有一个相同节点
                    return true;
                }
            } else {
                return false;
            }
        }
        
        if (circuit[0] != circuit[circuit.size() - 1]) {
            // 首尾不一样
            return false;
        }
        
        if (circuit.size() < vertexes.size() + 1) {
            // 数量小于图中定点数目+1，不能反悔原点
            return false;
        }
        
        unordered_map<int, bool> visited;
        for (int i = 1; i < circuit.size(); i++) {
            int vId = circuit[i];
            if (visited.find(vId) != visited.end()) {
                return false;
            }
            auto& v = vertexes.at(vId);
            int lastVId = circuit[i - 1];
            if (v.edges.find(lastVId) == v.edges.end()) {
                // 没有边相连
                return false;
            }
            visited[vId] = true;
        }
        
        bool isHamilton = true;
        for (auto iter = vertexes.begin(); iter != vertexes.end(); iter++) {
            auto vId = iter->first;
            if (visited.find(vId) == visited.end()) {
                // 有顶点没有遍历到
                isHamilton = false;
                break;
            }
        }
        return isHamilton;
    }
private:
    unordered_map<int, Vertex> vertexes;
};

int main(int argc, const char * argv[]) {
//    freopen("HamiltonCircuit.txt", "r", stdin);
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
        vertexes.resize(num);
        
        for (int j = 0; j < num; j++) {
            int vId = 0;
            cin >> vId;
            vertexes[j] = vId;
        }
        
        if (g.isHamiltonCircuit(vertexes)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}

