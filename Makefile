NAME	= minishell

SRC		= main.c executor.c parser.c
USRC	= Utils/isspace.c Utils/strdup.c Utils/strlen.c Utils/substr.c

OBJ		= $(SRC:%.c=%.o) $(USRC:%.c=%.o)

CC		= cc
FLAGS	= -Wall -Wextra -Werror
RDLN_M	= -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include
RDLN_L	= -lreadline
RM		= rm -f

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(RDLN_L) $(RDLN_M) libft.a -o $(NAME)

all: $(NAME)

mac: $(OBJ)
	$(CC) $(UOBJ) $(OBJ) $(RDLN_L) $(RDLN_M) -o $(NAME)

linux: $(OBJ)
	$(CC) $(UOBJ) $(OBJ) $(RDLN_L) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: fclean all
	$(RM) $(OBJ)

.PHONY: all clean fclean re test
