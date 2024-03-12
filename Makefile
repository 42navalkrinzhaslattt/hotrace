NAME	= hotrace

SRC		= hotrace.c utils.c utils2.c create_art.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

SRC_DIR	= srcs/

OBJ	= $(addprefix $(SRC_DIR), $(SRC:.c=.o))

INC_DIR = includes

CC		= cc

CFLAGS	= -Wall -Werror -Wextra -g

%.o: %.c
	$(CC) $(CFLAGS) -I ./includes -c  $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -g3 -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re