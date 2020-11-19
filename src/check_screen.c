#include "header.h"

_Bool check_screen(){
    int y, x;
    _Bool f = 0;
    getmaxyx(stdscr, y, x);
    timeout(-1);
    while (y<65 || x<230){
        f = 1;
        mvprintw(0, 0, "'q' - go to \"MENU\"");
        mvprintw(1, 0, "Your window has too small resolution!");
        mvprintw(2, 0, "Resize your window!");
        refresh();
        if (getch()=='q'){
            clear();
            return 0;
            }
        getmaxyx(stdscr, y, x);
        clear();
    }
    if (f){
        clear();
        mvprintw(0, 0, "Press 'c' - to continue . . .");
        while(getch()!='c');
        clear();
        refresh();
        ref();
    }
    return 1;
}
