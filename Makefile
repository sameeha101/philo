NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = main.c parsing.c \
	checkforking.c forking.c \
	destroyer.c initializer.c \
	routines.c screening.c \
	utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -g3 -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=thread $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re