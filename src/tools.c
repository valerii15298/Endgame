#include "header.h"

void initcolors(){
    start_color();
    int COLOR_BROWN = 33;
    init_color(COLOR_BROWN, 150, 75, 0);
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_RED);
    init_pair(5, COLOR_BLACK, COLOR_BLUE);
    init_pair(6, COLOR_BLACK, COLOR_WHITE);
    init_pair(7, COLOR_BLACK, COLOR_BROWN);
    init_pair(8, COLOR_GREEN, COLOR_BLACK);
    init_pair(9, COLOR_YELLOW, COLOR_BLACK);
    init_pair(10, COLOR_RED, COLOR_BLACK);
    init_pair(11, COLOR_BLUE, COLOR_BLACK);
    init_pair(12, COLOR_WHITE, COLOR_GREEN);
    init_pair(13, COLOR_WHITE, COLOR_YELLOW);
    init_pair(14, COLOR_RED, COLOR_WHITE);
    init_pair(15, COLOR_YELLOW, COLOR_GREEN);
    init_pair(16, COLOR_WHITE, COLOR_CYAN);
    init_pair(17, COLOR_WHITE, COLOR_BLUE);
    init_pair(18, COLOR_WHITE, COLOR_WHITE);
    init_pair(19, COLOR_WHITE, COLOR_RED);
    init_pair(20, COLOR_WHITE, COLOR_BLUE);
    init_pair(21, COLOR_GREEN, COLOR_GREEN);
    init_pair(22, COLOR_RED, COLOR_RED);

}

void start_win(){
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(FALSE);
    initcolors();
    wrefresh(stdscr);
}

void ref(){
    update_panels();
    doupdate();
}

void shift_pan(PANEL *pan, int dy, int dx){
    move_panel(pan, getbegy(panel_window(pan))+dy, getbegx(panel_window(pan))+dx);
}

void get_trash(WINDOW *minion, int *num_trash, int level, int *choose, PANEL *trashes[]){
    int x = getbegx(minion) + 10;
    *choose = (x-100)/26;
    x = 104 + (*choose)*26;
    *num_trash = rand()%(((level<4) ? (level) : (4))+1);
    move_panel(trashes[*num_trash], getbegy(minion), x);
}

PANEL *init_levelbar(){
    WINDOW *levelbar = newwin(3, 97, 0, 0);
    wattron(levelbar, COLOR_PAIR(8));
    mvwprintw(levelbar, 0, 0, "\"Q\" - EXIT\n\"R\" - RESTART\n\"P\" - PAUSE/CONTINUE");
    mvwprintw(levelbar, 1, 61, "POINTS: 0");
    mvwprintw(levelbar, 1, 73, "LEVEL: 1");
    return new_panel(levelbar);
}

void check_lvl(WINDOW *levelbar, int *level, int points, int *speed, PANEL *boxes[]){
    if ((*level) < 4 && (points % 2)){
        (*level)++;
        show_panel(boxes[*level]);
    } 
    else if ((*level) > 3) {
        *level += (points % 3) / 2;
        if (*speed > 35 && (points % 3 == 2))
            (*speed) -= (*speed) / 3;
        else if ((*level) < 15)
            (*speed) -= ((points % 4) / 3) * 2;
        else 
            (*speed) -= ((points % 7) / 6);
    }
    mvwprintw(levelbar, 1, 69, "%d", points);
    mvwprintw(levelbar, 1, 80, "%d", *level);
}

void go_minion(PANEL *win_pan, int *dsty, int *dstx, int y1, int x1, int y2, int x2) {
    WINDOW *win = panel_window(win_pan);
    int y_minion = getbegy(win),
        x_minion = getbegx(win);
    if (*dsty == y_minion && *dstx == x_minion){
        *dsty = y1 + rand() % (y2 - getmaxy(win) - y1);
        *dstx = x1 + rand() % (x2 - getmaxx(win) - x1);
        }
    shift_pan(win_pan, (y_minion != *dsty) ? (*dsty - y_minion)/abs(*dsty - y_minion) : 0,
                       (x_minion != *dstx) ? (*dstx - x_minion)/abs(*dstx - x_minion) : 0);
}

void free_panels(PANEL *panels[], int k){
    WINDOW *win;
    for (int i = 0;i<k;i++){
        win = panel_window(panels[i]);
        del_panel(panels[i]);
        delwin(win);
        }
}

void number_from_file(int src, int *num, char c){
    char buf;
    *num = 0;
    for(read(src, &buf, 1);(buf!=c) && (buf!='\n');read(src, &buf, 1))
        *num = 10*(*num)+(buf-'0');
}

PANEL *get_pan(char *image, int pos_y, int pos_x){
    int src = open(image, 'r'), index = 0, count = 0, height, width, k = 0;
    char buf;
    number_from_file(src, &height, ' ');
    number_from_file(src, &width, '\n');
    WINDOW *win = newwin(height, width, pos_y, pos_x);
    for (int i = 0;i<height;k+=count){
        if (k == width){
            i++;
            k = 0;
        }
        // clear();
        // mvprintw(0, 0, "invalid file: %s line: %d", image, i+2);
        //refresh();
        read(src, &buf, 1);
        number_from_file(src, &index, '-');
        number_from_file(src, &count, ',');
        wattron(win, COLOR_PAIR(index));
        for (int j = 0;j<count;j++)
            mvwprintw(win, i, j+k, &buf);
        wattroff(win, COLOR_PAIR(index));
        }
    close(src);
    return new_panel(win);
}

void free_all(PANEL *arr1[], PANEL *arr2[], PANEL *arr3[], PANEL *arr4[]){
    free_panels(arr1, 4);
    free_panels(arr2, 5);
    free_panels(arr3, 5);
    free_panels(arr4, 5);
}
