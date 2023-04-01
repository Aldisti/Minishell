# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 18:28:42 by adi-stef          #+#    #+#              #
#    Updated: 2023/03/29 15:00:35 by adi-stef         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC			= main.c
EXP_SRC		= $(wildcard Expansions/*.c)
COMM_SRC	= $(wildcard Commands/*.c)
SIGN_SRC	= $(wildcard Signals/*.c)
PARSER_SRC	= $(wildcard Parser/*.c)
PIPEX_SRC	= $(wildcard Pipex/*.c)
UTILS_SRC	= $(wildcard Utils/*.c)
INIT_SRC	= $(wildcard Init/*.c)

OBJ		= $(SRC:%.c=%.o) $(PARSER_SRC:%.c=%.o) $(PIPEX_SRC:%.c=%.o)	\
			$(UTILS_SRC:%.c=%.o) $(COMM_SRC:%.c=%.o) $(INIT_SRC:%.c=%.o)	\
			$(EXP_SRC:%.c=%.o) $(SIGN_SRC:%.c=%.o)

CC		= cc
FLAGS	= -Wall -Wextra -Werror
RDLN_M	= -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include
RDLN_L	= -lreadline
RM		= rm -f

RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
RESET	= \033[0;0m

%.o : %.c
	@$(CC) $(FLAG) -c $< -o $@
	@printf "$(GREEN)Compiling... %-33.33s\r" $@

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(RDLN_L) $(RDLN_M) -o $(NAME)
	@echo "MINISHELL  CREATED  SUCCESSUFULLY\n$(RESET)"
	@echo "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"
	@echo "███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      "
	@echo "████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██      "
	@echo "██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██      "
	@echo "██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██      "
	@echo "██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████ "
	@echo "\n$(BLUE)-------------------------------------------------------------------------\n$(RESET)"
	@echo "$(YELLOW)Made with love and bestemmie by Gpanico, Mpaterno, Adi-stef and Afraccal\n$(RESET)"
	@echo "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"

all: $(NAME)

linux: $(OBJ)
	$(CC) -fsanitize=address $(OBJ) $(RDLN_L) -o $(NAME)

clean:
	@printf "$(RED)\nRemoving Object files...\n$(RESET)"
	@echo "$(BLUE)-------------------------------------------------------------------------$(RESET)"
	@$(RM) $(OBJ)
	@echo "$(RED)Object files removed\n$(RESET)"
	
fclean: clean
	@printf "$(RED)\nRemoving program executable...\n$(RESET)"
	@echo "$(BLUE)-------------------------------------------------------------------------$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)MINISHELL REMOVED\n$(RESET)"
	
re: fclean all

test: fclean linux clean

leaks: re
	@valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re test
