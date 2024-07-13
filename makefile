output: all_poem.o
        gcc -Wall all_poem.o -o output

all_poem.o: all_poem.c
        gcc -Wall -std=c99 -c all_poem.c

clean:
        rm -f *.o output
