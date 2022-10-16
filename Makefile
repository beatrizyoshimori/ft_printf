NAME = libftprintf.a

SRC = ft_printf.c

OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	cc $(CFLAGS) -c $< -o $@
	ar rcs $(NAME) $@

.PHONY: all clean fclean re bonus