all: lab5

lab5: db.o main.o storage.o
	gcc db.o main.o storage.o -o lab5

main.o: main.c db.h
	gcc -c main.c -o main.o

db.o: db.c db.h
	gcc -c db.c -o db.o

storage.o: storage.c storage.h
	gcc -c storage.c -o storage.o

clean:
	rm -f db.o main.o storage.o lab5
