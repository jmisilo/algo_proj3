#include <iostream>
#include "graph.hpp"

using namespace std;

// graph implementation
int main() {
    vector<edge> edges= { {0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {0,5}, {1,4}, {2,1}, {2,3}, {4,1} };
	vector<int> vertices= { 0,1,2,3,4,5 };

	DiGraph graph = DiGraph(edges, vertices);

    cout << "Prosze wybrac zadanie do wykonania:" << endl << "1. Lista sasiedztwa" <<
    endl << "2. Wszystkie wierzcholki, ktore sa sasiadami kazdego wierzcholka" <<
    endl << "3. Stopnie wychodzace" << endl << "4. Stopnie wchodzace" << endl << "5. Wszystkie wierzcholki izolowane" <<
    endl << "6. Wszystkie petle" << endl << "7. Wszystkie krawedzie dwukierunkowe" << endl;

    int choice;
    cin >> choice;

    switch(choice) {
        case 1:
            graph.displayAdj();
        break;

        case 2:
            graph.everyVerAdj();
        break;

        case 3:
            graph.degOut();
        break;

        case 4:
            graph.degIn();
        break;

        case 5:
            graph.sepVertices();
        break;

        case 6:
            graph.disLoops();
        break;

        case 7:
            graph.twoDirEdges();
        break;
    }

    return 0;
}
