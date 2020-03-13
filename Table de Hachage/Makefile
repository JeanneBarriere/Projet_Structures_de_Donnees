all : main.o biblio_hachage.o parser.o
	gcc parser.o biblio_hachage.o main.o -o main

parser.o : parser.c parser.h
	gcc -c parser.c

biblio_hachage.o : biblio_hachage.c biblio_hachage.h
	gcc -c biblio_hachage.c


main.o : main.c biblio_hachage.h
	gcc -c main.c

clean :
	rm -fr *.o
	rm -fr main
