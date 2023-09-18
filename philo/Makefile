# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 14:30:42 by nfaust            #+#    #+#              #
#    Updated: 2023/09/07 17:22:04 by nfaust           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wextra -Wall  -g3
REMOVE = rm -f

NAME = philo

HEADER = philo.h \
		error_codes.h

SOURCES = src/philo.c \
		src/atoi.c \
		src/parsing.c \
		src/utils.c \
		src/actions.c

OBJ = $(SOURCES:.c=.o)

all:	${NAME}

${NAME}:	${OBJ}
	${CC} ${FLAGS} ${OBJ} -o ${NAME} -lpthread

clean:
	${REMOVE} ${OBJ}

fclean:	clean
	${REMOVE} ${NAME}

%.o : %.c ${HEADER} Makefile
	${CC} ${FLAGS}  -c $< -o $@ -I ./headers

re:    fclean
	${MAKE} all

.PHONY: re fclean all clean