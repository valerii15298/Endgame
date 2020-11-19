#include "header.h"

void save_record(int points){
    curs_set(TRUE);
	FILE *dst = fopen("records", "a+");
    FIELD *field[3];
	FORM  *my_form;
	char *buf, feedback[37] = "feedbacks/", *buf2;
	feedback[10] = '\0';
	int ch;

    field[0] = new_field(1, 16, 7, 5, 0, 0);
    field[1] = new_field(5, 40, 11, 5, 0, 0);
	field[2] = NULL;
	set_field_back(field[0], A_UNDERLINE);
	set_field_back(field[1], A_UNDERLINE);
	field_opts_off(field[1], O_WRAP);

	my_form = new_form(field);
	post_form(my_form);
	mvprintw(5, 5, "NICKNAME:");
	mvprintw(9, 5, "WRITE PLEASE YOUR FEEDBACK ABOUT THIS GAME:");
    move(7, 5);
	refresh();
	while((ch = getch()) != KEY_F(1)){
		if (ch==KEY_BACKSPACE){
			form_driver(my_form, REQ_DEL_CHAR);
			form_driver(my_form, REQ_PREV_CHAR);
			form_driver(my_form, REQ_DEL_CHAR);
		} else if(ch==10){
			form_driver(my_form, REQ_VALIDATION);
			buf = field_buffer(current_field(my_form), 0);
			if (current_field(my_form) == field[0]){
				fprintf(dst, "%s - %d\n", buf, points);
				fclose(dst);
				for (int i = 0;i<16;i++)
					if (buf[i] == ' '){
						buf[i] = '\0';
						break;
					}
				dst = fopen(strcat(feedback, buf), "w");
				fprintf(dst, "Feedback from user: %s\n\n", buf);
			} else {
				buf2 = field_buffer(field[1], 0);
				for (int i = 199;buf2[i]==' ' && i>-1;i--)
					buf2[i] = '\0';
				fprintf(dst, "%s", field_buffer(field[1], 0));
				break;
				}
			form_driver(my_form, REQ_NEXT_FIELD);
		} else
			form_driver(my_form, ch);
	}
	unpost_form(my_form);
	free_form(my_form);
    for (int i = 0;i<2;i++)
	    free_field(field[i]);
    fclose(dst);
    curs_set(FALSE);
	clear();
}
