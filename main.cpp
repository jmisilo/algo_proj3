// https://www.softwaretestinghelp.com/graph-implementation-cpp/amp/?fbclid=IwAR25tR-sQQUZrWyoj0AdvHsAzdNvmwmVeiqyPrnMna1aBr4kwIpK1Cg47zI#C_Graph_Implementation_Using_Adjacency_List
#include <iostream>

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
        cout << "(" << i << ", " << ptr->val << ", " << ptr->cost << ") ";
        ptr = ptr->next;
    }
    cout << endl;
}

void displayVertexDegOut(adjNode* ptr, int i) {
    int deg = 0;

    while (ptr != nullptr) {
        ptr = ptr->next;
        deg++;
    }

    cout << endl << "Stopien wychodzacy wierzcholka " << i << ": " << deg << endl;
}

void displayVertexDegIn(DiaGraph graph, int i, int n, int N) {
    adjNode* ptr;
    int vertexesIn [n];

    int counter = 0;
    for (int j = 0; j < N; j++) {
        ptr = graph.head[j];

        while (ptr != nullptr) {
            if (i == ptr->val) counter++;

            ptr = ptr->next;
        }
    }

    cout << "Stopien wchodzacy wierzcholka " << i << ": " << counter << endl;
}

void displayLoops(adjNode* ptr, int i) {
    cout << "Petle wierzcholka " << i << ":" << endl;
    while (ptr != nullptr) {
        if (i == ptr->val)
            // (start_vertex, end_vertex, weight)
            cout << "(" << i << ", " << ptr->val << ", " << ptr->cost << ") ";
            ptr = ptr->next;
    }
}

// graph implementation
int main() {
    // graph edges array.
    graphEdge edges[] = {
        // (x, y, w) -> edge from x to y with weight w
        {0,1,2}, {0,2,4}, {1,4,3}, {1,1,1}, {2,3,2}, {3,1,4}, {4,3,3}
    };

    // Number of vertices in the graph
    int N = 5;

    // calculate number of edges
    int n = sizeof(edges)/sizeof(edges[0]);

    // construct graph
    DiaGraph diagraph(edges, n, N);

    // print adjacency list representation of graph
    cout<<"Graph adjacency list "<<endl<<"(start_vertex, end_vertex, weight):"<<endl;

    for (int i = 0; i < N; i++) {
        // display adjacent vertices of vertex i
        displayAdjList(diagraph.head[i], i);
        displayLoops(diagraph.head[i], i);
        displayVertexDegOut(diagraph.head[i], i);
        displayVertexDegIn(diagraph, i, n, N);
    }

    return 0;
}
