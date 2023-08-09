#include <vector>
#include <iostream>
using namespace std;

//! @return true if the graph is bipartite, i.e. the nodes can be partitioned 
//!         into two independent sets A and B such that every edge in the 
//!         graph connects a node in set A and a node in set B.
//! @param graph a graph where graph[u] stores the nodes adjacent to u.
//! @author Nhut Nguyen
bool isBipartite(vector<vector<int>>& graph) {
    vector<int> color(graph.size(), 0);
    for (int i = 0; i < graph.size(); i++) {
        if (color[i] != 0) continue;
        vector<int> s;
        s.push_back(i);
        color[i] = 1;
        while (!s.empty()) {
            int u = s.back();
            s.pop_back();
            for (int v : graph[u]) {
                if (color[v] == 0) {
                    color[v] = -color[u];
                    s.push_back(v);
                } else if (color[v] == color[u]) {
                    return false;
                }          
            }
        }

    }
    return true;
}

int main() {
    vector<vector<int>> graph{{1,2,3},{0,2},{0,1,3},{0,2}};
    cout << isBipartite(graph) << endl;
    graph = {{1,3},{0,2},{1,3},{0,2}};
    cout << isBipartite(graph) << endl;
}