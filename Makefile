CC = cc
FLAGS = -Wextra -Wall -Werror -g3
REMOVE = rm -f

NAME = philo

HEADER = headers/philo.h

SOURCES = src/philo.c

OBJ = $(SOURCES:.c=.o)

all:	${NAME}

${NAME}:     ${OBJ}
	${CC} ${FLAGS} ${OBJ} -o ${NAME}

clean:
	${REMOVE} ${OBJ}

fclean:	clean
	${REMOVE} ${NAME}

keep_o: all clean

%.o : %.c ${HEADER} Makefile
	${CC} ${FLAGS}  -c $< -o $@ -I .

re:    fclean
	${MAKE} all

.PHONY: re fclean all clean libft keep_o ft_printf