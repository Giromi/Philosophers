# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 23:37:23 by minsuki2          #+#    #+#              #
#    Updated: 2022/08/20 00:26:59 by minsuki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = philo_bonus

CFLAGS = -Wall -Werror -Wextra
# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread

SRCS = philo_bonus.c	 		\
	   philo_utils_bonus.c		\
	   routine_bonus.c			\
	   print_out_bonus.c		\
	   ft_postive_atoi_bonus.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

all : $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

debug: all
	$(CC) -lpthread $(OBJS) -o $(NAME)
#$(CC) -lpthread $(OBJS) -o $(NAME) -fsanitize=address

lldb: all
	$(CC) $(CFLAGS) -lpthread $(SRCS) -o $(NAME) -g3

re:
	make fclean
	make all

.PHONY: all clean fclean re
