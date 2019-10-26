#include <ncurses.h>

int main(){
    char text1[] = "Oh give me a clone!\n";
    char text2[] = "Yes a clone of my own!";

    initscr();
    addstr(text1);
    addstr(text2);
    refresh();
    getch();

    endwin();
    return 0;
}