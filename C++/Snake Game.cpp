#include <iostream>
#include <conio.h>   // for _kbhit() and _getch() (Windows)
#include <windows.h> // for Sleep()
#include <cstdlib>   // for rand()
using namespace std;

bool gameOver;
const int width = 20;
const int height = 10;
int x, y;           // Snake head position
int fruitX, fruitY; // Fruit position
int score;
int tailX[100], tailY[100]; // Tail positions
int nTail;                  // Tail length

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;

    // Spawn fruit at a position not inside the snake's tail
    do {
        fruitX = rand() % width;
        fruitY = rand() % height;
    } while (fruitX == x && fruitY == y);

    score = 0;
    nTail = 0;
}

void Draw() {
    system("cls");

    // Draw top wall
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#"; // Left wall

            if (i == y && j == x)
                cout << "O"; // Snake head
            else if (i == fruitY && j == fruitX)
                cout << "F"; // Fruit
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Tail
                        printTail = true;
                        break;
                    }
                }
                if (!printTail)
                    cout << " "; // Empty space
            }

            if (j == width - 1) cout << "#"; // Right wall
        }
        cout << endl;
    }

    // Draw bottom wall
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
    cout << "Controls: W = up, S = down, A = left, D = right, X = exit" << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
        case 'A':
            if (dir != RIGHT) dir = LEFT; // Prevent reverse direction
            break;
        case 'd':
        case 'D':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
        case 'W':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
        case 'S':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
        case 'X':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    // Update tail positions
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move head
    switch (dir) {
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    default: break;
    }

    // Wrap around screen edges
    if (x >= width) x = 0; 
    else if (x < 0) x = width - 1;

    if (y >= height) y = 0; 
    else if (y < 0) y = height - 1;

    // Check if head hits tail => game over
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // If snake eats fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        
        // Generate new fruit position avoiding snake body
        bool validPosition = false;
        while (!validPosition) {
            fruitX = rand() % width;
            fruitY = rand() % height;
            validPosition = true;

            if (fruitX == x && fruitY == y) {
                validPosition = false;
                continue;
            }
            for (int i = 0; i < nTail; i++) {
                if (tailX[i] == fruitX && tailY[i] == fruitY) {
                    validPosition = false;
                    break;
                }
            }
        }
        nTail++;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Speed of the game, reduce to make it faster
    }
    system("cls");
    cout << "Game Over! Final Score: " << score << endl;
    cout << "Press any key to exit..." << endl;
    _getch(); // Pause before exit
    return 0;
}
