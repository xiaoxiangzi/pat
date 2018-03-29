//
//  Test0329.cpp
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

struct Vertex {
    int id;
    vector<int> edges;
};

void printVector(const vector<int>& v) {
    cout << "{";
    for (int i = 0; i < v.size(); i++) {
        cout << " " << v[i];
    }
    cout << " }" << endl;
}

bool cmpVertexId (int i,int j) {
    return i > j;
}

void dfs(const unordered_map<int, Vertex>& graph, int n) {
    unordered_map<int, bool> visited;
    deque<int> visitQueue;
    
    for (int id = 0; id < n; id++) {
        if (visited.find(id) != visited.end()) {
            continue;
        }
        
        visitQueue.push_back(id);
        vector<int> order;
        
        while (!visitQueue.empty()) {
            int curId = visitQueue.front();
            visitQueue.pop_front();
            order.push_back(curId);
            visited[curId] = true;
            
            auto& v = graph.at(curId);
            if (v.edges.size() > 0) {
                for (int i = 0; i < v.edges.size(); i++) {
                    int connectId = v.edges.at(i);
                    if (visited.find(connectId) == visited.end()) {
                        visited[connectId] = true;
                        visitQueue.push_front(connectId);
                    }
                }
            }
        }
        
        printVector(order);
    }
}

void bfs(const unordered_map<int, Vertex>& graph, int n) {
    unordered_map<int, bool> visited;
    deque<int> visitQueue;
    
    for (int id = 0; id < n; id++) {
        if (visited.find(id) != visited.end()) {
            continue;
        }
        
        vector<int> order;
        visitQueue.push_back(id);
        order.push_back(id);
        while (!visitQueue.empty()) {
            int curId = visitQueue.front();
            visitQueue.pop_front();
            visited[curId] = true;
            
            auto& v = graph.at(curId);
            if (v.edges.size() > 0) {
                for (int i = (int) v.edges.size() - 1; i >= 0; i--) {
                    int connectId = v.edges.at(i);
                    if (visited.find(connectId) == visited.end()) {
                        visited[connectId] = true;
                        order.push_back(connectId);
                        visitQueue.push_front(connectId);
                    }
                }
            }
        }
        
        printVector(order);
    }
}

int main(int argc, const char * argv[]) {
//    freopen("Test0329.txt", "r", stdin);
    int n;
    int e;
    
    cin >> n >> e;
    unordered_map<int, Vertex> graph;
    
    for (int i = 0; i < n; i++) {
        Vertex v;
        v.id = i;
        graph.insert(pair<int, Vertex>(i, v));
    }
    
    for (int i = 0; i < e; i++) {
        int start;
        int end;
        cin >> start >> end;
        Vertex& startV = graph.at(start);
        startV.edges.push_back(end);
        Vertex& endV = graph.at(end);
        endV.edges.push_back(start);
    }
    
    for (int i = 0; i < n; i++) {
        Vertex& v = graph.at(i);
        if (v.edges.size() > 0) {
            sort(v.edges.begin(), v.edges.end(), cmpVertexId);
        }
    }
    
    dfs(graph, n);
    bfs(graph, n);
    
    return 0;
}
