/**
 * GRAPH CREATOR
 * Graph creator with breadth first search.
 * 
 * Implementation: Create a program which can create graphs (we are using weighted edge, directed graphs), 
 * and it can search for a path in the graph using breadth-first search. Use an adjacency table for the graph, 
 * which can be printed out. (You may assume that no more than 20 vertices will be in the table.)
 * 
 * (1) Add Vertex: Enter a label for a vertex. Add it to the graph.
 * (2) Add Edge: Enter two node names and a weight (number). Add an edge between them, 
 *      from the first node to the second node. (You would need to create another edge to go both directions.)
 * (3) Remove Vertex: Enter a vertex label and remove it from the graph. Remove all edges to that vertex.
 * (4) Remove Edge: Enter two vertex labels, and remove an edge between them.
 * (5) Find Path: Enter two vertex labels. Starting at the first label, use a breadth-first search to find a path between 
 * the first vertex and the last vertex. Return the shortest path (and total) if it exists, or return that no path exists.
 * 
 * @author Harish Palani
 * @version May 2017
 */

#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph graph;
    while (true) {
        char response;
        cout << "\n1 | Add a vertex\n2 | Add an edge\n3 | Remove a vertex\n4 | Remove an edge\nq | quit" << endl;
        cin >> response;
        
        if (response == '1') {
            char label[16];
            
            cout << "Enter label: ";
            // cin.getline(label, 16);
            cin >> label;
            
            if (graph.addVertex(label)) { cout << "Status: SUCCESS!" << endl; }
            else { cout << "Status: FAILED." << endl; }
        } else if (response == '2') {
            char label1[16], label2[16];
            int weight;
            
            cout << "Enter first label: ";
            // cin.getline(label1, 16);
            cin >> label1;
            
            cout << "Enter second label: ";
            // cin.getline(label2, 16);
            cin >> label2;
            
            cout << "Enter weight: ";
            cin >> weight;
            
            if (graph.addEdge(label1, label2, weight) == true) { cout << "Status: SUCCESS!" << endl; }
            else { cout << "Status: FAILED." << endl; }
        } else if (response == '3') {
            char label[16];
            
            cout << "Enter label: ";
            // cin.getline(label, 16);
            cin >> label;
            
            if (graph.removeVertex(label) == true) { cout << "Status: SUCCESS!" << endl; }
        } else if (response == '4') {
            char label1[16], label2[16];
            int weight;
            
            cout << "Enter first label: ";
            cin.getline(label1, 16);
            cout << "Enter second label: ";
            cin.getline(label2, 16);
            
            if (graph.removeEdge(label1, label2) == true) { cout << "Status: SUCCESS!" << endl; }
            else { cout << "Status: FAILED." << endl; }
        } else {
            break;
        }
    }

    return 0;
}