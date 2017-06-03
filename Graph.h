#ifndef GRAPH_H
#define GRAPH_H

#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Graph {
  public:
    Graph();
    ~Graph();
    bool addVertex(const char* c);
    bool removeVertex(const char* c);
    bool addEdge(const char* c1, const char* c2, int weight);
    bool removeEdge(const char* c1, const char* c2);
    void printMatrix();
    void pathPrint(const char* c1, const char* c2);
    pair<vector<char*>, int> findShortestPath(const char* c1, const char* c2);
    
  private:
    const int INFINITY;
    // Helpers
    int index(vector<char*> &content, const char* c); // Get index of the desired content within the graph
    
    // Variables
    vector<char*> content;
    vector<vector<int>*> adjacencyMatrix;
};

#endif