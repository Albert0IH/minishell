LIBS = -lreadline
LIBFT = ./libft 
LIBFT_FLAGS = -L$(LIBFT) -lft
	@make -s -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFT_FLAGS) -o $(NAME)
	@make clean -s -C $(LIBFT)
	@make fclean -s -C $(LIBFT)
