NAME = minishell

SRC = ${wildcard src/*/*.c src/*.c}

OBJ = ${SRC:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra # -Werror

%.o:%.c headerfile.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline libft/libft.a

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


m: all
	./minishell

.PHONY : all clean fclean re
