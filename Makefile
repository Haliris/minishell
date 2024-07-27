NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g3
LDFLAGS = -lreadline

SRCDIR	= src
OBJDIR	= obj
CFILES	= main.c \
		  main_utils.c \
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
		  vector_split.c \
		  process_command.c \
		  redir_child.c \
		  redir_child_utils.c \
		  parse_here_doc.c \
		  here_doc_utils.c \
		  lex_bools1.c \
		  lex_bools2.c \
		  lex_executables.c \
		  lex_retrieve_str_tk.c \
		  lex_concat_str_tks.c \
		  lex_retrieve_tk.c \
		  lex_token_utils.c \
		  lex_expand_str_vars.c \
		  lex_utils.c \
		  lexer.c \
		  validate_input.c \
		  validate_tokens.c \
		  signals.c \
		  signals_utils.c \
		  built_ins.c \
		  cd.c \
		  echo.c \
		  pwd.c \
		  exit.c \
		  export.c \
		  env.c \
		  unset.c \
		  varlist_add.c \
		  varlist_del.c \
		  varlist_utils.c
INCS	=	-I ./include \
			-I ./libft

vpath %.c ./ src/ src/here_doc_parsing src/parser src/lexer/ src/execution src/built_ins

OBJS	= $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

all: $(OBJDIR) $(NAME)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	make -C ./libft all
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) -L ./libft/ -lft $(LDFLAGS)
	@echo "> Minishell build done!"

clean:
	@echo "> Cleaning object files..."
	make -C ./libft/ clean
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "> Removing minishell..."
	rm -f ./libft/libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
