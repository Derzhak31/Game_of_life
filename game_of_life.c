
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void input_board(int **board_pointer, int width, int heigth, int *life);
void print_screen(int **board_pointer, int width, int heigth);
int neighbors_count(int **board_pointer, int width, int heigth, int i, int j);
void play_game(int **board_pointer, int **newboard, int width, int heigth);
void scan_buttons(int *delay, int *life);

int main(void) {
    int width = 80;
    int heigth = 25;
    int delay = 0, life;
    int **board_pointer = (int **)calloc(heigth, sizeof(int *));
    int *board_values = (int *)calloc(heigth * width, sizeof(int));
    int **newboard_pointer = (int **)calloc(heigth, sizeof(int *));
    int *newboard_values = (int *)calloc(heigth * width, sizeof(int));
    for (int i = 0; i < heigth; i++) {
        board_pointer[i] = &board_values[i * width];
    }
    for (int i = 0; i < heigth; i++) {
        newboard_pointer[i] = &newboard_values[i * width];
    }
    input_board(board_pointer, width, heigth, &life);
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    if (freopen("/dev/tty", "r", stdin)) {
    }
    while (life) {
        print_screen(board_pointer, width, heigth);
        play_game(board_pointer, newboard_pointer, width, heigth);
        scan_buttons(&delay, &life);
        usleep(400000 + delay);
    }
    free(board_pointer);
    free(board_values);
    free(newboard_pointer);
    free(newboard_values);
    endwin();
    return 0;
}

void scan_buttons(int *delay, int *life) {
    char input_buttons = getch();
    if (input_buttons == '-' && *delay < 600000) *delay += 50000;
    if (input_buttons == '+' && *delay > -300000) *delay -= 50000;
    if (input_buttons == 'q') *life = 0;
}

void input_board(int **board_pointer, int width, int heigth, int *life) {
    *life = 1;
    for (int i = 0; i < heigth; i++) {
        for (int j = 0; j < width; j++) {
            if (scanf("%d", &board_pointer[i][j]) != 1) {
                *life = 0;
                break;
            }
        }
    }
}

void print_screen(int **board_pointer, int width, int heigth) {
    clear();
    for (int i = 0; i < heigth; i++) {
        for (int j = 0; j < width; j++) {
            if (board_pointer[i][j] == 0) printw("%c", ' ');
            if (board_pointer[i][j] == 1) printw("%c", 'o');
        }
        printw("\n");
    }
    refresh();
}

int neighbors_count(int **board_pointer, int width, int heigth, int i, int j) {
    int count = 0;
    for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
            if (k || l) {
                int a = i + k;
                if (a < 0) a = heigth - 1;
                if (a >= heigth) a = 0;
                int b = j + l;
                if (b < 0) b = width - 1;
                if (b >= width) b = 0;
                if (board_pointer[a][b]) count++;
            }
        }
    }
    return count;
}

void play_game(int **board_pointer, int **newboard, int width, int heigth) {
    int a;
    for (int i = 0; i < heigth; i++) {
        for (int j = 0; j < width; j++) {
            a = neighbors_count(board_pointer, width, heigth, i, j);
            if (a == 2) {
                newboard[i][j] = board_pointer[i][j];
            }
            if (a == 3) {
                newboard[i][j] = 1;
            }
            if (a < 2) {
                newboard[i][j] = 0;
            }
            if (a > 3) {
                newboard[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < heigth; i++) {
        for (int j = 0; j < width; j++) {
            board_pointer[i][j] = newboard[i][j];
        }
    }
}