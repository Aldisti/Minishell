# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afraccal <afraccal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 18:28:42 by adi-stef          #+#    #+#              #
#    Updated: 2023/03/23 10:19:30 by afraccal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC		= main.c Init/env_set.c Parser/parser.c Pipex/command_parser.c \
		  Pipex/command.c Pipex/pipex_utils.c Pipex/pipex.c \
		  Pipex/trim_strs.c
USRC	= Utils/calloc.c Utils/isspace.c Utils/itoa.c Utils/split.c	\
			Utils/strdup.c Utils/strrchr.c Utils/strtrim.c \
			Utils/strjoin.c Utils/strlen.c Utils/strncmp.c Utils/substr.c \
			Utils/realloc.c Utils/lstnew.c Utils/lstlast.c \
			Utils/lstadd_back.c

OBJ		= $(SRC:%.c=%.o) $(USRC:%.c=%.o)

CC		= cc
FLAGS	= -Wall -Wextra -Werror
RDLN_M	= -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include
RDLN_L	= -lreadline
RM		= rm -f
	
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(RDLN_L) $(RDLN_M) -o $(NAME)
	@echo "\033[0;32mCreating        MINISHELL\033[0;0m"
	
all: $(NAME)

linux: $(OBJ)
	$(CC) $(OBJ) $(RDLN_L) -o $(NAME)

clean:
	$(RM) $(OBJ)
	@echo "\033[0;31mCleaning        folder objs\033[0;0m"
	
fclean: clean
	$(RM) $(NAME)
	@echo "\033[0;31mRemove          MINISHELL\033[0;0m"
	
re: fclean all

test: fclean linux
	$(RM) $(OBJ)

.PHONY: all clean fclean re test
