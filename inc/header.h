#ifndef HEADER_H
#define HEADER_H
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <panel.h>
#include <menu.h>
#include <form.h>

int  cycle();

_Bool check_screen();

void save_record(int points);

void free_panels(PANEL *panels[], int k);

void free_all(PANEL *arr1[], PANEL *arr2[], PANEL *arr3[], PANEL *arr4[]);

void start_win();

void initcolors();

void ref();

void shift_pan(PANEL *pan, int dy, int dx);

void get_trash(WINDOW *minion, int *num_trash, int level, int *choose, PANEL *trashes[]);

PANEL *init_levelbar();

void check_lvl(WINDOW *levelbar, int *level, int points, int *speed, PANEL *boxes[]);

void go_minion(PANEL *win_pan, int *dsty, int *dstx, int y1, int x1, int y2, int x2);

PANEL *get_pan(char *file, int pos_y, int pos_x);

void number_from_file(int src, int *num, char c);

void menu();

void show_file(char *file);

void choice(int c);

#endif
