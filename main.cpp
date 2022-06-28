#include <ncurses.h>
#include "src/StatusBar.hpp"

int main()
{
    initscr();
    clear();
    refresh();
    curs_set(0);
    noecho();

    if (!has_colors())
    {
        // Error message
        return 1;
    }

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_RED);

    StatusBar statusbar(3);
    statusbar.setText(0, " NORMAL ", COLOR_PAIR(1));
    statusbar.setText(1, " main.cpp ", COLOR_PAIR(2));
    statusbar.setText(2, " Cool Text ", COLOR_PAIR(3));
    statusbar.draw();

    // attron(COLOR_PAIR(1));
    // mvprintw(LINES - 1, 0, " NORMAL ");
    // attroff(COLOR_PAIR(1));
    refresh();

    getch();
    endwin();
    return 0;
}