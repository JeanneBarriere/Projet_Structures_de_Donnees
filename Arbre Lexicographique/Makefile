all : main.o biblio_arbrelex.o parser.o
	gcc parser.o biblio_arbrelex.o main.o -o main

parser.o : parser.c parser.h
	gcc -c parser.c

biblio_arbrelex.o : biblio_arbrelex.c biblio_arbrelex.h
	gcc -c biblio_arbrelex.c


main.o : main.c biblio_arbrelex.h
	gcc -c main.c

clean :
	rm -fr *.o
	rm -fr main
