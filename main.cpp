#include <iostream>
#include "graph.hpp"

using namespace std;

// graph implementation
int main() {
    // graph edges array.
    graphEdge edges[] = {
        // (x, y, w) -> edge from x to y with weight w
        {0,0,6}, {0,1,3}, {0,2,1}, {0,3,10}, {0,4,6}, {0,5,5}, {1,4,6}, {4,1,3}, {2,1,3}, {2,3,10}
    };

    // Number of vertices in the graph
    int N = 6;

    // calculate number of edges
    int n = sizeof(edges)/sizeof(edges[0]);

    // construct graph
    DiaGraph diagraph(edges, n, N);

    cout << "Prosze wybrac zadanie do wykonania:" << endl << "1. Lista sasiedztwa" <<
    endl << "2. Wszystkie wierzcholki, ktore sa sasiadami kazdego wierzcholka" <<
    endl << "3. Stopnie wychodzace" << endl << "4. Stopnie wchodzace" << endl << "5. Wszystkie wierzcholki izolowane" <<
    endl << "6. Wszystkie petle" << endl << "7. Wszystkie krawedzie dwukierunkowe" << endl;

    int choice, degIn, degOut;
    cin >> choice;

    switch(choice) {
        case 1:
            for (int i = 0; i < N; i++)
                displayAdjList(diagraph.head[i], i);
        break;

        case 2:
            everyVertexAdjacent(diagraph, N);
        break;

        case 3:
            for (int i = 0; i < N; i++) {
                degOut = displayVertexDegOut(diagraph.head[i]);
                cout << endl << "Stopien wychodzacy wierzcholka " << i << ": " << degOut;
            }
        break;

        case 4:
            displayVertexDegIn(edges, n, N);
        break;

        case 5:
            displaySepVertices(diagraph, N);
        break;

        case 6:
            for (int i = 0; i < N; i++)
                displayLoops(diagraph.head[i], i);
        break;

        case 7:
            twoDirectEdges(diagraph, N);
        break;
    }

    return 0;
}
