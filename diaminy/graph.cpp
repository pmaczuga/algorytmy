#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <limits>
#include <ctime>
#include <chrono>

using namespace std;

enum Field { Wall = 1, Jewel, Mine, Hole, Empty };
struct Vector2{
    int x;
    int y;
    Vector2() : x(0), y(0) { };
    Vector2(int _x, int _y) : x(_x), y(_y) { };
    int hash() const { return ((x + y) * (x + y + 1)) / 2 + x; };
    bool operator<(Vector2 other) const { return this->hash() < other.hash(); };
};

bool logged = false;
const string NO_SOL = "BRAK";

int height;
int width;
int maxMoves;
int allJewelsCount = 0;
int maxJewelsInRow = 0;
Vector2 player;
vector <Vector2> jewelsPositions;
Field maze[200][200];


// -----------------------GRAPH----------------------------------
struct State { int movesLeft; int jewelsLeft; };
struct Edge { int dir; int neighbour; vector <int> jewels; int jewelsCount; };
struct Vertex { int id; State state; vector <Edge *> edges;};
struct Graph { vector <Vertex *> vertexes; };

Graph *initGraph() {
    Graph *G = new Graph();
    return G;
}

int addVertex(Graph *G) {
    int id = G->vertexes.size();
    State state;
    state.movesLeft = 0;
    state.jewelsLeft = numeric_limits<int>::max();
    Vertex *vertex = new Vertex;
    vertex->id = id;
    vertex->state = state;
    G->vertexes.push_back(vertex);
    return id;
}

Edge *addEdge(Graph *G, int from, int to, int dir, vector <int> jewels) {
    Edge *edge = new Edge;
    edge->dir = dir;
    edge->neighbour = to;
    edge->jewels = jewels;
    edge->jewelsCount = jewels.size();
    G->vertexes[from]->edges.push_back(edge);
    return edge;
}

