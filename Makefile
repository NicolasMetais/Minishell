SRCS = 	src/main.c \
		src/welcome.c \
		src/signals.c \
		src/init_env.c \
		src/var_manager.c \
		src/cmd/cd.c \
		src/cmd/echo.c \
		src/cmd/exit.c \
		src/cmd/pwd.c \
		src/cmd/exec.c \
		src/cmd/export.c \
		src/cmd/env.c \
		src/cmd/exit_display.c \
		src/cmd/builtin.c \
		src/utils/ft_get_env.c \
		src/utils/get_env_size.c \
		src/utils/rotate_env.c \
		src/utils/update_env_tab.c \
		src/utils/ft_strcmp.c \
		src/error_manager/errors.c \
		src/free/free_env.c \
		src/free/free.c \
		src/free/garbage_collector.c \

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -Ilibft/include -Iinclude

NAME = minishell

LIB = libft/libft.a

all: $(NAME)


$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIB) -lreadline -o $(NAME)

$(LIB):
	$(MAKE) -C $(@D)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

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