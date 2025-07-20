#include <iostream>      // Provides standard input/output stream (cin, cout)
#include <conio.h>       // For _kbhit() and _getch() to handle real-time keyboard input
#include <windows.h>     // For Sleep() to delay game loop and Beep() to play sound
#include <ctime>         // For time() to seed the random number generator
#include <vector>        // Provides vector to manage a dynamic list of obstacles

using namespace std;      // Avoid writing std:: everywhere

// Game area dimensions
const int width = 50;           // Width of the game screen
const int height = 10;          // Height of the game screen

// Game state variables
int dinoY = height - 2;         // Y-position of dinosaur; starts on ground
bool jump = false;              // Flag: true if the dinosaur is jumping
int jumpCount = 0;              // Counts how many steps into the jump we are
bool gameOver = false;          // Flag: true when collision occurs
int score = 0;                  // Player’s score, increases over time

// Structure to represent a cactus obstacle
struct Obstacle {
    int x;                      // X-position of the cactus
    int y;                      // Y-position of the cactus (ground level)
};

// List of all current obstacles (dynamic)
vector<Obstacle> obstacles;

// Function to render the game screen
void draw() {
    system("cls");  // Clear the console screen

    // Draw the top border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\n";

    // Draw each row of the game area
    for (int y = 0; y < height; y++) {
        cout << "#"; // Left border

        // Draw each column in the current row
        for (int x = 0; x < width; x++) {
            if (y == dinoY && x == 5) {
                cout << "D";   // Print dinosaur at its position
            }
            else {
                bool isObstacle = false;  // Flag to check if cactus is here

                // Check if a cactus is at this position
                for (auto &obs : obstacles) {
                    if (obs.x == x && obs.y == y) {
                        cout << "|";  // Draw cactus
                        isObstacle = true;
                        break;
                    }
                }

                if (!isObstacle) cout << " ";  // Empty space if no dino or cactus
            }
        }

        cout << "#\n"; // Right border
    }

    // Draw the bottom border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\n";

    // Display the score
    cout << "Score: " << score << endl;
}

// Function to handle the dinosaur’s jump logic
void updateJump() {
    if (jump) {  // If currently jumping
        if (jumpCount < 3) {      // Moving up phase
            dinoY--;             // Move dinosaur up
            jumpCount++;
        }
        else if (jumpCount < 6) { // Moving down phase
            dinoY++;             // Move dinosaur down
            jumpCount++;
        }

        if (jumpCount >= 6) {     // Jump finished
            jump = false;         // Reset jump
            jumpCount = 0;
            dinoY = height - 2;   // Back to ground
        }
    }
}

// Function to check if dinosaur collides with a cactus
void checkCollision() {
    for (auto &obs : obstacles) {
        if (obs.x == 5 && obs.y == dinoY) {  // Dino and cactus at same position
            gameOver = true;                // End game
            Beep(400, 300);                 // Play game over sound
        }
    }
}

// Function to spawn a new cactus at the far right
void spawnObstacle() {
    Obstacle obs;                // Create a new cactus
    obs.x = width - 1;           // Place at rightmost column
    obs.y = height - 2;          // Place on ground
    obstacles.push_back(obs);   // Add to the list
}

// Function to update positions of all cacti
void updateObstacles() {
    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i].x--;       // Move each cactus left by 1
    }

    // Remove any cacti that have moved off the screen
    while (!obstacles.empty() && obstacles[0].x < 0) {
        obstacles.erase(obstacles.begin());
    }
}

// The main game loop where everything happens
void gameLoop() {
    int frame = 0;  // Frame counter

    while (!gameOver) { // Loop runs until collision
        draw();         // Render the current frame

        // Check for keyboard input
        if (_kbhit()) {
            char ch = _getch();   // Get the pressed key
            if (ch == ' ' && !jump) {  // If SPACE pressed and not already jumping
                jump = true;          // Start jump
                Beep(1000, 100);      // Play jump sound
            }
        }

        updateJump();         // Update dinosaur’s jump state
        updateObstacles();    // Move all cacti

        if (frame % 30 == 0) {  // Every 30 frames spawn a new cactus
            spawnObstacle();
        }

        checkCollision();     // Detect collision

        score++;              // Increment score

        Sleep(50);            // Wait ~50ms to control speed (about 20 FPS)
        frame++;              // Next frame
    }

    // When game is over, show final score
    cout << "\nGame Over! Final Score: " << score << endl;
}

// Main function: entry point of the program
int main() {
    srand(time(0));   // Seed the random number generator with current time

    // Intro message
    cout << "=== DINO GAME ===\n";
    cout << "Press SPACE to jump and avoid the cacti!\n";
    cout << "Press any key to start...\n";
    _getch();         // Wait for the player to press a key

    gameLoop();       // Start the game

    cout << "Press any key to exit...\n";
    _getch();         // Wait for key press before exiting
    return 0;         // Exit the program
}
