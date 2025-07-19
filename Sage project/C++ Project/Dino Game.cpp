#include <iostream>      // for console input/output
#include <conio.h>       // for _kbhit() and _getch() to detect keypress
#include <windows.h>     // for Sleep() to control game speed and Beep() for sound
#include <ctime>         // for srand(time(0)) random seed
#include <vector>        // to store and manage obstacles dynamically

using namespace std;

const int width = 50;           // width of the game area
const int height = 10;          // height of the game area
int dinoY = height - 2;         // starting y-position of the dinosaur (ground level)
bool jump = false;              // flag to indicate if dinosaur is jumping
int jumpCount = 0;              // counter to manage jump height & duration
bool gameOver = false;          // flag to stop game loop on collision
int score = 0;                  // player’s score

// Structure to represent an obstacle (a cactus)
struct Obstacle {
    int x;                      // x-coordinate of the cactus
    int y;                      // y-coordinate (usually ground level)
};

vector<Obstacle> obstacles;     // list of current obstacles

// Function to draw the game screen
void draw() {
    system("cls");  // clear the console screen

    // Draw top border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\n";

    // Draw game area row by row
    for (int y = 0; y < height; y++) {
        cout << "#"; // left border
        for (int x = 0; x < width; x++) {
            if (y == dinoY && x == 5) {
                cout << "D";   // Draw the dinosaur at (5, dinoY)
            }
            else {
                bool isObstacle = false;
                for (auto &obs : obstacles) {
                    if (obs.x == x && obs.y == y) {
                        cout << "|";  // Draw cactus
                        isObstacle = true;
                        break;
                    }
                }
                if (!isObstacle) cout << " ";  // empty space
            }
        }
        cout << "#\n"; // right border
    }

    // Draw bottom border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\n";

    // Show the score
    cout << "Score: " << score << endl;
}

// Function to handle the jump mechanic
void updateJump() {
    if (jump) {
        if (jumpCount < 3) {      // going up
            dinoY--;
            jumpCount++;
        }
        else if (jumpCount < 6) { // coming down
            dinoY++;
            jumpCount++;
        }
        if (jumpCount >= 6) {     // finished jumping
            jump = false;
            jumpCount = 0;
            dinoY = height - 2;   // reset to ground
        }
    }
}

// Check if dinosaur collides with a cactus
void checkCollision() {
    for (auto &obs : obstacles) {
        if (obs.x == 5 && obs.y == dinoY) {
            gameOver = true;          // end game
            Beep(400, 300);           // play game-over sound
        }
    }
}

// Add a new cactus on the rightmost edge
void spawnObstacle() {
    Obstacle obs;
    obs.x = width - 1;          // start from far right
    obs.y = height - 2;         // at ground level
    obstacles.push_back(obs);
}

// Move all obstacles to the left
void updateObstacles() {
    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i].x--;      // move left
    }
    // Remove cactus if it goes off screen
    while (!obstacles.empty() && obstacles[0].x < 0) {
        obstacles.erase(obstacles.begin());
    }
}

// Main game loop
void gameLoop() {
    int frame = 0;  // to count frames
    while (!gameOver) {
        draw();  // render the screen

        // Handle player input
        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ' && !jump) {    // if SPACE pressed and not already jumping
                jump = true;
                Beep(1000, 100);         // play jump sound
            }
        }

        // Update game state
        updateJump();         // handle jump
        updateObstacles();    // move cacti

        if (frame % 30 == 0) {  // spawn a cactus every 30 frames
            spawnObstacle();
        }

        checkCollision();     // check for crash

        score++;              // increase score

        Sleep(50);            // control speed (~20 fps)
        frame++;
    }

    // Game over screen
    cout << "\nGame Over! Final Score: " << score << endl;
}

// Program entry point
int main() {
    srand(time(0));   // seed random number generator
    cout << "=== DINO GAME ===\n";
    cout << "Press SPACE to jump and avoid the cacti!\n";
    cout << "Press any key to start...\n";
    _getch();         // wait for player to press a key

    gameLoop();       // start the game loop

    cout << "Press any key to exit...\n";
    _getch();         // wait before closing
    return 0;
}
 