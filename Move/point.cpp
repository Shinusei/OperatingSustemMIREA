#include <stdio.h>
#include <ncurses.h>
#include <thread>
#include <unistd.h>
//#include <fstream>
using namespace std;

int f = 1;
int x, y, ch;
int f1()
{
    if (NULL == initscr())
    {
        return -1;
    }
    x = COLS / 2;
    y = LINES / 2;
    noecho();
    curs_set(0);
    while (1)
    {
        mvaddch(y, x, ' ');

        switch (f)
        {
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

        mvaddch(y, x, '*');
        refresh();
        sleep(1);
    }
    endwin();
    return 0;
}

void f2()
{
    noecho();
    keypad(stdscr, TRUE);
    while (1)
    {
        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            f = 1;
            break;
        case KEY_DOWN:
            f = 2;
            break;
        case KEY_LEFT:
            f = 3;
            break;
        case KEY_RIGHT:
            f = 4;
            break;
        default:
            break;
        }
        //sleep(1);
    }
}

int main()
{
    thread t2(f2);
    thread t1(f1);
    t2.join();
    t1.join();
    return 0;
}
