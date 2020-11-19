#include "header.h"

void show_file(char *file){
    int src = open(file, 'r'), y = 0, x = 0;
    char buf;
    while(read(src, &buf, sizeof(char)) > 0)
        if (buf == '\n'){
            y++;
            x = 0;
            }
        else if (buf>31 && buf<127){
            mvprintw(y, x++, &buf);
            mvprintw(y, x, "   ");
            }
    close(src);
    move(getcury(stdscr)+2, 0);
    printw("Press \"Enter\" to continue . . .");
    refresh();
    timeout(-1);
    while(getch()!=10);
    clear();
}
