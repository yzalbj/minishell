NAME = minishell

FLAGS = -g -Wall -Wextra -Werror

SRC = builtin.c builtin_env.c env.c exec.c main.c\

OBJ = $(SRC:.c=.o)

INCLUDE = ./includes/minishell.h

all: $(NAME)

%.o: %.c $(INCLUDE)
	gcc $(FLAGS) -c $<

$(NAME): $(OBJ)
	@make -C libft
	gcc -g $(OBJ) -o $(NAME) -I./includes -L libft -lft
	@echo "MINISHELL COMPILED"

clean:
	@make clean -C libft
	@rm -rf $(OBJ)
	@echo "OBJECTS DELETED"

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "MINISHELL DELETED"

re: fclean all

.PHONY: make re clean fclean
