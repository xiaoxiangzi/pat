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
    bool hasEdges;
    unordered_map<int, bool> edges;
};

class Graph {
    
public:
    void readGraph(int n, int m) {
        for (int i = 1; i <= n; i++) {
            Vertex v;
            v.id = i;
            v.hasEdges = false;
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
            v1.hasEdges = true;
            v2.hasEdges = true;
        }
    }
    
    bool canConquer(const unordered_map<int, bool>& cities) {
        if (cities.empty()) {
            return true;
        }
        
        if (cities.size() == 1) {
            return true;
        }
        
        bool can = true;
        for (auto iter = _vertexes.begin(); iter != _vertexes.end(); iter++) {
            auto& v = iter->second;
            if (cities.find(v.id) == cities.end()) {
                v.hasEdges = v.edges.size() > 0;
                removeEdgesOfCities(v, cities);
                if (v.hasEdges) {
                    can = false;
                    break;
                }
            }
            
        }
        
        return can;
    }
private:
    void removeEdgesOfCities(Vertex& v, const unordered_map<int, bool>& cities) {
        int delCount = 0;
        int edgesSize = (int)v.edges.size();
        for (auto cityIter = cities.begin(); cityIter != cities.end(); cityIter++) {
            int city = cityIter->first;
            auto iter = v.edges.find(city);
            if (iter != v.edges.end()) {
                delCount++;
                if (delCount == edgesSize) {
                    break;
                }
            }
        }
        
        if (delCount == edgesSize) {
            v.hasEdges = false;
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
        unordered_map<int, bool> vertexes;
        
        for (int j = 0; j < num; j++) {
            int vId = 0;
            cin >> vId;
            vertexes[vId] = true;
        }
        
        if (g.canConquer(vertexes)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}


