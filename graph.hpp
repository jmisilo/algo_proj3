#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// stores adjacency list items
struct adjNode {
    int val, cost;

    adjNode* next;
};

// structure to store edges
struct graphEdge {
    int start_ver, end_ver, weight;
};

class DiaGraph {
    // insert new nodes into adjacency list from given graph
    adjNode* getAdjListNode(int value, int weight, adjNode* head) {
        adjNode* newNode = new adjNode;

        newNode->val = value;
        newNode->cost = weight;

        newNode->next = head;   // point new node to current head

        return newNode;
    }

    int N;  // number of nodes in the graph

    public:
        adjNode **head;                //adjacency list as array of pointers

        // Constructor
        DiaGraph(graphEdge edges[], int n, int N)  {

            // allocate new node
            head = new adjNode*[N]();

            this->N = N;

            // initialize head pointer for all vertices
            for (int i = 0; i < N; ++i) head[i] = nullptr;

            // construct directed graph by adding edges to it
            for (unsigned i = 0; i < n; i++)  {
                int start_ver = edges[i].start_ver;
                int end_ver = edges[i].end_ver;
                int weight = edges[i].weight;
                // insert in the beginning
                adjNode* newNode = getAdjListNode(end_ver, weight, head[start_ver]);

                // point head pointer to new node
                head[start_ver] = newNode;
            }
        }
        // Destructor
        ~DiaGraph() {
            for (int i = 0; i < N; i++) delete[] head[i];

            delete[] head;
        }
};

// print all adjacent vertices of given vertex
void displayAdjList(adjNode* ptr, int i) {
    cout << "Sasiedzi wierzcholka " << i << ":" << endl;

    while (ptr != nullptr) {
        // (start_vertex, end_vertex, weight)
        //cout << "(" << i << ", " << ptr->val << ", " << ptr->cost << ") ";
        cout << ptr->val << ", ";
        ptr = ptr->next;
    }
    cout << endl;
}

int displayVertexDegOut(adjNode* ptr) {
    int deg = 0;

    while (ptr != nullptr) {
        ptr = ptr->next;
        deg++;
    }

    return deg;
}

int displayVertexDegIn(graphEdge edges[], int n, int N) {


    int c;
    for(int z=0; z < N; z++) {
        c = 0;
        for (int j = 0; j < n; j++) {
            //cout << " (" << edges[j].start_ver << ", " << edges[j].end_ver << ", " << edges[j].weight << ") " << endl;
            if(edges[j].end_ver == z) {
            c = c + 1;
            }
        }

        cout << "Stopien wchodzacy wierzcholka " << z << ": " << c << endl;
    }
}

void displayLoops(adjNode* ptr, int i) {
    cout << "Petle wierzcholka " << i << ":" << endl;
    while (ptr != nullptr) {
        if (i == ptr->val)
            // (start_vertex, end_vertex, weight)
            cout << "(" << i << ", " << ptr->val << ", " << ptr->cost << ") ";
            ptr = ptr->next;
    }
    cout << endl;
}

void displaySepVertices(DiaGraph graph, int N) {
    vector<int> vect = {};
    for(int i = 0; i < N; i++) if (displayVertexDegOut(graph.head[i]) == 0) vect.push_back(i);

    if(vect.size() > 0) {
        cout << "Wierzcholki izolowane grafu:" << endl;
        for(int i = 0; i < vect.size(); i++) {
            cout << vect[i];
            if (vect.size() - 1 != i) cout << ", ";
        }
    } else cout << "Graf nie ma wierzcholkow izolowanych." << endl;
}

void twoDirectEdges(DiaGraph graph, int N) {
    vector<vector<int>> twoDirEdges;
    vector<int> helper;

    for(int j = 0; j < N; j++) {
        adjNode* ptr = graph.head[j];

        while (ptr != nullptr) {
            adjNode* ptr2 = graph.head[ptr->val];

            while(ptr2 != nullptr) {

                helper = {ptr->val, j};
                if(ptr2->val == j && ptr->val != j && find(twoDirEdges.begin(), twoDirEdges.end(), helper) == twoDirEdges.end()) {
                    helper = {j, ptr->val};
                    twoDirEdges.push_back(helper);
                }
                ptr2 = ptr2->next;
            }

            ptr = ptr->next;
        }
    }
    cout << "Krawedzie dwukierunkowe:" << endl;
    for(int j = 0; j < twoDirEdges.size(); j++) cout << "(" << twoDirEdges[j][0] << ", " << twoDirEdges[j][1] << ")" << endl;
}

void everyVertexAdjacent(DiaGraph graph, int N) {
    vector<int> adjacents, targets;
    bool isInAdjacents;

    for(int j = 0; j < N; j++) {
        adjNode* ptr = graph.head[j];
        isInAdjacents = false;
        adjacents.clear();
        for(int z = 0; z < adjacents.size(); z++) if(ptr->val == adjacents[z]) isInAdjacents = true;

        while (ptr != nullptr) {
            if(ptr->val != j && !isInAdjacents) adjacents.push_back(ptr->val);

            ptr = ptr->next;
        }

        if(adjacents.size() == N - 1) targets.push_back(j);
    }

    cout << "Wierzcholki bedace sasiadami kazdego innego wierzcholka:" << endl;
    for (int j = 0; j < targets.size(); j++) {
        cout << targets[j];
        if(j != targets.size() - 1) cout << ", ";
    }
}