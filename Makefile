NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -pthread -g3

SRCDIR	= src
OBJDIR	= obj
CFILES	= main.c \
		  parse.c
SRC		= $(addprefix $(SRCDIR)/, $(CFILES))
OBJS	= $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))
INCS	=	-I ./include \
			-I ./libft

all: $(OBJDIR) $(NAME)
	@echo "Making minishell..."

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	make -C ./libft all
	$(CC) $(CFLAGS) $(INCS) -L ./libft/ -lft -o $(NAME) $(OBJS)

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