#include "Graph.h"
 
using namespace std;

bool Graph::addVertex(const char* c) {
    
}

bool Graph::removeVertex(const char* c) {
    
}

bool Graph::addEdge(const char* c1, const char* c2) {
    
}

bool Graph::removeEdge(const char* c1, const char* c2) {
    
}

// Helpers
int Graph::index(vector<char*> &content, const char* c) { // Gets index of char c within the graph
    for (int i = 0; i < content.size(); i++) {
        if (strcmp(content[i], c) == 0) {
            return i;
        }
    }
}