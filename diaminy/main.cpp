#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

enum Field {
    Wall = 1,
    Jewel,
    Mine,
    Hole,
    Empty
};

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

int height;
int width;
int maxMoves;
int jewels = 0;
Field maze[200][200];
list <Vector2> lastVisited;
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
}

void putJewelsBack(list <Vector2> jewelsToPut) {
    list <Vector2> :: iterator it;
    for (it = jewelsToPut.begin(); it != jewelsToPut.end(); ++it) {
        maze[(*it).getX()][(*it).getY()] = Jewel;
    }
}

bool contains(list<Vector2> iterable, Vector2 el) {
    list <Vector2> :: iterator it;
    for (it = iterable.begin(); it != iterable.end(); ++it) {
        if ((*it).getX() == el.getX() && (*it).getY() == el.getY()) {
            return true;
        }
    }
    return false;
}

string solve_recursive(Vector2 pos, int intDirection, int jewewls_left, int moves_left) {
    Vector2 direction = directionToVector2(intDirection);
    list <Vector2> foundJewels;

    // if we don't have more moves - we lost
    if (moves_left == 0) {
        return "NOSOL";
    }

    // if we can't move - there is no point checking further
    if (maze[pos.getX() + direction.getX()][pos.getY() + direction.getY()] == Wall)
        return "NOSOL";

    while(maze[pos.getX() + direction.getX()][pos.getY() + direction.getY()] != Wall) {
        pos = Vector2(pos.getX() + direction.getX(), pos.getY() + direction.getY());

        if (maze[pos.getX()][pos.getY()] == Mine) {
            putJewelsBack(foundJewels);
            return "NOSOL";
        } else if (maze[pos.getX()][pos.getY()] == Jewel) {
            maze[pos.getX()][pos.getY()] = Empty;
            jewewls_left--;
            foundJewels.push_back(pos);
            // clear lastVisited list - if we found jewel going back is not pointless
            lastVisited.clear();
        } else if (maze[pos.getX()][pos.getY()] == Hole) {
            break;
        }
    }

    // if we are in the same position as we used to be - checking further is pointless
    if (contains(lastVisited, pos)) {
        return "NOSOL";
    }
    // add new position to last visited list
    lastVisited.push_back(pos);

    // if we found all jewels - game is over - we won
    if (jewewls_left == 0){
        return to_string(intDirection);
    }

    // Try moving in all directions
    for (int i = 0; i < 8; i++) {
        // going back when we didn't find any jewels is pointless
        if (foundJewels.empty() && i == (intDirection + 4) % 8)
            continue;

        string sol = solve_recursive(pos, i, jewewls_left, moves_left - 1);
        if (sol != "NOSOL") {
            return to_string(intDirection) + sol;
        }
    }

    // put back all jewels
    putJewelsBack(foundJewels);
    // pop last visited position
    if (!lastVisited.empty())
        lastVisited.pop_back();
    return "NOSOL";
}

string solve() {
    for (int i = 0; i < 8; i++) {
        string sol = solve_recursive(player.pos, i, jewels, maxMoves);
        if (sol != "NOSOL")
            return sol;
    }
    return "NOSOL";
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

    print_maze();

    cout << solve();

    return 0;
}
