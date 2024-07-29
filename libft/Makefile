# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/24 16:14:13 by jteissie          #+#    #+#              #
#    Updated: 2024/07/29 11:40:50 by bthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CCFLAGS = -Wall -Wextra -Werror -g3

NAME = libft.a

SRC = 		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_memcmp.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putnbr_fd.c \
		ft_putendl_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strcmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strjoin3.c \
		ft_strreplacejoin.c \
		ft_strarrjoin.c \
		ft_printf/ft_printf.c \
		ft_printf/format_triage.c \
		ft_printf/write_utils.c 

BONUS = 	ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJS = $(SRC:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -I ./ -o $@

clean : 
	rm -f $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -f $(NAME)

bonus : $(BONUS_OBJS)
	ar rc $(NAME) $(BONUS_OBJS)

re : fclean all

.PHONY : all clean fclean re bonus
