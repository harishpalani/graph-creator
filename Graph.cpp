#include "Graph.h"
 
using namespace std;

Graph::Graph() : INFINITY(numeric_limits<int>::max()) {}
Graph::~Graph() {}

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
    if (index(content, c1) == -1 || index(content, c2) == -1) { return false; }
    
    /* vector<int> sub = *adjacencyMatrix[index(content, c1)];
    sub[index(content, c2)] = weight;*/
    (*adjacencyMatrix[index(content, c1)])[index(content, c2)] = weight;
    
    return true;
}

bool Graph::removeEdge(const char* c1, const char* c2) {
    // If either is nonexistent, exit
    if (index(content, c1) == -1 || index(content, c2) == -2) { return false; }
    
    vector<int> sub = *adjacencyMatrix[index(content, c1)];
    sub[index(content, c2)] = -1;
    
    return true;
}

void Graph::printMatrix() {
    int max = 0;
    for (int i = 0; i < content.size(); i++) {
        int length = strlen(content[i]);
        if (length > max) {
            max = length;
        }
    }
    
    for (int i = 0; i < max + 1; i++) { cout << ' '; }
    for (int i = 0; i < content.size(); i++) { cout << content[i] << ' '; }
    cout << endl;
    
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        cout << content[i];
        for (int k = 0; k < max - strlen(content[i]) + 1; k++) {
            cout << ' ';
        }       
        for (int j = 0; j < content.size(); j++) {
            if ((*adjacencyMatrix[i])[j] >= 0) {
                cout << (*adjacencyMatrix[i])[j];
            } else { cout << 'X'; }
            for (int k = 0; k < strlen(content[j]); k++) {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

void Graph::pathPrint(const char* c1, const char* c2) {
    pair<vector<char*>, int> pair = findShortestPath(c1, c2);
    if (pair.second == -1) {
        cout << "Status: FAILED. Vertices not found." << endl;
        return;
    }
    
    if (pair.second == INFINITY) {
        cout << "Status: FAILED. Path nonexistent." << endl;
        return;
    }
    
    cout << "Path: " << pair.first[0];
    delete[] pair.first[0];
    for (int i = 1; i < pair.first.size(); i++) {
        cout << " > " << pair.first[i];
        delete[] pair.first[i];
    }
    cout << " | " << "Distance: " << pair.second << endl;
}

pair<vector<char*>, int> Graph::findShortestPath(const char* c1, const char* c2) {
    // If the path DNE, pair.second = INFINITY
    pair<vector<char*>, int> node;
    
    // If at least one of the vertices DNE...
        // pair.second = -1
    if (index(content, c1) == -1 || index(content, c2) == -1) {
        node.second = -1;
        return node;
    }
    
    int unique[content.size()];
    vector< pair<vector<char*>, int> > nodes;
    for (int i = 0; i < content.size(); i++) {
        unique[i] = true;
        nodes.push_back(pair<vector<char*>, int>());
        nodes[nodes.size()-1].second = INFINITY;
    }
    
    unique[index(content, c1)] = false;
    nodes[index(content, c1)].second = 0;
    nodes[index(content, c1)].first.push_back(strcpy(new char[strlen(content[index(content, c1)]) + 1], content[index(content, c1)]));
    int current = index(content, c1);
    
    while (true) {
        for (int i = 0; i < content.size(); i++) {
            if ((*adjacencyMatrix[current])[i] != -1 && unique[i]) {
                int distance = nodes[current].second + (*adjacencyMatrix[current])[i];
                if (distance < nodes[i].second) {
                    nodes[i].second = distance;
                    // copyPath(, );
                    for (int j = 0; j < nodes[i].first.size(); j++) {
                        delete[] nodes[i].first[j];
                    }
                    nodes[i].first.clear();
                    for (int j = 0; j < nodes[current].first.size(); j++) {
                        nodes[i].first.push_back(strcpy(new char[strlen(nodes[current].first[j]) + 1], nodes[current].first[j]));
                    }
                    
                    nodes[i].first.push_back(strcpy(new char[strlen(content[i]) + 1], content[i]));
                }
            }
        }
        
        unique[current] = false;
        if (unique[index(content, c2)] == false) {
            for (int i = 0; i < content.size(); i++) {
                if (i != index(content, c2)) {
                    for (int j = 0; j < nodes[i].first.size(); j++) {
                        delete[] (nodes[i].first)[j];
                    }
                }
            }
            return nodes[index(content, c2)];
        }
        
        bool noPath = true;
        for (int i = 0; i < content.size(); i++) {
            if (unique[i] && nodes[i].second != INFINITY) {
                noPath = false;
                break;
            }
        }
        
        if (noPath) {
            for (int i = 0; i < content.size(); i++) {
                for (int j = 0; j<nodes[i].first.size(); j++) {
                    delete[] (nodes[i].first)[j];
                }
            }
            return nodes[index(content, c2)];
        }
        
        int smallest = INFINITY;
        for (int i = 0; i < content.size(); i++) {
            if (unique[i] && nodes[i].second < smallest) {
                smallest = nodes[i].second;
                current = i;
            }
        }
    }
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