//
//  PTA_7_1.cpp
//  PAT
//
//  Created by xiaoxiangzi on 18/4/1.
//  Copyright © 2018年 xiaoxiangzi.com. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <deque>
using namespace std;

struct Vertex {
    int id;
    vector<int> edges;
};

void printVector(const vector<int>& v) {
    cout << "{";
    for (int i = 0; i < v.size(); i++) {
        int vId = v[i];
        cout << " " << vId;
    }
    cout << " }" << endl;
}

bool checkIfExistedInDeque(deque<int>& q, int targetId) {
    for (auto iter = q.begin(); iter != q.end(); iter++) {
        int id = *iter;
        if (id == targetId) {
            return true;
        }
    }
    
    return false;
}

void bfs(const unordered_map<int, Vertex>& graph, int n) {
    unordered_map<int, bool> visited;
    deque<int> scanQueue;
    
    for (int i = 0; i < n; i++) {
        if (visited.find(i) != visited.end()) {
            continue;
        }
        
        vector<int> order;
        scanQueue.push_front(i);
        while (!scanQueue.empty()) {
            int curId = scanQueue.front();
            scanQueue.pop_front();
            visited[curId] = true;
            order.push_back(curId);
            
            auto& curVertex = graph.at(curId);
            for (int j = 0; j <  curVertex.edges.size(); j++) {
                int edgeVertexId = curVertex.edges[j];
                if (visited.find(edgeVertexId) != visited.end()) {
                    continue;
                }
                if (!checkIfExistedInDeque(scanQueue, edgeVertexId)) {
                    scanQueue.push_back(edgeVertexId);
                }
            }
            
        }
        printVector(order);
    }
}

void dfs(const unordered_map<int, Vertex>& graph, int n) {
    unordered_map<int, bool> visited;
    deque<int> scanQueue;
    
    for (int i = 0; i < n; i++) {
        if (visited.find(i) != visited.end()) {
            continue;
        }
        
        vector<int> order;
        scanQueue.push_front(i);
        while (!scanQueue.empty()) {
            int curId = scanQueue.front();
            scanQueue.pop_front();
            visited[curId] = true;
            order.push_back(curId);
            auto& curVertex = graph.at(curId);
            for (int j = (int) curVertex.edges.size() - 1; j >= 0; j--) {
                int edgeVertexId = curVertex.edges[j];
                
                if (visited.find(edgeVertexId) != visited.end()) {
                    continue;
                }
                if (!checkIfExistedInDeque(scanQueue, edgeVertexId)) {
                    scanQueue.push_front(edgeVertexId);
                }
            }
        }
        
        printVector(order);
    }
}

int main(int argc, const char * argv[]) {
//    freopen("PTA_7_1.txt", "r", stdin);
    
    int n = 0;
    int e = 0;
    cin >> n >> e;
    
    unordered_map<int, Vertex> graph;
    for (int i = 0; i < n; i++) {
        Vertex v;
        v.id = i;
        graph.insert(pair<int, Vertex>(i, v));
    }
    
    int start = 0;
    int end = 0;
    for (int i = 0; i < e; i++) {
        cin >> start >> end;
        Vertex& startVertex = graph.at(start);
        Vertex& endVertex = graph.at(end);
        
        startVertex.edges.push_back(end);
        endVertex.edges.push_back(start);
    }
    
    for (int i = 0; i < n; i++) {
        Vertex& v = graph.at(i);
        sort(v.edges.begin(), v.edges.end());
//        printVector(v.edges);
    }
    
    dfs(graph, n);
    bfs(graph, n);
    
    return 0;
}
