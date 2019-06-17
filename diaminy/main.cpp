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

class Vector2 {
public:
    Vector2(int x, int y);

    int getX() { return x; };
    int getY() { return y; };
private:
    int x;
    int y;
};

Vector2::Vector2(int x, int y) : x(x), y(y) {}

class Player {
public:
    Vector2 pos;
    Player(Vector2 pos);
    void setPos(int _x, int _y);
};

Player::Player(Vector2 pos) : pos(pos) { }

void Player::setPos(int x, int y) {
    pos = Vector2(x, y);
}

class Move {
public:
    Vector2 newPos;
    vector <Vector2> jewelsOnPath;
    Move();
    Move(Vector2 pos);
};

Move::Move() : newPos(Vector2(0, 0)) { }
Move::Move(Vector2 pos) : newPos(pos) { }

struct State {
    int movesLeft;
    int jewelsLeft;
};

string noSolString = "BRAK";
int height;
int width;
int maxMoves;
int jewels = 0;
Field maze[200][200];
State fieldState[200][200];
Move movementArray[200][200][8];
Player player(Vector2(0, 0));


void init(string filename) {
    ifstream instream;
    instream.open(filename);
    char character;
    if (instream.is_open()) {

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
                    player.setPos(x, y);
                    x++;
                    break;
                case '\n':
                    x = 0;
                    y++;
                    break;
                default:
                    cout << "Illegal character in " << filename;
                    exit(1);
            }
        }
    }
    instream.close();

    // init fieldState array;
    State quiteBadState;
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
            return Vector2(0, -1);
        case 1:
            return Vector2(1, -1);
        case 2:
            return Vector2(1, 0);
        case 3:
            return Vector2(1, 1);
        case 4:
            return Vector2(0, 1);
        case 5:
            return Vector2(-1, 1);
        case 6:
            return Vector2(-1, 0);
        case 7:
            return Vector2(-1, -1);
    }
    return Vector2(0, 0);
}

void putJewelsBack(list <Vector2> *jewelsToPut) {
    list <Vector2> :: iterator it;
    for (it = jewelsToPut->begin(); it != jewelsToPut->end(); ++it) {
        maze[it->getX()][it->getY()] = Jewel;
    }
}

bool contains(list<Vector2> *iterable, Vector2 el) {
    list <Vector2> :: iterator it;
    for (it = iterable->begin(); it != iterable->end(); ++it) {
        if (it->getX() == el.getX() && it->getY() == el.getY()) {
            return true;
        }
    }
    return false;
}

void prepareMovementArray() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (maze[x][y] == Empty || maze[x][y] == Hole || maze[x][y] == Jewel) {
                for (int i = 0; i< 8; i++) {
                    int newX = x;
                    int newY = y;
                    Vector2 direction = directionToVector2(i);
                    movementArray[x][y][i] = Move();
                    while(maze[newX + direction.getX()][newY + direction.getY()] != Wall) {
                        newX = newX + direction.getX();
                        newY = newY + direction.getY();

                        if (maze[newX][newY] == Jewel) {
                            movementArray[x][y][i].jewelsOnPath.emplace_back(Vector2(newX, newY));
                        } else if (maze[newX][newY] == Hole || maze[newX][newY] == Mine) {
                            break;
                        }
                    }
                    movementArray[x][y][i].newPos = Vector2(newX, newY);
                }
            }
        }
    }
}

string solve_recursive(Vector2 pos, int intDirection, int jewelsLeft, int movesLeft) {
    Vector2 direction = directionToVector2(intDirection);
    list <Vector2> foundJewels;

    // if we don't have more moves - we lost
    if (movesLeft == 0) {
        return noSolString;
    }

    // if we won't move (because of wall) - there is no point checking further
    if (maze[pos.getX() + direction.getX()][pos.getY() + direction.getY()] == Wall)
        return noSolString;

    // make move
    Move *move = &movementArray[pos.getX()][pos.getY()][intDirection];
    pos = move->newPos;
    if (maze[pos.getX()][pos.getY()] == Mine) {
        return noSolString;
    }
    vector <Vector2> :: iterator it;
    for (it = move->jewelsOnPath.begin(); it != move->jewelsOnPath.end(); ++it) {
        if (maze[it->getX()][it->getY()] == Jewel) {
            maze[it->getX()][it->getY()] = Empty;
            jewelsLeft--;
            foundJewels.emplace_back((*it));
        }
    }

//    while(maze[pos.getX() + direction.getX()][pos.getY() + direction.getY()] != Wall) {
//        pos = Vector2(pos.getX() + direction.getX(), pos.getY() + direction.getY());
//
//        if (maze[pos.getX()][pos.getY()] == Mine) {
//            putJewelsBack(&foundJewels);
//            return noSolString;
//        } else if (maze[pos.getX()][pos.getY()] == Jewel) {
//            maze[pos.getX()][pos.getY()] = Empty;
//            jewelsLeft--;
//            foundJewels.push_back(pos);
//        } else if (maze[pos.getX()][pos.getY()] == Hole) {
//            break;
//        }
//    }

    // if we are in worse state than before - checking further is pointless
    State previousState = fieldState[pos.getX()][pos.getY()];
    if (movesLeft < previousState.movesLeft && jewelsLeft > previousState.jewelsLeft) {
        putJewelsBack(&foundJewels);
        return noSolString;
    }

    // if we are in definitely better state - save that to fieldState array
    if (movesLeft > previousState.movesLeft && jewelsLeft < previousState.jewelsLeft) {
        fieldState[pos.getX()][pos.getY()].jewelsLeft = jewelsLeft;
        fieldState[pos.getX()][pos.getY()].movesLeft = movesLeft;
    }

    // if we found all jewels - game is over - we won
    if (jewelsLeft == 0){
        return to_string(intDirection);
    }

    // Try moving in all directions
    for (int i = 0; i < 8; i++) {
        // going back when we didn't find any jewels is pointless
        if (foundJewels.empty() && i == (intDirection + 4) % 8)
            continue;

        string sol = solve_recursive(pos, i, jewelsLeft, movesLeft - 1);
        if (sol != noSolString) {
            return to_string(intDirection) + sol;
        }
    }

    // put back all jewels
    putJewelsBack(&foundJewels);

    return noSolString;
}

string solve() {
    prepareMovementArray();
//    cout << "Done preparing!" << endl;
    for (int i = 0; i < 8; i++) {
        string sol = solve_recursive(player.pos, i, jewels, maxMoves);
        if (sol != noSolString)
            return sol;
    }
    return noSolString;
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
    if (argc < 2) {
        cout << "Wrong number of arguments.\nArguments:\n - filename\n";
        exit(0);
    }

    string filename = argv[1];
    init(filename);

//    print_maze();

    auto start = chrono::system_clock::now();

    // solve maze
    string sol = solve();

    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;

    cout << sol;
    if (argc >= 3) {
        ofstream os;
        os.open(argv[2]);
        os << sol;
        os.close();
    }
//    cout << endl << "Time: " << elapsed_seconds.count();

    return 0;
}
