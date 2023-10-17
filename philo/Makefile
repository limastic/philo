# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 14:30:42 by nfaust            #+#    #+#              #
#    Updated: 2023/10/17 20:29:56 by nfaust           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wextra -Wall -Werror -g3 -fsanitize=thread
REMOVE = rm -f

NAME = philo

HEADER = headers/philo.h \
		headers/error_codes.h

SOURCES = src/philo.c \
		src/atoi.c \
		src/parsing.c \
		src/utils.c \
		src/actions.c \
		src/fork_actions.c \
		src/monitoring.c \
		src/forks_mutex.c \
		src/custom_printf.c

OBJ = $(SOURCES:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lpthread

clean:
	$(REMOVE) $(OBJ)

fclean:	clean
	$(REMOVE) $(NAME)

%.o:%.c $(HEADER) Makefile
	$(CC) $(FLAGS)  -c $< -o $@ -I .

re:    fclean
	$(MAKE) all

.PHONY: re fclean all clean
