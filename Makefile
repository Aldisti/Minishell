NAME	= minishell

SRC			= main.c executor.c parser.c 
USRC		= Utils/isspace.c Utils/strdup.c Utils/strlen.c Utils/substr.c
PIPEX		= pipex/command.c pipex/pipex_utils.c pipex/pipex.c pipex/spaces.c
COMMANDS	= commands/cd.c commands/pwd.c

OBJ		= $(SRC:%.c=%.o) $(USRC:%.c=%.o) $(PIPEX:%.c=%.o) $(COMMANDS:%.c=%.o)

CC		= cc
FLAGS	= -Wall -Wextra -Werror
RDLN_M	= -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include
RDLN_L	= -lreadline
RM		= rm -f

$(NAME): libft_comp $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(RDLN_L) $(RDLN_M) -L./libft -lft -o $(NAME)

all: $(NAME)

mac: $(OBJ)
	$(CC) $(UOBJ) $(OBJ) $(RDLN_L) $(RDLN_M) -o $(NAME)

libft_comp:
	make -C libft

linux: $(OBJ)
	$(CC) $(UOBJ) $(OBJ) $(RDLN_L) -o $(NAME)

clean:
	make -C libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all

test: fclean all
	$(RM) $(OBJ)

.PHONY: all clean fclean re test
