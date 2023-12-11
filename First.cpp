#include <iostream>
using namespace std;
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "startscreen.h"
#include "result.h"

const int WIDTH = 600;
const int HEIGHT = 600;
const int CELL_SIZE = 200;

enum Player {
    NONE,
    PLAYER_X,
    PLAYER_O
};

Player board[3][3] = { {NONE, NONE, NONE},
                      {NONE, NONE, NONE},
                      {NONE, NONE, NONE} };

void drawBoard() {
    al_clear_to_color(al_map_rgb(0, 0, 0));  // Clear the screen to white

    // Draw grid
    for (int i = 1; i < 3; ++i) {
        al_draw_line(i * CELL_SIZE, 0, i * CELL_SIZE, HEIGHT, al_map_rgb(255, 255, 255), 5);
        al_draw_line(0, i * CELL_SIZE, WIDTH, i * CELL_SIZE, al_map_rgb(255, 255, 255), 5);
    }
	int counter = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == PLAYER_X) {
                // Alternate between normal color and a brighter color for glowing effect
                ALLEGRO_COLOR color = (counter / 10 % 2 == 0) ? al_map_rgb(255, 0, 0) : al_map_rgb(255, 100, 100);
                al_draw_line(j * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE, color, 5);
                al_draw_line((j + 1) * CELL_SIZE, i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE, color, 5);
            } else if (board[i][j] == PLAYER_O) {
                // Alternate between normal color and a brighter color for glowing effect
                ALLEGRO_COLOR color = (counter / 10 % 2 == 0) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 100);
                al_draw_circle((j + 0.5) * CELL_SIZE, (i + 0.5) * CELL_SIZE, CELL_SIZE / 2 - 5, color, 5);
            }
        }
    }

    al_flip_display();  // Refresh the display
}

bool isBoardFull() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == NONE) {
                return false;
            }
        }
    }
    return true;
}

bool checkWin(Player player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}
	
	ALLEGRO_SAMPLE* clickSound;

void initializeSound() {
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);  // Reserve 1 sample for now

    // Load the click sound (replace "click_sound.ogg" with your actual sound file)
    clickSound = al_load_sample("click.wav");
    if (!clickSound) {
        fprintf(stderr, "Failed to load click sound.\n");
    }
}

void playClickSound() {
    if (clickSound) {
        al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
}


int main() {
    // Initialize Allegro
    if (!al_init()) {
        cerr << "Failed to initialize Allegro." << endl;
        return -1;
    }
	
	

    startscreen();
    // Create display
    ALLEGRO_DISPLAY* display = al_create_display(WIDTH, HEIGHT);
    if (!display) {
        cerr << "Failed to create display." << endl;
        return -1;
    }

    if (!al_init_primitives_addon()) {
        cerr << "Failed to initialize Allegro Primitives addon!" << endl;
        return -1;
    }

    if (!al_install_mouse()) {
        cerr << "Failed to initialize the mouse!" << endl;
        return -1;
    }

    // Initialize sound
    initializeSound();

    // Set up event queue
    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    // Draw the initial board
    drawBoard();

    // Set up game loop
    bool gameOver = false;
    Player currentPlayer = PLAYER_X;

    while (!gameOver) {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            gameOver = true;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int col = event.mouse.x / CELL_SIZE;
            int row = event.mouse.y / CELL_SIZE;

            if (board[row][col] == NONE) {
                board[row][col] = currentPlayer;
                drawBoard();
                playClickSound();

                if (checkWin(PLAYER_X)) {
                    cout << "Player 1 wins!" << endl;
                    gameOver = true;
                    displayResult1();
                    break;
                } else if (checkWin(PLAYER_O)) {
                    cout << "Player 2 wins!" << endl;
                    gameOver = true;
                    displayResult2();
                    break;
                } else if (isBoardFull()) {
                    cout << "It's a draw!" << endl;
                    gameOver = true;
                    displayResult3();
                	break;
                } else {
                    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
                }
            }
        }
        
    }

    // Clean up
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);
    al_destroy_sample(clickSound);  // Clean up sound resources

    return 0;
}

