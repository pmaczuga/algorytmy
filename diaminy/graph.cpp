#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include <ctime>
#include <chrono>

using namespace std;

enum Field { Wall = 1, Jewel, Mine, Hole, Empty };
struct Vector2 { int x; int y; Vector2() : x(0), y(0) { }; Vector2(int _x, int _y) : x(_x), y(_y) {} };
struct State { int movesLeft; int jewelsLeft; };
struct Move { Vector2 newPos; bool valid; vector <Vector2> jewelsOnPath; };

bool logged = false;
string noSolString = "BRAK";

int height;
int width;
int maxMoves;
int jewels;
int maxJewelsInRow = 0;
Vector2 player;
vector <Vector2> jewelsPositions;
Field maze[200][200];
State fieldState[200][200];
Move movementArray[200][200][8];


// -----------------------GRAPH----------------------------------
struct Edge { int dir; int neighbour; vector <int> jewels; };
struct Vertex { int id; list <Edge> edges; };
struct Graph { vector <Vertex> vertexes; };

int addVertex(Graph G) {
    int id = G.vertexes.size();
    Vertex vertex;
    vertex.id = id;
    G.vertexes.push_back(vertex);
}

void addEdge(Graph G, int from, int to, int dir, vector <int> jewels) {
    Edge edge;
    edge.dir = dir;
    edge.neighbour = to;
    edge.jewels = jewels;
    G.vertexes[from].edges.push_back(edge);
}
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
        instream >> noskipws >> character;

        switch (character) {
            case '#':
                maze[x][y] = Wall;
                x++;
                break;
            case '+':
                maze[x][y] = Jewel;
                jewelsPositions.emplace_back(x, y);
                jewels++;
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
                maze[x][y] = Hole;
                player.x = x;
                player.y = y;
                x++;
                break;
            case '\n':
                x = 0;
                y++;
                break;
            default:
                cout << "Illegal character" << endl;
                exit(1);
        }
    }

    // init fieldState array;
    State quiteBadState{};
    quiteBadState.jewelsLeft = numeric_limits<int>::max();
    quiteBadState.movesLeft = 0;
    for (int i = 0;i < 200; i++) {
        for (int j = 0; j < 200; j++) {
            fieldState[i][j] = quiteBadState;
        }
    }
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

void prepareMovementArray() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (maze[x][y] == Empty || maze[x][y] == Hole || maze[x][y] == Jewel) {
                for (int i = 0; i< 8; i++) {
                    int newX = x;
                    int newY = y;
                    int jewelsInRow = 0;
                    Vector2 direction = directionToVector2(i);
                    movementArray[x][y][i] = Move();
                    while(maze[newX + direction.x][newY + direction.y] != Wall) {
                        newX = newX + direction.x;
                        newY = newY + direction.y;

                        if (maze[newX][newY] == Jewel) {
                            movementArray[x][y][i].jewelsOnPath.push_back(Vector2(newX, newY));
                            jewelsInRow++;
                        } else if (maze[newX][newY] == Hole || maze[newX][newY] == Mine) {
                            break;
                        }
                    }
                    movementArray[x][y][i].newPos = Vector2(newX, newY);
                    if (jewelsInRow > maxJewelsInRow) maxJewelsInRow = jewelsInRow;
                }
            }
        }
    }
}

string solveRecursive(Vector2 pos, int jewelsLeft, int movesLeft) {
    if (jewelsLeft == 0) {
        return "";
    }
    if (movesLeft == 0) {
        return noSolString;
    }

    for (int dir = 0; dir < 8; dir++) {
        Vector2 newPos
    }
    return noSolString;
}

string solve() {

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
