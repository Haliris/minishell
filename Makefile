NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -pthread -g3

SRCDIR	= src
OBJDIR	= obj
CFILES	= main.c -lreadline\
		  parser.c \
		  parser_utils.c \
		  build_pipe_table.c \
		  get_cmd_pipe.c \
		  build_redirect_table.c \
		  check_parsing_errors.c \
		  parse_here_doc.c \
		  get_next_line.c \
		  get_next_line_utils.c \
		  lex_bools1.c \
		  lex_clean_exit.c \
		  lex_env_vars.c \
		  lex_executables.c \
		  lex_retrieve_tk1.c \
		  lex_retrieve_tk2.c \
		  lex_token_utils.c \
		  lexer.c \
		  validate_input.c \
		  validate_tokens.c
INCS	=	-I ./include \
			-I ./libft

vpath %.c ./ src src/here_doc_parsing src/here_doc_parsing/get_next_line src/parser src/lexer/

OBJS	= $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

all: $(OBJDIR) $(NAME)
	@echo "Making minishell..."

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	make -C ./libft all
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) -L ./libft/ -lft

clean:
	@echo "Cleaning object files..."
	make -C ./libft/ clean
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Removing minishell..."
	rm -f ./libft/libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
