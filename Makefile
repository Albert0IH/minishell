# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 10:51:22 by ahamuyel          #+#    #+#              #
#    Updated: 2024/11/19 11:28:58 by ahamuyel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src/
INCLUDES = -INCLUDES
LIBS = -lreadline
SRC = $(SRC_DIR)main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

