CC=cc
CFLAGS= -Wall -Wextra -Werror #-fsanitize=thread
NAME=philo
SRCS=main.c monitor_routine.c parse.c philo_routine.c simulation.c utils.c
OBJS=$(SRCS:.c=.o)


all: $(NAME)
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
