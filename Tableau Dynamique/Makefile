all : main.o biblio_dynamique.o parser.o
	gcc parser.o biblio_dynamique.o main.o -o main

parser.o : parser.c parser.h
	gcc -c parser.c

biblio_dynamique.o : biblio_dynamique.c biblio_dynamique.h
	gcc -c biblio_dynamique.c
	
test : main.o biblio_dynamique.o parser.o
	gcc parser.o biblio_dynamique.o maintest.o -o test
	
maintest.o : maintest.c biblio_dynamique.h
	gcc -c maintest.c

main.o : main.c biblio_dynamique.h
	gcc -c main.c

clean :
	rm -fr *.o
	rm -fr main
