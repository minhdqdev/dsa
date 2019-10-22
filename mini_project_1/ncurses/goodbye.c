#include <ncurses.h>

int main(){
    initscr();
    addstr("Goodbye, cruel C programming!");
    refresh();
    getch();

    endwin();

    return 0;
}