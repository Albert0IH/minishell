
NAME = minishell

CC = cc 
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I./includes
SRCS_DIR = srcs/
OBJS_DIR = objs/

SRCS = 	$(SRCS_DIR)main.c		\
		$(SRCS_DIR)signals.c	\
		$(SRCS_DIR)parsing.c 	\
		$(SRCS_DIR)tokens.c 	\
		$(SRCS_DIR)expand.c 	\
		$(SRCS_DIR)execute.c 	\
		$(SRCS_DIR)builtins.c	\
		$(SRCS_DIR)ft_cd.c 		\
		$(SRCS_DIR)ft_echo.c 	\
		$(SRCS_DIR)ft_pwd.c 	\
		$(SRCS_DIR)ft_export.c 	\
		$(SRCS_DIR)ft_unset.c 	\
		$(SRCS_DIR)ft_env.c 	\
		$(SRCS_DIR)ft_exit.c 	\
		$(SRCS_DIR)redirecting.c\
		$(SRCS_DIR)pipes.c 		\
		$(SRCS_DIR)clean.c
OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

LIBS = -lreadline
LIBFT = ./libft 
LIBFT_FLAGS = -L$(LIBFT) -lft

all:$(NAME)
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
$(NAME):$(OBJS)
	@make -s -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFT_FLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)
	@make clean -s -C $(LIBFT)

fclean: clean
	rm -rf $(NAME)
	@make fclean -s -C $(LIBFT)

re: fclean all
