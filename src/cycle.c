#include "header.h"

int cycle(){
    int ch = 0, speed = 100, t,
        current_trash, choose,
        minion_startx = 209, minion_starty = 1,
        points = 0, level = 1, life = 3,
        ice_x[] = {0, 28, 16, 3};
    
    char *ice_files[] = {"images/water.txt", "images/glacier_3.txt",
                         "images/glacier_2.txt", "images/glacier_4.txt"},

         *box_files[] = {"images/trash_paper.txt", "images/trash_organic.txt",
                         "images/trash_glass.txt", "images/trash_plastic.txt",  
                         "images/trash_unsorted.txt"},

         *trash_files[] = {"images/paper.txt", "images/apple.txt",
                           "images/bottle.txt", "images/bag.txt",
                           "images/battery.txt"};
    PANEL
    *panels[4], *boxes[5], *trashes[5],
    *minion = get_pan("images/minion.txt", 4, 100),
    *pinguin = get_pan("images/pinguin.txt", 26, 35),
    *mid_line = get_pan("images/line.txt", 0, 97),
    *levelbar = init_levelbar(),
    *bear = get_pan("images/bear.txt", 12, 100);
    for (int i = 0;i<5;i++)
        trashes[i] = get_pan(trash_files[i], 58, 100);
    for (int i = 0;i<4;i++)
        panels[i] = get_pan(ice_files[i], 46, ice_x[i]);
    for (int i = 0;i<5;i++)
        boxes[i] = get_pan(box_files[i], 58, 100+26*i);
    
    hide_panel(boxes[2]);
    hide_panel(boxes[3]);
    hide_panel(boxes[4]);
    hide_panel(bear);
    top_panel(minion);
    get_trash(panel_window(minion), &current_trash, level, &choose, trashes);
    ref();
    
    timeout(speed);
    while ((ch = getch())!='q'){
        go_minion(minion, &minion_starty, &minion_startx, 0, 100, 20, 229);
        shift_pan(trashes[current_trash], 1, 0);
        t = getbegy(panel_window(trashes[current_trash]));
        if (t>57){
            if (choose==current_trash)
                check_lvl(panel_window(levelbar), &level, ++points, &speed, boxes);
            else {  
                    hide_panel(panels[life--]);
                    if (life == 0){
                        bottom_panel(pinguin);
                        timeout(200);
                        for (int i = 0;i<20;i++){
                            shift_pan(pinguin, 1, 0);
                            ref();
                            if (getch()=='q'){
                                free_all(panels, boxes, trashes, (PANEL *[]){minion, pinguin, bear, mid_line, levelbar});
                                return points;
                                }
                            }
                        show_panel(bear);
                        mvwprintw(panel_window(bear), 10, 35, "SCORE: %d", points);
                        mvwprintw(panel_window(bear), 12, 35, "PRESS 'c' to continue . . .");
                        ref();
                        while(getch()!='c');
                        free_all(panels, boxes, trashes, (PANEL *[]){minion, pinguin, bear, mid_line, levelbar});
                        return points;
                        }
                    }
            get_trash(panel_window(minion), &current_trash, level, &choose, trashes);
        }
        if(ch == KEY_LEFT && choose>0 && t<=57){
            choose--;
            shift_pan(trashes[current_trash], 0, -26);
            }
        if (ch == KEY_RIGHT && choose<((level<4) ? level : 4) && t<=57){
            choose++;
            shift_pan(trashes[current_trash], 0, 26);
            }
        ref();
        if (ch == 'p')
            while(getch() != 'p');
        if (ch == 'r'){
            free_all(panels, boxes, trashes, (PANEL *[]){minion, pinguin, bear, mid_line, levelbar});
            return -1;
        }
        if (!check_screen())
            break;
        timeout(speed);
    }
    free_all(panels, boxes, trashes, (PANEL *[]){minion, pinguin, bear, mid_line, levelbar});
    return points;
}
