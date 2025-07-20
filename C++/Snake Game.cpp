#include <iostream>      // For console I/O (cout, cin)
#include <conio.h>       // For _kbhit(), _getch() (real-time keyboard input)
#include <windows.h>     // For Sleep() and system("cls")
#include <cstdlib>       // For rand()
using namespace std;

// === Game state variables ===
bool gameOver;                  // Flag: true when the game ends
const int width = 20;           // Width of game board
const int height = 10;          // Height of game board
int x, y;                       // Snake head position (x, y)
int fruitX, fruitY;             // Fruit position (x, y)
int score;                      // Player's current score
int tailX[100], tailY[100];     // Arrays to store tail segments' positions
int nTail;                      // Current length of tail

// === Direction of movement ===
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;                 // Current direction of the snake

// === Initialize the game state ===
void Setup() {
    gameOver = false;           // Game is running
    dir = STOP;                 // Snake is stationary at the start
    x = width / 2;              // Snake head starts at center of board
    y = height / 2;

    // Place fruit at random position not equal to snake head
    do {
        fruitX = rand() % width;
        fruitY = rand() % height;
    } while (fruitX == x && fruitY == y);

    score = 0;                  // Reset score
    nTail = 0;                  // Tail is empty
}

// === Draw the game board ===
void Draw() {
    system("cls");              // Clear the console screen

    // Draw top border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Draw the game area row by row
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#"; // Left wall

            // Draw snake head
            if (i == y && j == x)
                cout << "O";
            // Draw fruit
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool printTail = false;

                // Check if current cell is part of the tail
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Tail segment
                        printTail = true;
                        break;
                    }
                }

                // Empty space
                if (!printTail)
                    cout << " ";
            }

            if (j == width - 1) cout << "#"; // Right wall
        }
        cout << endl;
    }

    // Draw bottom border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Show score and controls
    cout << "Score: " << score << endl;
    cout << "Controls: W = up, S = down, A = left, D = right, X = exit" << endl;
}

// === Handle player input ===
void Input() {
    if (_kbhit()) {             // If a key is pressed
        switch (_getch()) {     // Read the key
        case 'a':
        case 'A':
            if (dir != RIGHT) dir = LEFT; // Prevent reversing into itself
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
            gameOver = true;   // End the game
            break;
        }
    }
}

// === Game logic: movement, collisions, eating fruit ===
void Logic() {
    // === Move the tail ===
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

    // === Move the head ===
    switch (dir) {
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    default: break;
    }

    // === Check wall collisions (wrap around) ===
    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;

    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;

    // === Check collision with tail ===
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // === Check if fruit is eaten ===
    if (x == fruitX && y == fruitY) {
        score += 10;           // Increase score
        nTail++;               // Grow tail

        // Place new fruit at a valid position (not on snake)
        bool validPosition = false;
        while (!validPosition) {
            fruitX = rand() % width;
            fruitY = rand() % height;
            validPosition = true;

            // Check if fruit is on snake head
            if (fruitX == x && fruitY == y) {
                validPosition = false;
                continue;
            }

            // Check if fruit is on tail
            for (int i = 0; i < nTail; i++) {
                if (tailX[i] == fruitX && tailY[i] == fruitY) {
                    validPosition = false;
                    break;
                }
            }
        }
    }
}

// === Main function ===
int main() {
    Setup();                   // Initialize game state

    while (!gameOver) {        // Game loop
        Draw();                // Draw the board
        Input();               // Handle input
        Logic();               // Update state
        Sleep(100);            // Delay to control game speed (~10 FPS)
    }

    // Game over message
    system("cls");
    cout << "Game Over! Final Score: " << score << endl;
    cout << "Press any key to exit..." << endl;
    _getch();                  // Wait for user before closing
    return 0;
}
