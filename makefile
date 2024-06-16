main: main.o tableau.o grille.o images.o GFXLib/libisentlib.a
	gcc -Wall main.o -o main tableau.o grille.o images.o GFXLib/libisentlib.a -lm -lglut -lGL -lX11

main.o: main.c GFXLib/GfxLib.h GFXLib/BmpLib.h GFXLib/ESLib.h
	gcc -Wall -c main.c

tableau.o: tableau.c tableau.h
	gcc -g -Wall -c tableau.c

grille.o: grille.c grille.h
	gcc -g -Wall -c grille.c

images.o: images.c images.h
	gcc -g -Wall -c images.c

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f main
