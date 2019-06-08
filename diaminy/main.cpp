#include <iostream>
#include <fstream>

using namespace std;

enum Field {
    Wall = 1,
    Jewel,
    Mine,
    Hole,
    Empty
};

class Player {
public:
    int x;
    int y;
    void setPos(int _x, int _y);
};

void Player::setPos(int _x, int _y) {
    x = _x;
    y = _y;
}

int height;
int width;
int maxMoves;
Field maze[200][200];
Player player;

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

Player move() {

}

string solve() {

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Wrong number of arguments.\nArguments:\n - filename\n";
        exit(0);
    }

    string filename = argv[1];
    init(filename);
    solve();

    return 0;
}
