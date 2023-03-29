# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 18:28:42 by adi-stef          #+#    #+#              #
#    Updated: 2023/03/29 12:22:20 by mpaterno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC			= main.c
PARSER_SRC	= $(wildcard Parser/*.c)
PIPEX_SRC	= $(wildcard Pipex/*.c)
UTILS_SRC	= $(wildcard Utils/*.c)
INIT_SRC	= $(wildcard Init/*.c)
EXP_SRC		= $(wildcard Expansions/*.c)
COMM_SRC	= $(wildcard Commands/*.c)

OBJ		= $(SRC:%.c=%.o) $(PARSER_SRC:%.c=%.o) $(PIPEX_SRC:%.c=%.o)	\
			$(UTILS_SRC:%.c=%.o) $(COMM_SRC:%.c=%.o) $(INIT_SRC:%.c=%.o)	\
			$(EXP_SRC:%.c=%.o)

CC		= cc
FLAGS	= -Wall -Wextra -Werror
RDLN_M	= -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include
RDLN_L	= -lreadline
RM		= rm -f

%.o : %.c
	@$(CC) $(FLAG) -c $< -o $@
	@printf "\033[0;32mCompiling... %-33.33s\r" $@

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(RDLN_L) $(RDLN_M) -o $(NAME)
	@echo "MINISHELL  CREATED  SUCCESSUFULLY\033[0;0m"

all: $(NAME)

linux: $(OBJ)
	$(CC) $(OBJ) $(RDLN_L) -o $(NAME)

clean:
	@printf "\033[0;31mRemoving Object files...\n\033[0;0m"
	@$(RM) $(OBJ)
	@echo "\033[0;31mObject files removed\n\033[0;0m"
	
fclean: clean
	@printf "\033[0;31mRemoving program executable...\n\033[0;0m"
	@$(RM) $(NAME)
	@echo "\033[0;31mMINISHELL REMOVED\n\033[0;0m"
	
re: fclean all

test: fclean linux clean

leaks: all
	@valgrind ./$(NAME)

.PHONY: all clean fclean re test
