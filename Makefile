#Nome do executável
NAME = minishell
#Compilador e flags de compilação
CC = cc 
CFLAGS = -Wall -Wextra -Werror
#Directórios
INCLUDES = -I./includes
SRCS_DIR = srcs/
OBJS_DIR = objs/
#Ficheiros .c e .o
SRCS = $(SRCS_DIR)main.c $(SRCS_DIR)parsing.c $(SRCS_DIR)execute.c $(SRCS_DIR)builtins.c $(SRCS_DIR)redirecting.c $(SRCS_DIR)pipes.c $(SRCS_DIR)signals.c
OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)
#Libs para funcs auxíliares
LIBS = -lreadline
LIBFT = ./libft 
LIBFT_FLAGS = -L$(LIBFT) -lft
#Regras de complição
all:$(NAME)
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
$(NAME):$(OBJS)
	@make -s -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFT_FLAGS) -o $(NAME)
#Remover os .o
clean:
	rm -rf $(OBJS_DIR)
	@make clean -s -C $(LIBFT)
#Limpar o projeto
fclean: clean
	rm -rf $(NAME)
	@make fclean -s -C $(LIBFT)
#Recompilação
re: fclean all