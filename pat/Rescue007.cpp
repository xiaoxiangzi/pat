//
//  Rescue007.cpp
//  pat
//
//  Created by xiaoxiangzi on 2018/4/12.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

struct Vertex {
    int id;
    int x;
    int y;
    vector<int> edges;
};

bool findPathToVertexes(int startId, unordered_map<int, Vertex*>& graph, const unordered_map<int, bool>& dstVertexes) {
    unordered_map<int, bool> visited;
    
    queue<int> q;
    visited[startId] = true;
    q.push(startId);
    while (!q.empty()) {
        int curId = q.front();
        q.pop();
        if (dstVertexes.find(curId) != dstVertexes.end()) {
            return true;
        }
        auto v = graph.at(curId);
        for (int i = 0; i < v->edges.size(); i++) {
            int adjId = v->edges[i];
            if (visited.find(adjId) == visited.end()) {
                visited[adjId] = true;
                q.push(adjId);
            }
        }
    }
    
    return false;
}

bool canRescue007(vector<Vertex>& crocodiles, int jumpDist, const unordered_map<int, bool>& firstChoices, const unordered_map<int, bool>& lastChoices) {
    unordered_map<int, Vertex*> graph;
    for (int i = 0; i < crocodiles.size(); i++) {
        auto& vi = crocodiles[i];
        graph.insert(pair<int, Vertex*>(vi.id, &vi));
        for (int j  = 0; j < crocodiles.size(); j++) {
            if (i != j) {
                auto& vj = crocodiles[j];
                int dist = ceil(sqrt((vi.x - vj.x) * (vi.x - vj.x) + (vi.y - vj.y) * (vi.y - vj.y)));
                if (dist <= jumpDist) {
                    vi.edges.push_back(vj.id);
                    vj.edges.push_back(vi.id);
                }
            }
        }
    }
    
    for (auto iter = firstChoices.begin(); iter != firstChoices.end(); iter++) {
        int vId = iter->first;
        if (findPathToVertexes(vId, graph, lastChoices)) {
            return true;
        }
    }
    
    return false;
}

int calcDistToLand(int x, int y) {
    int minDist = INT32_MAX;
    int distToUp = abs(50 - y);
    if (distToUp < minDist) {
        minDist = distToUp;
    }
    
    int distToBottom = abs(-50 - y);
    if (distToBottom < minDist) {
        minDist = distToBottom;
    }
    
    int distToRight = abs(50 - x);
    if (distToRight < minDist) {
        minDist = distToRight;
    }
    
    int distToLeft = abs(-50 - x);
    if (distToLeft < minDist) {
        minDist = distToLeft;
    }
    
    return minDist;
}

int main(int argc, const char * argv[]) {
//    freopen("Rescue007.txt", "r", stdin);
    int crocodileNum = 0;
    int jumpDistance = 0;
    cin >> crocodileNum >> jumpDistance;
    vector<Vertex> crocodiles;
    unordered_map<int, bool> firstChoices;
    unordered_map<int, bool> lastChoices;
    crocodiles.resize(crocodileNum);
    for (int i = 0 ; i < crocodileNum; i++) {
        Vertex v;
        v.id = i;
        cin >> v.x >> v.y;
        int distFromIsLand = ceil(sqrt(v.x * v.x + v.y * v.y) - 15);
        int distToLand = calcDistToLand(v.x, v.y);
        crocodiles[i] = v;
        if (distFromIsLand <= jumpDistance) {
            firstChoices[i] = true;
        }
        
        if (distToLand <= jumpDistance) {
            lastChoices[i] = true;
        }
    }
    
    if (firstChoices.empty() || lastChoices.empty()) {
        cout << "No" << endl;
    } else {
        if (canRescue007(crocodiles, jumpDistance, firstChoices, lastChoices)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    
    return 0;
}
