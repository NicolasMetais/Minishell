SRCS = 	src/main.c \
		src/welcome.c \
		src/parsing/free_parser.c \
		src/parsing/get_fd.c \
		src/parsing/get_path.c \
		src/parsing/get_cmd.c \
		src/parsing/init.c \
		src/parsing/utils.c \
		src/parsing/realloc_cmd.c \
		src/parsing/get_fd_in_utils.c \

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibft/include -Iinclude -g3

NAME = minishell

LIB = libft/libft.a

all: $(NAME)


$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIB) -lreadline -o $(NAME)

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