void printGraph(Graph *G) {
    cout << endl << "GRAPH: " << endl;
    for(auto & vertex : G->vertexes) {
        cout << vertex->id;
        for(auto & edge : vertex->edges) {
            cout << "    " << edge->neighbour << " - dir: " << edge->dir << ", jewels: (";
            for (auto & jewel : edge->jewels) {
                cout << jewel << ", ";
            }
            cout << ")";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void printGraphNicer(Graph *G) {
    cout << endl << "NICER GRAPH: " << endl;
    cout << "digraph G {" << endl;
    for(auto & vertex : G->vertexes) {
        for(auto & edge : vertex->edges) {
            cout << vertex->id << " -> " << edge->neighbour;
            if (edge->jewelsCount > 0) {
                cout << " [ color=\"0.0 1.0 1.0\" ]";
            }
            cout << ";" << endl;
        }
    }
    cout << "}";
    cout << endl << endl;
}

void removeGraph(Graph *G) {
    for (auto & vertex : G->vertexes) {
        for (auto & edge : vertex->edges) {
            free(edge);
        }
        free(vertex);
    }
    free(G);
};
//----------------------GRAPH-END--------------------------------

void init(istream &instream) {
    char character;

    instream >> height;
    instream >> width;
    instream >> maxMoves;

    instream >> noskipws >> character; // skip endline

    int x = 0;
    int y = 0;
    while (!instream.eof()) {
        if (y == height) break;

        instream >> noskipws >> character;

        switch (character) {
            case '#':
                maze[x][y] = Wall;
                x++;
                break;
            case '+':
                maze[x][y] = Jewel;
                jewelsPositions.emplace_back(x, y);
                allJewelsCount++;
                x++;
                break;
            case '*':
                maze[x][y] = Mine;
                x++;
                break;
            case 'O':
                maze[x][y] = Hole;
                x++;
                break;
            case ' ':
                maze[x][y] = Empty;
                x++;
                break;
            case '.':
                maze[x][y] = Empty;
                player = Vector2(x, y);
                x++;
                break;
            case '\n':
                x = 0;
                y++;
                break;
            default:
                break;
        }
    }
}

int positionToInt(Vector2 pos) {
    return pos.y * width + pos.x;
}

Vector2 directionToVector2(int direction) {
    switch (direction) {
        case 0:
            return {0, -1};
        case 1:
            return {1, -1};
        case 2:
            return {1, 0};
        case 3:
            return {1, 1};
        case 4:
            return {0, 1};
        case 5:
            return {-1, 1};
        case 6:
            return {-1, 0};
        case 7:
            return {-1, -1};
    }
    return {0, 0};
}

bool compare_edges (Edge *first, Edge *second)
{
    return first->jewelsCount > second->jewelsCount;
}

Graph *prepareGraph() {
    Graph *G = initGraph();
    int jewelsCount = 0;
    map <Vector2, int> jewelId;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            addVertex(G);
            // if there is Jewel - add to ID map (pos -> id)
            if (maze[x][y] == Jewel) {
                jewelId[Vector2(x, y)] = jewelsCount;
                jewelsCount++;
            }
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (maze[x][y] == Empty || maze[x][y] == Hole || maze[x][y] == Jewel) {
                for (int dirAsInt = 0; dirAsInt < 8; dirAsInt++) {
                    int newX = x;
                    int newY = y;
                    bool mineExplodedAndDestroyedOurWholeUniverse = false;
                    Vector2 direction = directionToVector2(dirAsInt);
                    vector <int> jewelsOnPath;

                    // if there is wall in next position - continue - we would stay where we are
                    if (maze[x + direction.x][y + direction.y] == Wall) {
                        continue;
                    }
                    // if we are out of the maze - continue
                    if (x + direction.x < 0 || x + direction.x >= width || y + direction.y < 0 || y + direction.y >= height) {
                        continue;
                    }

                    while(maze[newX + direction.x][newY + direction.y] != Wall) {
                        if (newX + direction.x < 0 || newX + direction.x >= width || newY + direction.y < 0 || newY + direction.y >= height) {
                            break;
                        }

                        newX = newX + direction.x;
                        newY = newY + direction.y;

                        if (maze[newX][newY] == Jewel) {
                            jewelsOnPath.push_back(jewelId[Vector2(newX, newY)]);
                        } else if (maze[newX][newY] == Hole) {
                            break;
                        } else if (maze[newX][newY] == Mine) {
                            mineExplodedAndDestroyedOurWholeUniverse = true;
                            break;
                        }
                    }

                    if (!mineExplodedAndDestroyedOurWholeUniverse) {
                        int thisVertex = positionToInt(Vector2(x, y));
                        int neighbourVertex = positionToInt(Vector2(newX, newY));
                        addEdge(G, thisVertex, neighbourVertex, dirAsInt, jewelsOnPath);
                        if (jewelsOnPath.size() > maxJewelsInRow) maxJewelsInRow = jewelsOnPath.size();
                    }
                }
            }
        }
    }

    // sort edges by number of jewels
//    for (auto & vertex : G->vertexes) {
//        vertex->edges.sort(compare_edges);
//    }
//
    return G;
}

bool implementationSearchDFS(Graph *G, Vertex *start, Vertex *vertexToFind, bool stopAfterJewel, bool *visited) {
    if (start == vertexToFind) {
        return true;
    }
    visited[start->id] = true;
    for (auto & edge : start->edges) {
        if (edge->jewelsCount > 0 && stopAfterJewel) {
            return true;
        }
        if (visited[edge->neighbour]) {
            continue;
        }
        if (implementationSearchDFS(G, G->vertexes[edge->neighbour], vertexToFind, stopAfterJewel, visited)) {
            return true;
        }
    }
    return false;
}

bool searchDFS(Graph *G, Vertex *start, Vertex *vertexToFind, bool stopAfterJewel) {
    bool *visited = new bool[G->vertexes.size()];
    for (int i = 0; i < G->vertexes.size(); i++) {
        visited[i] =false;
    }
    bool result = implementationSearchDFS(G, start, vertexToFind, stopAfterJewel, visited);
    delete[] visited;
    return result;
}

void removeUselessSubgraphs(Graph *G, int startVertexAsInt) {
    Vertex *startVertex = G->vertexes[startVertexAsInt];
    for (auto & vertex : G->vertexes) {
        for (int i = 0; i < vertex->edges.size(); i++) {
            Edge *firstRemovedEdge = vertex->edges.back();
            Edge *secondRemovedEdge = NULL;
            if (firstRemovedEdge->jewelsCount >0) {
                continue;
            }
            vertex->edges.pop_back();

            Vertex *neighbour = G->vertexes[firstRemovedEdge->neighbour];
            for (int j = 0; j< neighbour->edges.size(); j++) {
                Edge *neighbourEdge = neighbour->edges[j];
                if (neighbourEdge->neighbour == vertex->id && neighbourEdge->jewelsCount == 0) {
                    secondRemovedEdge = neighbourEdge;
                    neighbour->edges.erase(neighbour->edges.begin() + j);
                    break;
                }
            }

            bool canBeRemoved = true;
            if (searchDFS(G, startVertex, vertex, false)) {
                if (searchDFS(G, neighbour, startVertex, true)) {
                    canBeRemoved = false;
                }
            } else {
                if (searchDFS(G, vertex, NULL, true)) {
                    canBeRemoved = false;
                }
            }

            if (!canBeRemoved) {
                vertex->edges.insert(vertex->edges.begin(), firstRemovedEdge);
                if (secondRemovedEdge) {
                    neighbour->edges.insert(neighbour->edges.begin(), secondRemovedEdge);
                }
            }
            else if (logged) {
                cout << "Removed edge: " << vertex->id << " -> " << neighbour->id << endl;
                if (secondRemovedEdge) {
                    cout << "Removed edge: " << neighbour->id << " -> " << vertex->id << endl;
                }
            }
        }
    }
}

string solveRecursive(Graph *G, int pos, int previousPos, int jewelsLeft, int movesLeft, bool foundJewels[]) {
    if (jewelsLeft == 0) {
        return "";
    }
    if (movesLeft == 0) {
        return NO_SOL;
    }

    // if there are not enough moves to collect remaining jewels - we lost
    if (movesLeft * maxJewelsInRow < jewelsLeft) {
        return NO_SOL;
    }

    // if we are in worse state than before - no point checking further
    State state = G->vertexes[pos]->state;
    if (jewelsLeft >= state.jewelsLeft && movesLeft <= state.movesLeft) {
        return NO_SOL;
    }

    // if we are in definitely better state - update
    if (jewelsLeft <= state.jewelsLeft && movesLeft >= state.movesLeft) {
        G->vertexes[pos]->state.movesLeft = movesLeft;
        G->vertexes[pos]->state.jewelsLeft = jewelsLeft;
    }

    int removedJewels[maxJewelsInRow];
    int sizeOfRemovedJewels = 0;
    for (auto & edge : G->vertexes[pos]->edges) {

        // there is no point in going back if we found no jewels
        if (edge->neighbour == previousPos && edge->jewelsCount == 0) {
            continue;
        }

        // mark jewels on that edge
        sizeOfRemovedJewels = 0;
        for (auto & jewel : edge->jewels) {
            if (!foundJewels[jewel]) {
                removedJewels[sizeOfRemovedJewels] = jewel;
                sizeOfRemovedJewels++;
                edge->jewelsCount--;
                foundJewels[jewel] = true;
            }
        }

        // find solution going through that edge
        string sol = solveRecursive(G, edge->neighbour, pos, jewelsLeft - sizeOfRemovedJewels, movesLeft - 1, foundJewels);
        if (sol != NO_SOL) {
            return to_string(edge->dir) + sol;
        }

        // no solution - unmark jewels
        for (int i = 0; i < sizeOfRemovedJewels; i++) {
            foundJewels[removedJewels[i]] = false;
            edge->jewelsCount++;
        }
    }

    return NO_SOL;
}

string solve() {
    Graph *G = prepareGraph();
    if (logged) printGraph(G); printGraphNicer(G);

    removeUselessSubgraphs(G, positionToInt(player));

    bool foundJewels[allJewelsCount];
    for (int i = 0; i < allJewelsCount; i++) foundJewels[i] = false;
    string sol = solveRecursive(G, positionToInt(player), positionToInt(player), allJewelsCount, maxMoves, foundJewels);

    removeGraph(G);

    return sol;
}

void print_maze() {
    cout << endl << "MAZE: " << endl;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch (maze[x][y]) {
                case Wall:
                    cout << "#";
                    break;
                case Empty:
                    cout << " ";
                    break;
                case Mine:
                    cout << "*";
                    break;
                case Jewel:
                    cout << "+";
                    break;
                case Hole:
                    cout << "O";
                    break;
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    int firstArg = 1;
    if (argc >= 2 && string(argv[1]) == "-l"){ logged = true; firstArg = 2; }

    if (argc < 2 || (logged && argc < 3)) {
        init(cin);
    } else {
        ifstream instream(argv[firstArg]);
        init(instream);
    }

    if (logged) print_maze();

    auto start = chrono::system_clock::now();

    // ------------------------------------
    // ----------SOLVE-MAZE----------------
    string sol = solve();
    // ------------------------------------

    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;

    if (logged) cout << "---> ";
    cout << sol;
    if (logged) cout << " <--- " << endl;
    if (argc >= 3 || (logged && argc >= 4)) {
        ofstream os;
        os.open(argv[firstArg + 1]);
        os << sol;
        os.close();
    }
    if (logged) cout << "Time: " << elapsed_seconds.count();

    return 0;
}
