#include "Graph.h"
 
using namespace std;

bool Graph::addVertex(const char* c) {
    // If the content already exists in the graph, don't return anything
    if (index(content, c) != -1) { return false; }
    content.push_back(strcpy(new char[strlen(c+1)], c));
    
    // Unlink any old vertices
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        adjacencyMatrix[i]->push_back(-1);
    }
    
    // Link the new vertex
    adjacencyMatrix.push_back(new vector<int>);
    for (int i = 0; i < adjacencyMatrix.size(); i++) { // For the number of elements in the graph, unlink
        adjacencyMatrix[adjacencyMatrix.size() - 1]->push_back(-1);
    }
    
    // If successful...
    return true;
}

bool Graph::removeVertex(const char* c) {
    int i = index(content, c);
    // If vertex is nonexistent, exit
    if (i == -1) { return false; }
    
    // delete[] content[i];
    content.erase(content.begin() + i);
    
    // Remove any connections to other vertices + delete the row
    for (int j = 0; j < adjacencyMatrix.size(); j++) {
        adjacencyMatrix[j]->erase(adjacencyMatrix[j]->begin() + i);
    }
    delete adjacencyMatrix[i];
    adjacencyMatrix.erase(adjacencyMatrix.begin() + i);
    
    return true;
}

bool Graph::addEdge(const char* c1, const char* c2, int weight) {
    // If either is nonexistent, exit
    if (index(content, c1) == -1 || index(content, c2) == -2) { return false; }
    
    vector<int> sub = *adjacencyMatrix[index(content, c1)];
    sub[index(content, c2)] = weight;
    
    return true;
}

bool Graph::removeEdge(const char* c1, const char* c2) {
    // If either is nonexistent, exit
    if (index(content, c1) == -1 || index(content, c2) == -2) { return false; }
    
    vector<int> sub = *adjacencyMatrix[index(content, c1)];
    sub[index(content, c2)] = -1;
    
    return true;
}

void printMatrix() {
    
}

// Helpers
int Graph::index(vector<char*> &content, const char* c) { // Gets index of char c within the graph
    for (int i = 0; i < content.size(); i++) {
        if (strcmp(content[i], c) == 0) {
            return i;
        }
    }
    return -1;
}