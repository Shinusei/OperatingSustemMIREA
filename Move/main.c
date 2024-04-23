#include <stdio.h>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h> 

int x, y, state = 1;
bool running = true; 

void *move_thread(void *arg) {
    while (running) {
        switch (state) {
            case 1:
                y = (y + LINES - 1) % LINES;
                break;
            case 2:
                y = (y + 1) % LINES;
                break;
            case 3:
                x = (x + COLS - 1) % COLS;
                break;
            case 4:
                x = (x + 1) % COLS;
                break;
            default:
                break;
        }
        usleep(80000);
        
    }
    return NULL;
}

void *input_thread(void *arg) {
    int ch, tch;
    while (running) {
        
        tch = getch();
        ch = tch;
        switch (ch) {
            case KEY_UP:
                state = 1;
                break;
            case KEY_DOWN:
                state = 2;
                break;
            case KEY_LEFT:
                state = 3;
                break;
            case KEY_RIGHT:
                state = 4;
                break;
            case KEY_END:
                running = false;
                break;
            default:
                break;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t move_thread_id, input_thread_id;

    if (NULL == initscr()) {
        return -1;
    }

    x = COLS / 2;
    y = LINES / 2;
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    pthread_create(&move_thread_id, NULL, move_thread, NULL);
    pthread_create(&input_thread_id, NULL, input_thread, NULL);

    while (running) {
        mvaddch(y, x, '*');
        refresh();
    }

    endwin();

    pthread_join(move_thread_id, NULL);
    pthread_join(input_thread_id, NULL);

    return 0;
}