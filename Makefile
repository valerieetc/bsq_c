all: my_bsq

my_bsq: my_bsq.o
	gcc -Wall -Wextra -Werror -o my_bsq my_bsq.o


my_bsq.o: my_bsq.c
	gcc -Wall -Wextra -Werror -c my_bsq.c

clean:
	rm -f *.o

fclean: clean
	rm -f my_bsq

re: fclean all