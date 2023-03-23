# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 18:28:42 by adi-stef          #+#    #+#              #
#    Updated: 2023/03/23 16:30:05 by adi-stef         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC		= executor.c parser.c exec_utils.c
USRC	= Utils/calloc.c Utils/countn.c Utils/isspace.c Utils/itoa.c	\
			Utils/joiner.c Utils/split.c Utils/strdup.c Utils/strjoin.c	\
			Utils/strlen.c Utils/strncmp.c Utils/substr.c

OBJ		= $(SRC:%.c=%.o) $(USRC:%.c=%.o)

CC		= cc
FLAGS	= -Wall -Wextra -Werror
RDLN_M	= -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include
RDLN_L	= -lreadline
RM		= rm -f

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(RDLN_L) $(RDLN_M) -o $(NAME)

all: $(NAME)

linux: $(OBJ)
	$(CC) -g $(OBJ) $(RDLN_L) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: fclean linux
	$(RM) $(OBJ)

.PHONY: all clean fclean re test
