# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 10:51:22 by ahamuyel          #+#    #+#              #
#    Updated: 2024/11/30 01:23:03 by ahamuyel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = ./srcs
OBJS_DIR = ./objs
INCLUDES = -I./includes

SRCS =	$(SRCS_DIR)/main.c \
		$(SRCS_DIR)/token.c \
		$(SRCS_DIR)/execute.c \
		$(SRCS_DIR)/signals.c 

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

LIBS = -lreadline
LIBFT = ./libft

LIBFT_FLAGS = -L$(LIBFT) -lft

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


$(NAME): $(OBJS)
	@make -s -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFT_FLAGS) -o $(NAME)


clean:
	rm -rf $(OBJS_DIR)
	@make clean -s -C $(LIBFT)

fclean: clean
	rm -rf $(NAME)
	@make fclean -s -C $(LIBFT)

re: fclean all
