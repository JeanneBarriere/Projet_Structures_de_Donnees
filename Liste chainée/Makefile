all : main.o biblio_liste.o parser.o
	gcc parser.o biblio_liste.o main.o -o main

parser.o : parser.c parser.h
	gcc -c parser.c

biblio_liste.o : biblio_liste.c biblio_liste.h
	gcc -c biblio_liste.c


main.o : main.c biblio_liste.h
	gcc -c main.c

clean :
	rm -fr *.o
	rm -fr main
