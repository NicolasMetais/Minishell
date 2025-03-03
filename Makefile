SRCS = 	src/main.c \
		src/parsing/free_parser.c \
		src/parsing/get_fd.c \
		src/parsing/init.c \
		src/parsing/utils.c \
		src/parsing/utils_.c \
		src/parsing/realloc_cmd.c \
		src/parsing/get_fd_in_utils.c \
		src/parsing/handle_pipe/get_pipe.c \
		src/parsing/handle_pipe/handle_pipe.c \
		src/parsing/handle_quote/get_quote.c \
		src/parsing/handle_quote/realloc_quote.c \
		src/parsing/handle_quote/get_quote_utils.c \
		src/parsing/handle_quote/get_quote_utils_2.c \
		src/parsing/handle_quote/quote_or_not.c \
		src/parsing/handle_quote/var_init.c \
		src/parsing/handle_quote/free_quote.c \
		src/parsing/handle_quote/free_quote_2.c \
		src/welcome.c \
		src/signals.c \
		src/init_env.c \
		src/var_replace.c \
		src/var_replace_bis.c \
		src/cmd/cd.c \
		src/cmd/echo.c \
		src/cmd/exit.c \
		src/cmd/pwd.c \
		src/cmd/export.c \
		src/cmd/export_marked.c \
		src/cmd/export_var.c \
		src/cmd/unset.c \
		src/cmd/env.c \
		src/cmd/builtin.c \
		src/utils/ft_atol.c \
		src/utils/ft_get_env.c \
		src/utils/get_env_size.c \
		src/utils/rotate_env.c \
		src/utils/update_env_tab.c \
		src/utils/ft_strcmp.c \
		src/utils/env_exist.c \
		src/error_manager/errors.c \
		src/error_manager/errors_bis.c \
		src/free/free_env.c \
		src/free/free.c \
		src/free/garbage_collector.c \

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibft/include -fsanitize=address -Iinclude -g3

NAME = minishell

LIB = libft/libft.a

all: $(NAME)


$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIB) -lreadline -fsanitize=address -o $(NAME)

$(LIB):
	$(MAKE) -C $(@D)

.c.o:
	$(CC) $(CFLAGS)  -c $< -o $@

bonus:
	make

clean:
	rm -rf $(OBJS)
	make clean -C ./libft

fclean: clean 
	rm -f $(NAME)
	make fclean -C ./libft

re:	fclean all

.PHONY: all clean fclean re .c.o