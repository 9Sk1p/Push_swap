NAME		= push_swap

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -Iincludes -Ilibft

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		= src/main.c \
			src/algorithms/complex.c \
			src/algorithms/medium.c \
			src/algorithms/simple.c \
			src/algorithms/sort_3.c \
			src/algorithms/strategy.c \
			src/operations/execute.c \
			src/operations/index.c \
			src/operations/push.c \
			src/operations/rotate.c \
			src/operations/swap.c \
			src/parsing/disorder.c \
			src/parsing/options.c \
			src/parsing/parse_args.c \
			src/parsing/validate.c \
			src/utils/bench.c \
			src/utils/free_and_error.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re