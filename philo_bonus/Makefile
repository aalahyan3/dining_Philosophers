# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 18:16:10 by aalahyan          #+#    #+#              #
#    Updated: 2025/04/30 10:31:58 by aalahyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_bonus
CC=cc
CFLAGS= -Wall -Wextra -Werror

SRCS= main_bonus.c parse_bonus.c utils_bonus.c start_simulation_bonus.c philo_child_proc_bonus.c get_unique_sem_name_bonus.c

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