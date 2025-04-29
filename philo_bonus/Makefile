# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 18:16:10 by aalahyan          #+#    #+#              #
#    Updated: 2025/04/29 16:19:40 by aalahyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_bonus
CC=cc
CFLAGS= -Wall -Wextra -Werror

SRCS= main.c parse.c utils.c start_simulation.c philo_child_proc.c get_unique_sem_name.c

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re