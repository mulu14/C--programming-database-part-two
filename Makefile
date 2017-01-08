CC=gcc
FLAGS=-Wall -std=c11 -ggdb

main: main.o tree.o list.o shelf.o ware.o utilise.o wareinfo.o shelfinfo.o compare.o
	$(CC) $(FLAGS) -o $@ $^

tree: tree.o list.o ware.o shelf.o utilise.o  compare.o
	$(CC) $(FLAGS) -o $@ $^
utilise: utilise.o
	$(CC) $(FLAGS) -o $@ -c $^
compare: compare.o
	$(CC) $(FLAGS) -o $@ -c$^
shelf: shelf.o utilise.o
	$(CC) $(FLAGS) -o $@ -c $^
shelfinfo: shelfinfo.o utilise.o
	$(CC) $(FLAGS) -o $@ -c $^
list: list.o shelf.o compare.o
	$(CC) $(FLAGS) -o $@ -c $^
wareinfo: wareinfo.o utilise.o shelfinfo.o
	$(CC) $(FLAGS) -o $@ -c $S^
ware: ware.o
	$(CC) $(FLAGS) -o $@ -c $^

clean:
	rm -f   
	rm -f *.o 
	rm -rf *.dSYM  
	rm -f *~

tobias:
	$(CC) $(FLAGS) main.c tree.c list.c shelf.c ware.c utilise.c wareinfo.c shelfinfo.c compare.c -o main
