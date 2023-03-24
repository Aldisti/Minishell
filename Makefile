# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afraccal <afraccal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 18:28:42 by adi-stef          #+#    #+#              #
#    Updated: 2023/03/24 11:11:19 by afraccal         ###   ########.fr        #
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

%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "\033[0;32mCompiling... %-33.33s\r" $@

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(RDLN_L) $(RDLN_M) -o $(NAME)
	@echo "MINISHELL  CREATED  SUCCESSUFULLY\n\033[0;0m"

all: $(NAME)

linux: $(OBJ)
	$(CC) $(OBJ) $(RDLN_L) -o $(NAME)

clean:
	@printf "\033[0;31m\nRemoving Object files...\n\n\033[0;0m"
	@$(RM) $(OBJ)
	@echo "\033[0;31m\nObject files removed\n\033[0;0m"
	
fclean: clean
	@printf "\033[0;31m\nRemoving program executable...\n\n\033[0;0m"
	@$(RM) $(NAME)
	@echo "\033[0;31m\nMINISHELL REMOVED\n\033[0;0m"
	
re: fclean all

test: fclean linux
	$(RM) $(OBJ)

leaks: all
	@leaks --atExit -- ./$(NAME)

.PHONY: all clean fclean re test
