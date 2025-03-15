NAME = minishell
LIB = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft/include -Iinclude -g3
SRCS =	src/main.c \
		src/parsing/free_parser.c \
		src/parsing/handle_file/get_fd.c \
		src/parsing/handle_file/get_file_utils.c \
		src/parsing/handle_file/create_file_list.c \
		src/parsing/handle_file/extract_file.c \
		src/parsing/handle_file/shearch_file.c \
		src/parsing/handle_file/realloc_fd.c \
		src/parsing/handle_file/free_list_fd.c \
		src/parsing/tokenisation/get_bool_red.c \
		src/parsing/tokenisation/get_bool_red_utils.c \
		src/parsing/tokenisation/get_bool_red_utils2.c \
		src/parsing/tokenisation/get_bool_pipe.c \
		src/parsing/tokenisation/handle_token_error.c \
		src/parsing/tokenisation/token_error_utils.c \
		src/parsing/cat_fd_list.c \
		src/parsing/init.c \
		src/parsing/utils.c \
		src/parsing/handle_pipe/get_pipe.c \
		src/parsing/handle_pipe/handle_pipe.c \
		src/parsing/handle_quote/get_quote.c \
		src/parsing/handle_quote/get_word.c \
		src/parsing/handle_quote/handle_inside_quote.c \
		src/parsing/handle_quote/realloc_quote.c \
		src/parsing/handle_quote/get_quote_utils.c \
		src/parsing/handle_quote/get_quote_utils_2.c \
		src/parsing/handle_quote/quote_or_not.c \
		src/parsing/handle_quote/var_init.c \
		src/parsing/handle_quote/free_quote.c \
		src/parsing/handle_quote/free_quote_2.c \
		src/signals.c \
		src/init_env.c \
		src/expansion_var.c \
		src/expansion_var_bis.c \
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
		src/utils/main_utils.c \
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
		src/exec1/fork.c \
		src/exec1/exec.c \
		src/exec1/free_exec.c \
		src/exec1/here_doc.c \
		src/exec1/here_doc_init.c \
		src/exec1/main_exec.c \
		src/exec1/dup.c \
		src/exec1/file_manager.c \
		src/exec1/pipe.c

OBJ_DIR = obj

OBJS = $(patsubst %.c,%.o,$(SRCS))
OBJS := $(patsubst src/%, $(OBJ_DIR)/src/%, $(OBJS))

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIB) -lreadline -o $(NAME)

$(LIB):
	$(MAKE) -C libft

$(OBJ_DIR)/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: all clean fclean re bonus
