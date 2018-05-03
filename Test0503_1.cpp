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
    unordered_map<int, bool> edges;
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
            v1.edges[v2Id] = true;
            v2.edges[v1Id] = true;
        }
    }
    
    bool canConquer(const vector<int>& cities) {
        unordered_map<int, Vertex> vertexes = _vertexes;
        if (cities.empty()) {
            return true;
        }
        
        if (cities.size() == 1) {
            return true;
        }
        
        for (int i = 0; i < cities.size(); i++) {
            auto iter = vertexes.find(cities[i]);
            if (iter != vertexes.end()) {
                vertexes.erase(iter);
            }
        }
        
        for (auto iter = vertexes.begin(); iter != vertexes.end(); iter++) {
            auto& v = iter->second;
            removeEdgesOfCities(v, cities);
        }
        
        bool can = true;
        for (auto iter = vertexes.begin(); iter != vertexes.end(); iter++) {
            auto& v = iter->second;
            if (!v.edges.empty()) {
                can = false;
                break;
            }
        }
        return can;
    }
private:
    void removeEdgesOfCities(Vertex& v, const vector<int>& cities) {
        for (int i = 0; i < cities.size(); i++) {
            auto iter = v.edges.find(cities[i]);
            if (iter != v.edges.end()) {
                v.edges.erase(iter);
                if (v.edges.empty()) {
                    break;
                }
            }
        }
    }
    unordered_map<int, Vertex> _vertexes;
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
        vertexes.resize(num);
        
        for (int j = 0; j < num; j++) {
            int vId = 0;
            cin >> vId;
            vertexes[j] = vId;
        }
        
        if (g.canConquer(vertexes)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}


