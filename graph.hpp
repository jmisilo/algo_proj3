#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct edge {
    int ver_out, ver_in; // wierzcholek wychodzacy, wierzcholek wchodzacy
};

class DiGraph {

    public:
            vector<edge> edges;
            vector<int> vertices;

            int n, N;

            DiGraph(vector<edge> edges, vector<int> vertices) {
                this->edges = edges;
                this->vertices = vertices;
                this->N = this->edges.size();
                this->n = this->vertices.size();
            }

            // 1
            void displayAdj() {
                for (int i=0; i<n; i++) {
                    vector<int> adj = {};

                    for (int j=0; j<N; j++) {

                        if (this->vertices[i] == this->edges[j].ver_out) adj.push_back(edges[j].ver_in);
                    }

                    cout << "Sasiedzi wierzcholka " << this->vertices[i] << ": ";
                    for (int j=0; j<adj.size(); j++ ) cout << adj[j] << ", ";
                    cout << endl;
                }
            }

            // 2
            void everyVerAdj() {
                set<int> vert = {};

                for (int i = 0; i < this->n; i++) {
                    set<int> adj = {};

                    for (edge j: this->edges) {
                        if (j.ver_in == this->vertices[i]) adj.insert(this->vertices[i]);
                    }

                    if(adj.size() >= this->n) vert.insert(this->vertices[i]);
                }

                cout << "Wierzcholki bedace sasiadami kazdego wierzcholka:" << endl;
                for(int i: vert) cout << i << ", ";
            }

            // 3
            void degOut() {
                for (int i=0; i<n; i++) {
                    int degOut = 0;

                    for (int j=0; j<N; j++)
                        if (this->vertices[i] == this->edges[j].ver_out) degOut++;

                    cout << "Stopien wychodzacy wierzcholka " << this->vertices[i] << ": " << degOut << endl;
                }
            }

            // 4
            void degIn() {
                for(int i=0; i<n; i++) {
                    int degIn = 0;

                    for (int j=0; j<N; j++)
                        if (this->vertices[i] == this->edges[j].ver_in) degIn++;

                    cout << "Stopien wchodzacy wierzcholka " << this->vertices[i] << ": " << degIn << endl;
                }
            }

            // 5
            void sepVertices() {
                vector<int> sepVert = {};

                for(int i: this->vertices) {
                    int counter = 0;
                    for(edge j: this->edges) {
                        if(i == j.ver_out) counter++;
                    }

                    if(!counter) sepVert.push_back(i);
                }

                cout << "Wierzcholki izolowane: ";
                for (int i: sepVert) cout << i << ", ";
                cout << endl;
            }

            // 6
            void disLoops() {
                vector<int> loops = {};

                for (edge i: this->edges)
                    if(i.ver_out == i.ver_in)
                        loops.push_back(i.ver_out);

                cout << "Petle:" << endl;
                for (int i: loops) cout << "(" << i << ", " << i << ")" << endl;

            }

            // 7
            void twoDirEdges() {
                vector<edge> twoDir = {};

                for (edge i: this->edges) {
                    for (edge j: this->edges) {
                        if(i.ver_in == j.ver_out && i.ver_out == j.ver_in && i.ver_in != i.ver_out) {
                            vector<int> helper = {j.ver_in, j.ver_out};

                            // dodajemy krawedz tylko jesli krawedz odwrotna nie wystapila w twoDir
                            if (twoDir.size()) {
                                for (edge z: twoDir) {
                                    if (z.ver_out != helper[0] && z.ver_in != helper[1])
                                        twoDir.push_back(j);
                                }
                            } else twoDir.push_back(j);
                        }
                    }
                }

                cout << "Krawedzie dwukierunkowe: " << endl;
                for (edge i: twoDir) cout << "{" << i.ver_out << ", " << i.ver_in << "}" << endl;
            }
};
