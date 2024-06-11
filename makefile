main: main.o tableau.o gfxlib/libisentlib.a
	gcc -Wall main.o -o main tableau.o gfxlib/libisentlib.a -lm -lglut -lGL -lX11

main.o: main.c gfxlib/GfxLib.h gfxlib/BmpLib.h gfxlib/ESLib.h
	gcc -Wall -c main.c

tableau.o: tableau.c tableau.h
	gcc -g -Wall -c tableau.c

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f exemple
