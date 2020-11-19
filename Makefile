all: install clean

install:
	@cp src/*.c inc/*.h .
	@clang -o endgame *.c -lform -lmenu -lpanel -lncurses

clean:
	@rm -rf *.c *.h
