// https://www.softwaretestinghelp.com/graph-implementation-cpp/amp/?fbclid=IwAR25tR-sQQUZrWyoj0AdvHsAzdNvmwmVeiqyPrnMna1aBr4kwIpK1Cg47zI#C_Graph_Implementation_Using_Adjacency_List
#include <iostream>
#include <vector>

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

int displayVertexDegOut(adjNode* ptr) {
    int deg = 0;

    while (ptr != nullptr) {
        ptr = ptr->next;
        deg++;
    }

    return deg;
}

int displayVertexDegIn(DiaGraph graph, int i, int n, int N) {
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

    return counter;
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

void twoDirectEdges(DiaGraph graph, int n, int N) {
    vector<vector<int>> twoDirEdges;
    vector<int> helper;
    for(int j = 0; j < N; j++) {
        adjNode* ptr = graph.head[j];

        while (ptr != nullptr) {
            adjNode* ptr2 = graph.head[ptr->val];

            while(ptr2 != nullptr) {

                if(ptr2->val == j && ptr->val != j) {
                    helper = {j, ptr->val};
                    twoDirEdges.push_back(helper);
                }
                ptr2 = ptr2->next;
            }

            ptr = ptr->next;
        }
    }

    for(int j = 0; j < twoDirEdges.size(); j++) cout << "(" << twoDirEdges[j][0] << ", " << twoDirEdges[j][1] << ")" << endl;
}

// graph implementation
int main() {
    // graph edges array.
    graphEdge edges[] = {
        // (x, y, w) -> edge from x to y with weight w
        {0,1,2}, {0,2,4}, {1,4,3}, {1,1,1}, {2,3,2}, {3,2,2}, {3,1,4}, {1,3,4}, {4,3,3}, {4, 5, 10}, {4, 6, 7}
    };

    // Number of vertices in the graph
    int N = 7;

    // calculate number of edges
    int n = sizeof(edges)/sizeof(edges[0]);

    // construct graph
    DiaGraph diagraph(edges, n, N);

    // print adjacency list representation of graph
    cout<<"Graph adjacency list "<<endl<<"(start_vertex, end_vertex, weight):"<<endl;
    int degIn, degOut;
    /*
    for (int i = 0; i < N; i++) {
        // display adjacent vertices of vertex i
        cout << endl;
        displayAdjList(diagraph.head[i], i);
        displayLoops(diagraph.head[i], i);
        degOut = displayVertexDegOut(diagraph.head[i]);
        degIn = displayVertexDegIn(diagraph, i, n, N);

        cout << endl << "Stopien wychodzacy wierzcholka " << i << ": " << degOut << endl;
        cout << "Stopien wchodzacy wierzcholka " << i << ": " << degIn << endl;
    }
    displaySepVertices(diagraph, N);
*/
    twoDirectEdges(diagraph, n, N);
    return 0;
}
