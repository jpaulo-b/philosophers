# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpaulo-b <jpaulo-b@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/19 15:56:21 by jpaulo-b          #+#    #+#              #
#    Updated: 2026/05/28 16:34:11 by jpaulo-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror #-pthread -g3 -fsanitize=thread -O3 -march=native
RM = rm -f

SRC = actions.c \
	init.c \
	main.c \
	threads.c \
	utils.c \
	utils2.c
OBJ = $(SRC:.c=.o)
TARGET = philo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: all clean fclean re
