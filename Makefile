NAME = minishell

FLAGS = -g -Wall -Wextra -Werror

SRC = builtin.c builtin_env.c env.c exec.c main.c builtin_cd.c prompt.c\
	builtin_echo.c signal.c builtin_setenv.c builtin_cd_utils.c

OBJ_TMP = $(SRC:.c=.o)

OBJ = $(addprefix obj/, $(OBJ_TMP))

INCLUDE = ./includes/minishell.h

all: $(NAME)

obj/%.o: src/%.c
	gcc -o $@ $(FLAGS) -c $?

$(NAME): obj/ $(INCLUDE) $(OBJ)
	@make -C libft
	gcc -g $(OBJ) -o $(NAME) -I./includes -L libft -lft
	@echo "MINISHELL COMPILED"

obj/ :
	@mkdir obj 2> /dev/null

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
