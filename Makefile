CC=gcc

all: shapes circle ring semicircle square ellipse

shapes:
	$(CC) -o shapes shapes.c

circle:
	$(CC) -o circle circle.c

ring:
	$(CC) -o ring ring.c

semicircle:
	$(CC) -o semicircle semicircle.c

square:
	$(CC) -o square square.c

ellipse:
	$(CC) -o ellipse ellipse.c 

clean:
	rm -f shapes
	rm -f circle
	rm -f ring
	rm -f semicircle
	rm -f square
	rm -f ellipse

.PHONY: all clean

	
