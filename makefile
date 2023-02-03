all: exec

tri: tri.c
	gcc -c tri.c -o tri.o

list: list.c
	gcc -c list.c -o list.o

tree: tree.c
	gcc -c tree.c -o tree.o

exec: list tree tri
	gcc tri.o list.o tree.o -o tri

clean: 
	rm -f *.txt tri *.o
