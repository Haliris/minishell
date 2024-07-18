NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -pthread -g3
LDFLAGS = -lreadline

SRCDIR	= src
OBJDIR	= obj
CFILES	= main.c \
		  init.c \
		  cleanup.c \
		  get_prompt.c \
		  parser.c \
		  parser_utils.c \
		  parser_clean_exit.c \
		  build_redirect_table.c \
		  execute_commands.c \
		  execution_utils.c \
		  build_env.c \
		  process_command.c \
		  redir_child.c \
		  parse_here_doc.c \
		  here_doc_utils.c \
		  get_next_line.c \
		  get_next_line_utils.c \
		  lex_bools1.c \
		  lex_executables.c \
		  lex_retrieve_tk1.c \
		  lex_retrieve_tk2.c \
		  lex_token_utils.c \
		  lex_expand_str_vars.c \
		  lex_utils.c \
		  lexer.c \
		  validate_input.c \
		  validate_tokens.c \
		  signals.c \
		  built_ins.c \
		  cd.c \
		  echo.c \
		  pwd.c \
		  exit.c \
		  export.c \
		  env.c \
		  varlist_add.c \
		  varlist_del.c \
		  varlist_utils.c
INCS	=	-I ./include \
			-I ./libft

vpath %.c ./ src/ src/here_doc_parsing src/here_doc_parsing/get_next_line src/parser src/lexer/ src/execution src/built_ins

OBJS	= $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

all: $(OBJDIR) $(NAME)
	@echo "Making minishell..."

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	make -C ./libft all
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) -L ./libft/ -lft $(LDFLAGS)

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
