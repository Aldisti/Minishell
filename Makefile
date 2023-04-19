# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marco <marco@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 18:28:42 by adi-stef          #+#    #+#              #
#    Updated: 2023/04/18 22:27:26 by marco            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC			= main.c
INIT_SRC	= $(wildcard Init/*.c)
UTILS_SRC	= $(wildcard Utils/*.c)
PIPEX_SRC	= $(wildcard Pipex/*.c)
PARSER_SRC	= $(wildcard Parser/*.c)
SIGN_SRC	= $(wildcard Signals/*.c)
READ_SRC	= $(wildcard Readline/*.c)
COMM_SRC	= $(wildcard Commands/*.c)
EXP_SRC		= $(wildcard Expansions/*.c)
RED_SRC		= $(wildcard Redirection/*.c)
PAR_SRC		= $(wildcard Parentheses/*.c)

OBJ		= $(SRC:%.c=%.o) $(PARSER_SRC:%.c=%.o) $(PIPEX_SRC:%.c=%.o)	\
			$(UTILS_SRC:%.c=%.o) $(COMM_SRC:%.c=%.o) $(INIT_SRC:%.c=%.o)	\
			$(EXP_SRC:%.c=%.o) $(SIGN_SRC:%.c=%.o) $(PAR_SRC:%.c=%.o) \
			$(RED_SRC:%.c=%.o) ${READ_SRC:%.c=%.o}

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


SRC_COUNT_TOT = $(shell expr $(shell echo -n $(SRC) $(PARSER_SRC) $(PIPEX_SRC) $(UTILS_SRC) $(COMM_SRC) $(INIT_SRC) \
		 $(EXP_SRC) $(PAR_SRC) $(RED_SRC) ${READ_SRC} | wc -w))
SRC_COUNT = 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(RDLN_L) $(RDLN_M) -o $(NAME)
	@echo -e "\r\033[KMINISHELL  CREATED  SUCCESSUFULLY\n$(RESET)"
	@echo -e "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"
	@echo -e "███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      "
	@echo -e "████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██      "
	@echo -e "██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██      "
	@echo -e "██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██      "
	@echo -e "██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████ "
	@echo -e "\n$(BLUE)-------------------------------------------------------------------------\n$(RESET)"
	@echo -e "$(YELLOW)Made with love and bestemmie by Adi-stef, Afraccal, Gpanico, Mpaterno.\n$(RESET)"
	@echo -e "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"

%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@printf "$(GREEN)\r%100s\r[%d/%d (%d%%)] $(GREEN)$<" "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)

all: $(NAME)

linux: $(OBJ)
	$(CC) -fsanitize=address $(OBJ) $(RDLN_L) -o $(NAME)

clean:
	@printf "$(RED)\nRemoving Object files...\n$(RESET)"
	@echo -e "$(BLUE)-------------------------------------------------------------------------$(RESET)"
	@$(RM) $(OBJ)
	@echo -e "$(RED)Object files removed\n$(RESET)"
	
fclean: clean
	@printf "$(RED)\nRemoving program executable...\n$(RESET)"
	@echo -e "$(BLUE)-------------------------------------------------------------------------$(RESET)"
	@$(RM) $(NAME)
	@echo -e "$(RED)MINISHELL REMOVED\n$(RESET)"
	
re: fclean all

test: fclean linux clean

leaks: re
	@valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re test
