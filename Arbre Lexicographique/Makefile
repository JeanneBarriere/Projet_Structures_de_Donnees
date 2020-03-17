all : main.c biblio_arbrelex.c parser.c
	gcc parser.c biblio_arbrelex.c main.c -o main

parser.c : parser.c parser.h
	gcc -c parser.c

biblio_arbrelex.c : biblio_arbrelex.c biblio_arbrelex.h
	gcc -c biblio_arbrelex.c


main.c : main.c biblio_arbrelex.h
	gcc -c main.c

clean :
	rm -fr *.o
	rm -fr main
