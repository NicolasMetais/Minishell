SRCS = 	src/main.c \
		src/welcome.c \
		src/parsing/free_parser.c \
		src/parsing/get_fd.c \
		src/parsing/getpath.c \
		src/parsing/init.c \
		src/parsing/utils.c \

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibft/include -Iinclude -g3
LDFLAGS = -fsanitize=address

NAME = minishell

LIB = libft/libft.a

all: $(NAME)


$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIB) $(LDFLAGS) -lreadline -o $(NAME)

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