#include <vector>
#include <iostream>
using namespace std;

void DFS(vector<vector<int>>& graph, vector<vector<int>>& paths, vector<int>& path) {
    for (auto& node : graph[path.back()]) {
        path.push_back(node);
        if (node == graph.size()-1) {
            paths.push_back(path);
            path.pop_back();
        } else {
            DFS(graph, paths, path);
        }
    }
    path.pop_back();
}
vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    vector<vector<int>> paths;
    vector<int> path = {0};
    DFS(graph, paths, path);
    return paths;
}


void printPaths(vector<vector<int>>& paths) {
    cout << "[";
    for (auto& p : paths) {
        cout << "[";
        for (auto& node : p) {
            cout << node << ",";
        }
        cout << "],";
    }
    cout << "]\n";
}
int main() {
    vector<vector<int>> graph = {{1,2},{3},{3},{}};
    auto paths = allPathsSourceTarget(graph);
    printPaths(paths);
    graph = {{4,3,1},{3,2,4},{3},{4},{}};
    paths = allPathsSourceTarget(graph);
    printPaths(paths); 
}
// [[0,1,3,],[0,2,3,],]
// [[0,4,],[0,3,4,],[0,1,3,4,],[0,1,2,3,4,],[0,1,4,],]
