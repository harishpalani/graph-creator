#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <cstring>

using namespace std;

class Graph {
  public:
    // Graph();
    // ~Graph();
    bool addVertex(const char* c);
    bool removeVertex(const char* c);
    bool addEdge(const char* c1, const char* c2, int weight);
    bool removeEdge(const char* c1, const char* c2);
    void printMatrix();
    
  private:
    // Helpers
    int index(vector<char*> &content, const char* c); // Get index of the desired content within the graph
    // Variables
    vector<char*> content;
    vector<vector<int>*> adjacencyMatrix;
};

#endif