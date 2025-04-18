CC=cc
CFLAGS=  -fsanitize=thread #-Wall -Wextra -Werror
NAME=philo
SRCS=main.c monitor_routine.c parse.c philo_routine.c simulation.c
OBJS=$(SRCS:.c=.o)


all: $(NAME) clean
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
