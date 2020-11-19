#include "header.h"

void menu(){
    int c, number_items = 4, points;
    char *choices[] = {
                    "Start game!",
                    "Read instructions",
                    "See table of records",
                    "Exit('q')"
                    };
    ITEM *items[number_items];
    for (int i = 0;i<number_items;i++)
        items[i] = new_item(choices[i],"#");
    items[number_items] = (ITEM*)NULL;
    MENU *my_menu = new_menu(items);
    post_menu(my_menu);
    refresh();
    while((c = getch()) != 'q'){
        switch(c){
            case KEY_DOWN:
		        menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
            case 10:
                unpost_menu(my_menu);
                if (current_item(my_menu) == items[0]){
                    if (check_screen()){
                        while((points=cycle())==(-1));
                        save_record(points);
                    }
                }
                else if (current_item(my_menu) == items[1])
                    show_file("README.md");
                else if (current_item(my_menu) == items[2])
                    show_file("records");
                else {
                    post_menu(my_menu);
	                for (int i = 0;i<number_items;i++)
                        free_item(items[i]);
	                free_menu(my_menu);
                    return;
                }
                post_menu(my_menu);
                refresh();
		}
        timeout(-1);
	}	
}
